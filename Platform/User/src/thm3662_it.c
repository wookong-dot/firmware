 /**
  ******************************************************************************
  * @file    thm3622_it.c
  * @author  TMC Terminal Team
  * @version V1.0.0
  * @date    06/01/2018
  * @brief   This file provides all the IRQHandler functions.
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
#include "config.h"
#include "thm36x2.h"
#include "pxat_include.h"

/**
  * @brief  interrupt service function for NMI
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{

}
/**
  * @brief  interrupt service function for HardFault
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
    while(1);
}

/**
  * @brief  interrupt service function for MemManage
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{

}

/**
  * @brief  interrupt service function for BusFault
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{

}

/**
  * @brief  interrupt service function for UsageFault
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{

}

/**
  * @brief  interrupt service function for SVC
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{

}

/**
  * @brief  interrupt service function for DebugMon
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void) 
{

}

/**
  * @brief  interrupt service function for PendSV
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{

}

/**
  * @brief  interrupt service function for SysTick
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
    systick_cnt++;
}

/**
  * @brief  interrupt service function for RCC
  * @param  None
  * @retval None
  */
void RCC_IRQHandler(void)
{

}

/**
  * @brief  interrupt service function for DMA
  * @param  None
  * @retval None
  */
void DMA_IRQHandler(void)
{

}

/**
  * @brief  interrupt service function for AHBMMU
  * @param  None
  * @retval None
  */
void AHBMMU_IRQHandler(void)
{

}

/**
  * @brief  interrupt service function for MPU
  * @param  None
  * @retval None
  */
void MPU_IRQHandler(void) 
{

}

/**
  * @brief  interrupt service function for SM4
  * @param  None
  * @retval None
  */
void SM4_IRQHandler (void)
{

}

/**
  * @brief  interrupt service function for AES
  * @param  None
  * @retval None
  */
void AES_IRQHandler(void)
{

}

/**
  * @brief  interrupt service function for DES
  * @param  None
  * @retval None
  */
void DES_IRQHandler(void)
{

}

/**
  * @brief  interrupt service function for PKE
  * @param  None
  * @retval None
  */
void PKE_IRQHandler(void)
{

}

/**
  * @brief  interrupt FD2 function for EGS
  * @param  None
  * @retval None
  */
void EGS_IRQHandler(void)
{
    while(1);
}

/**
  * @brief  interrupt FD2 function for LD
  * @param  None
  * @retval None
  */
void LD_IRQHandler (void)
{

}

/**
  * @brief  interrupt service function for TRNG
  * @param  None
  * @retval None
  */
void TRNG_IRQHandler(void)
{

}

/**
  * @brief  interrupt FD2 function for FD2
  * @param  None
  * @retval None
  */
void FD2_IRQHandler(void)
{

}

/**
  * @brief  interrupt FD2 function for SENSOR
  * @param  None
  * @retval None
  */
void FD3_IRQHandler(void)
{

}

/**
  * @brief  interrupt service function for VB_SENSOR
  * @param  None
  * @retval None
  */
void VB_SENSOR_IRQHandler(void)
{

}

/**
  * @brief  interrupt service function for ASH
  * @param  None
  * @retval None
  */
void ASH_IRQHandler(void)
{
    while(1);
}

/**
  * @brief  interrupt service function for WWDT
  * @param  None
  * @retval None
  */
void WWDT_IRQHandler(void)
{

}

/**
  * @brief  interrupt service function for TIMER1
  * @param  None
  * @retval None
  */
void TIMER1_IRQHandler(void)
{

}

/**
  * @brief  interrupt service function for TIMER2
  * @param  None
  * @retval None
  */
void TIMER2_IRQHandler(void)
{
    TIM_ClearITStatus(TIM2);
    if(led_wink_flag != LED_IDLE)
    {
        led_handler();
    }
}

/**
  * @brief  interrupt service function for TIMER3
  * @param  None
  * @retval None
  */
void TIMER3_IRQHandler(void)
{

}

/**
  * @brief  interrupt service function for TIMER4
  * @param  None
  * @retval None
  */
void TIMER4_IRQHandler(void)
{

}

/**
  * @brief  interrupt service function for TIMER5
  * @param  None
  * @retval None
  */
void TIMER5_IRQHandler(void)
{

}

/**
  * @brief  interrupt service function for TIMER6
  * @param  None
  * @retval None
  */
void TIMER6_IRQHandler(void)
{

}

/**
  * @brief  interrupt service function for FLASH1
  * @param  None
  * @retval None
  */
void FLASH1_IRQHandler(void)
{

}

/**
  * @brief  interrupt service function for GPIO
  * @param  None
  * @retval None
  */
void GPIO_IRQHandler(void)
{

}

/**
  * @brief  interrupt service function for SPI1
  * @param  None
  * @retval None
  */
void SPI1_IRQHandler(void)
{

}

/**
  * @brief  interrupt service function for SPI2
  * @param  None
  * @retval None
  */
void SPI2_IRQHandler(void)
{

}

/**
  * @brief  interrupt service function for SPI3
  * @param  None
  * @retval None
  */
void SPI3_IRQHandler(void)
{

}

/**
  * @brief  interrupt service function for UART1
  * @param  None
  * @retval None
  */
//void UART1_IRQHandler(void)
//{

//}

/**
  * @brief  interrupt service function for UART2
  * @param  None
  * @retval None
  */
void UART2_IRQHandler(void)
{

}

/**
  * @brief  interrupt service function for UART3
  * @param  None
  * @retval None
  */
void UART3_IRQHandler(void)
{

}

/**
  * @brief  interrupt service function for I2C
  * @param  None
  * @retval None
  */
void I2C_IRQHandler(void)
{

}

/**
  * @brief  interrupt service function for ISO7816M1
  * @param  None
  * @retval None
  */
void ISO7816M1_IRQHandler(void)
{

}

/**
  * @brief  interrupt service function for ISO7816M2
  * @param  None
  * @retval None
  */
void ISO7816M2_IRQHandler(void)
{

}

/**
  * @brief  interrupt service function for ISO7816M3
  * @param  None
  * @retval None
  */
void ISO7816M3_IRQHandler(void)
{

}

/**
  * @brief  interrupt service function for PWM1
  * @param  None
  * @retval None
  */
void PWM1_IRQHandler(void)
{

}

/**
  * @brief  interrupt service function for PWM2
  * @param  None
  * @retval None
  */
void PWM2_IRQHandler(void)
{

}

/**
  * @brief  interrupt service function for DCMI
  * @param  None
  * @retval None
  */
void DCMI_IRQHandler(void)
{

}

/**
  * @brief  interrupt service function for USB
  * @param  None
  * @retval None
  */
void USB_IRQHandler(void)
{

}

/**
  * @brief  interrupt service function for UART4
  * @param  None
  * @retval None
  */
void UART4_IRQHandler(void)
{

}

/**
  * @brief  interrupt service function for ADC
  * @param  None
  * @retval None
  */
void ADC_IRQHandler(void)
{

}

/**
  * @brief  interrupt service function for EXTI0_15
  * @param  None
  * @retval None
  */
void EXTI0_15_IRQHandler(void)
{

}

/**
  * @brief  interrupt service function for EXTI16_31
  * @param  None
  * @retval None
  */
void EXTI16_31_IRQHandler(void)
{

}

/**
  * @brief  interrupt service function for EXTI32_47
  * @param  None
  * @retval None
  */
void EXTI32_47_IRQHandler(void)
{

}

/**
  * @brief  interrupt service function for EXTI48_63
  * @param  None
  * @retval None
  */
void EXTI48_63_IRQHandler(void)
{

}

/**
  * @brief  interrupt service function for EXTI64_65
  * @param  None
  * @retval None
  */
void EXTI64_79_IRQHandler(void)
{

}

/**
  * @brief  interrupt service function for EXTI80
  * @param  None
  * @retval None
  */
void EXTI80_IRQHandler(void)
{

}

/**
  * @brief  interrupt service function for EXTI81
  * @param  None
  * @retval None
  */
void EXTI81_IRQHandler(void)
{

}

/**
  * @brief  interrupt service function for EXTI82
  * @param  None
  * @retval None
  */
void EXTI82_IRQHandler(void)
{

}

/**
  * @brief  interrupt service function for EXTI83
  * @param  None
  * @retval None
  */
void EXTI83_IRQHandler(void)
{

}

/**
  * @brief  interrupt service function for EXTI84
  * @param  None
  * @retval None
  */
void EXTI84_IRQHandler(void)
{

}

/**
  * @brief  interrupt service function for EXTI85
  * @param  None
  * @retval None
  */
void EXTI85_IRQHandler(void)
{

}
