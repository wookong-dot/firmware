 /**
  ******************************************************************************
  * @file    system_thm36x2.c
  * @author  TMC Terminal Team
  * @version V1.0.0
  * @date    06/01/2018
  * @brief   This file provides SystemInit functions.
  * History:
  *          2018-06-01 Original version
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
#include "thm36x2.h"

uint32_t SystemCoreClock = 12000000;
__IO uint32_t systick_cnt = 0;
/**
  * @brief  Setup the microcontroller system
  *         Initialize the FPU setting, vector table location and External memory 
  *         configuration.
  * @param  None
  * @retval None
  */
void SystemInit(void)
{
    RCC_PLL_InitTypeDef PLLConfig;
    /*使能cache时钟*/
    RCC_AHBClockCmd(RCC_AHBPeriph_FLASHCACHE,ENABLE);
    /*关闭Ichace 关闭Dchace*/
    Flash_IcacheRest(Flash_ACC,DISABLE);
    Flash_IcacheCmd(Flash_ACC,ENABLE);
    Flash_DcacheRest(Flash_ACC,DISABLE);

    /*使能HSI时钟*/
    RCC_HSICmd(ENABLE);

    /*配置PLL时钟为192MHZ*/
    PLLConfig.PLL_Input = RCC_PLLC_PLLSRC_HSI;
    PLLConfig.PLL_M = 1;
    PLLConfig.PLL_N = 16;
    PLLConfig.PLL_Q = 4;
    PLLConfig.SourceClockVaule = HSI_VALUE;

    /* Disable the main PLL. */
    RCC_PLLCmd(DISABLE);
    /* Wait till PLL is not ready */
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) != RESET);
    /* Configure the main PLL clock source, multiplication and division factors. */
    RCC_PLLConfig(&PLLConfig);
    RCC_Enable();

    /*配置系统时钟为192MHZ*/
    RCC_SystemClockConfig(RCC_SYS_CLKSRC_PLL_H, 0);
    SystemCoreClock = RCC_GetSysClocksFreq();

    SysTick_Config(SystemCoreClock/1000);   //1ms
    NVIC_SetPriority(SysTick_IRQn, 0);
    NVIC_ClearPendingIRQ(SysTick_IRQn);
    NVIC_EnableIRQ(SysTick_IRQn);
}
