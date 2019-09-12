 /**
  ******************************************************************************
  * @file    main.c
  * @author  TMC Terminal Team
  * @version V1.0.0
  * @date    06/01/2018
  * @brief   This file provides main functions.
  * History:
  *          2018-06-01 Original version
  *          2019-01-22 modify by xinght
  ******************************************************************************
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, TMC SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2016 TMC</center></h2>
  ******************************************************************************/
#include "config.h"
#include "thm36x2.h"
#include "pxat_include.h"

/*HAL层 形参检查错误*/
void assert_failed(uint8_t* file, uint32_t line)
{
    while(1);
}

void NVIC_SetVectorTable(u32 NVIC_VectTab, u32 Offset)
{
    SCB->VTOR = NVIC_VectTab|(Offset & (u32)0x1FFFFF80);
}

/************************************************************************************
*   =========================DEBUG BOARD=========================
*   SENSOR_SPI:
*           MOSI    --  GB_IO12[SPI3_VDD3]
*           MISO    --  GB_IO13[SPI3_VDD3]
*           CLK     --  GB_IO14[SPI3_VDD3]
*           CS      --  GD_IO4 [SPI3_VDD3]
*           RESET   --  GD_IO11[VDD3]
*           INT     --  VB_IO3[VBAT]
*   DEBUG_UART:
*           TX      --  GC_IO12[UART1_VDD2]
*   AVALON_UART:
*           TX      --  GC_IO12[UART1_TX_VDD2]
*           RX      --  GC_IO15[UART1_RX_VDD2]
*   LED:
*           GREEN   --  GC_IO14[VDD2]
*           RED     --  GC_IO13[VDD2]
*           BLUE    --  GD_IO12[VDD2]
*   SWD:
*           CLK     --  GB_IO5[VDD2]
*           IO      --  GB_IO6[VDD2]
*   TIMER:
*           IRQ     --  TIM2
************************************************************************************/
void InitHardware(void)
{
    GPIO_InitTypeDef GPIOx_Init;
    TIM_TimeInitTypeDef TIMERx_Init;
    UART_InitTypeDef AVALON_UART_Init;

    // copy vector to ram
    memcpy((void *)0x20000000,(void *)FLASH_STRAT_ADDRESS,(75+16)*4);
    NVIC_SetVectorTable(0x20000000,0x20000000);

    // flash clk
    RCC_Security2PeriphClockCmd(RCC_SEC2Periph_FLASH,ENABLE);

    // trng clk //随机数函数存放在ROM内 使用前需要打开门控时钟
    RCC_Security1PeriphClockCmd(RCC_SEC1Periph_TRNG,ENABLE);

    // pke clk //非对称算法库在ROM内掩摸 使用前需打开门控时钟
    RCC_Security1PeriphClockCmd(RCC_SEC1Periph_PKE,ENABLE);
    pkeConfig(0xFF,0x0F,0x01);    //PKE初始化函数

    //RCC_AHBClockCmd(RCC_AHBPeriph_DMA,ENABLE);

    // flash init
    RCC_Security2PeriphGetResetFlag(RCC_SEC2Periph_FLASH);
    while(RCC_Security2PeriphGetResetFlag(RCC_SEC2Periph_FLASH) == RESET);
    FLASH_ClearFlag(FLASH_FLAG_OPERR|FLASH_FLAG_OVER|FLASH_FLAG_EVERR|FLASH_FLAG_PVERR|FLASH_FLAG_HVERR);

    // gpio clk
    RCC_APB3PeriphClockCmd(RCC_APB3Periph_GPIO,ENABLE);

    // bat reg write enable
    BAT_WriteEnable(ENABLE);
    // lsi clk enable
    RCC_LSICmd(ENABLE);
    while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET);

    // timer clk
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIMER1_2, ENABLE);

    /****************************** T I M 2 - TIMER_LED *******************************/
    // enalbe timer2 interrupt mode for led 100ms
    RCC_TimerClockConfig(PERIPHERAL_TIMER2, RCC_TIMER_CLKSRC_HSI, 5, ENABLE);
    TIMERx_Init.TIM_CounterMode = TIM_MODE_CONTINUITY_RELOAD;
    TIMERx_Init.TIM_Presclar = TIM_PRESCLAR_NOT_DIV;
    TIMERx_Init.TIM_SizeMode = TIM_SIZE_32BIT;
    TIM_TimeInit(TIM2,&TIMERx_Init);
    TIM_SetLoadValue(TIM2,(uint32_t)100*2000);
    TIM_ITConfig(TIM2,ENABLE);
    NVIC_ClearPendingIRQ(TIMER2_IRQn);
    NVIC_EnableIRQ(TIMER2_IRQn);
    TIM_Cmd(TIM2,ENABLE);

    /***************************** U A R T - AVALON_UART ******************************/
    GPIOx_Init.Pin = GPIO_PIN_12|GPIO_PIN_15;
    GPIOx_Init.Mode = GPIO_MODE_AF;
    GPIOx_Init.Speed = GPIO_FAST_SPEED;
    GPIOx_Init.Pull = GPIO_PULLUP;
    GPIOx_Init.Otype = GPIO_MODE_OUTPUT_PP;
    GPIOx_Init.SMIT = GPIO_INPUTSCHMIT_DISABLE;
    GPIO_Init(GPIOC, &GPIOx_Init);

    // uart tx rx
    GPIO_PinAFConfig(GPIOC,GPIO_PIN_Source12,GPIO_AF3_UART1);
    GPIO_PinAFConfig(GPIOC,GPIO_PIN_Source15,GPIO_AF3_UART1);

    //open uart clk
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_UART1, ENABLE);

    AVALON_UART_Init.BaudRate = 115200;
    AVALON_UART_Init.DataWidth = UART_DATA_WIDTH_8;
    AVALON_UART_Init.ParityMode = UART_PARITY_MODE_NONE;
    UART_Init(UART1, &AVALON_UART_Init);
    UART_ITConfig(UART1,UART_FLAG_RXF|UART_FLAG_PE|UART_FLAG_OF|UART_FLAG_FE, ENABLE);
    NVIC_ClearPendingIRQ(UART1_IRQn);
    NVIC_EnableIRQ(UART1_IRQn);
}

int main(void)
{
//    ALIGN(4) unsigned char g_message[32] = { 0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,};
//    ALIGN(4) unsigned char g_random[32] = { 0 };
//    ALIGN(4) unsigned char g_keypair[96] = { 74,83,195,251,188,89,151,14,229,248,90,248,19,135,93,255,193,58,144,74,46,83,174,126,101,250,13,234,110,98,201,1,159,7,231,190,85,81,56,122,152,186,151,124,115,45,8,13,203,15,41,160,72,227,101,105,18,198,83,62,50,238,122,237,156,102,163,57,200,52,79,146,47,195,32,108,181,218,232,20,165,148,192,23,125,211,35,92,37,77,156,64,154,101,184,8 }; 
//    ALIGN(4) unsigned int rv = 0; 
//    ALIGN(4) unsigned char g_signout[96] = { 0 };

    InitHardware();

    vdrvar_init();

    led_init();

//    rv = sr_sign(g_message,32,g_random,g_keypair,g_signout);

    while(1)
    {
        vdrmsg_deal();
    }
}
