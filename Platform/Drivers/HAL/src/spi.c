/**
  ******************************************************************************
  * @file    SPI.c
  * @author  TMC Terminal Team
  * @version V1.0.0
  * @date    01/21/2016
  * @brief   This file provides all the SPI firmware functions.
  * History:
  *          2016-01-13 Original version
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
  *******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "thm36x2.h"
#include "thm36x2_hal_def.h"
#include "rcc.h"
#include "spi.h"

/** @addtogroup THM36x2
  * @{
  */
/** @addtogroup THM36x2_HAL_Driver
  * @{
  */
/** @defgroup SPIx
  * @brief SPIx HAL modules driver 
  * @{
  */
/** @defgroup SPI_private_defines SPI private defines
  * @{
  */
#define SPIx_CON2_DEFAUT_VALUE	(0x00008040UL)
#define SPIx_CON3_DEFAUT_VALUE	(0x00000020UL)

/**
  * @}
  */
/** @defgroup SPI_exported_function FLASH exported function
  * @{  
  */

/**
  * @brief  Fills each SPI_InitStruct member with its default value.
  * @param[in] SPI_InitStruct: pointer to a SPI_InitTypeDef structure,which will be initialized.
  * @retval none
  * @note  The default value is as following
  */
__weak void SPIx_StructInit(SPI_InitTypeDef* SPI_InitStruct)
{
	SPI_InitStruct->Master_EGT = 0;
	SPI_InitStruct->BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	SPI_InitStruct->CLKPhase = SPI_PHASE_1EDGE;
	SPI_InitStruct->CLKPolarity = SPI_POLARITY_HIGH;
	SPI_InitStruct->Mode = SPI_MASTER_MODE;
	SPI_InitStruct->SQI_Select = SPI_MODE;
}

/**
  * @brief  Initializes the SPIx  peripheral according to 
  *   the specified parameters in the SPI_InitTypeDef.
  * @param[in] select the SPI1 or SPI3 peripheral.
  * @param[in] SPI_InitStruct: pointer to a SPI_InitTypeDef structure,which will be initialized.
  * @retval none
  * @note  The default value is as following
  */
void SPIx_Init(SPI_TypeDef* SPIx,SPI_InitTypeDef* SPI_InitStruct)
{
	SPIx->CON2 = (SPI_InitStruct->Master_EGT<<8)|SPI_InitStruct->BaudRatePrescaler|SPI_InitStruct->Mode|SPI_InitStruct->CLKPhase|SPI_InitStruct->CLKPolarity;
	SPIx->CON3 = SPI_InitStruct->SQI_Select;
}

/**
  * @brief Deinitializes the SPIx peripheral registers to their default reset values.
  * @param[in] SPIx: select the SPI1 or SPI3 peripheral.
  * @retval none
  * @note  
  */
void SPIx_DeInit(SPI_TypeDef* SPIx)
{
	if(SPIx == SPI1)
	{
		RCC_APB2PeriphSoftReset(RCC_APB2Periph_SPI1);
		while(RCC_APB2PeriphGetResetFlag(RCC_APB2Periph_SPI1) == RESET);
	}
	if(SPIx == SPI3)
	{
		RCC_APB2PeriphSoftReset(RCC_APB2Periph_SPI3);
		while(RCC_APB2PeriphGetResetFlag(RCC_APB2Periph_SPI3) == RESET);
	}
}

/**
  * @brief SPIx Send a byte 
  * @param[in] select the SPI1 or SPI3 peripheral.
  * @param[in] Data: data of send
  * @retval none
  * @note  
  */
void SPIx_SendData(SPI_TypeDef* SPIx,uint8_t Data)
{
	SPIx->DAT = Data;
}

/**
  * @brief SPIx Receive a byte 
  * @param[in] SPIx: where x can be 0 to 2 to select the SPI peripheral.
  * @param[in] Data: data of receive
  * @retval none
  * @note  
  */
uint8_t SPIx_ReceiveData(SPI_TypeDef* SPIx)
{
	return SPIx->DAT;
}

/**
  * @brief Get SPIx's Status
  * @param[in] select the SPI1 or SPI3 peripheral.
  * @param[in] Flag: the status of SPIx
  *				@arg SPI_BOVER_FLAG
  *				@arg SPI_TBE_FLAG
  * @retval FlagStatus
  * @note  
  */
FlagStatus SPIx_GetStatus(SPI_TypeDef* SPIx,uint32_t Flag)
{
	if(SPIx->STS&Flag)
	{
		return SET;
	}
	else
	{
		return RESET;
	}
}

/**
  * @brief Enable or Disable SPIx
  * @param[in] select the SPI1 or SPI3 peripheral.
  * @param[in] NewState: NewState: new state of the SPIx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval none
  * @note  
  */
void SPIx_Cmd(SPI_TypeDef* SPIx,FunctionalState NewState)
{
	if(NewState == ENABLE)
	{
		SPIx->CON2|= SPI_ENABLE;
	}
	else
	{
		SPIx->CON2&= SPI_DISABLE;
	}
}

/**
  * @brief Clear SPIx's Status
  * @param[in] select the SPI1 or SPI3 peripheral.
  * @retval FlagStatus
  * @note  
  */
void SPIx_ClearBoverStatus(SPI_TypeDef* SPIx)
{
	__IO uint32_t temp;
	temp = SPIx->DAT;
}

/**
  * @brief  Config Interrupt of SPIx
  * @param[in] select the SPI1 or SPI3 peripheral.
  * @param[in] Flag: the status of SPIx
  *				@arg SPI_BOVER_IT
  *				@arg SPI_TBE_IT
  * @retval FlagStatus
  * @note  
  */
void SPIx_ITConfig(SPI_TypeDef* SPIx,uint32_t Flag,FunctionalState NewState)
{
	if(NewState == DISABLE)
	{
		SPIx->MSK |= Flag;
	}
	else
	{
		SPIx->MSK &= ~Flag;
	}
}

/**
  * @brief enable or disable the SPIx Tx DMA mode 
  * @param[in] select the SPI1 or SPI3 peripheral.
  * @param[in] Mode DMA config Mode
  *		@arg SPI_RX_DMA
  *		@arg SPI_TX_DMA
  * @param[in] NewState: NewState: new state of the SPIx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval none
  * @note  
  */
void SPIx_ConfigDMA(SPI_TypeDef* SPIx,uint8_t Mode,FunctionalState NewState)
{
	if(NewState == ENABLE)
	{
		if((Mode & SPI_RX_DMA)&&(Mode & SPI_TX_DMA))
		{
			SPIx->DMACON = SPI_RX_DMA|SPI_TX_DMA;
		}
		else if(Mode == SPI_RX_DMA)
		{
			SPIx->DMACON = SPI_RX_DMA;
		}
		else if(Mode == SPI_TX_DMA)
		{
			SPIx->DMACON = SPI_TX_DMA;
		}
	}
	else
	{
		
		SPIx->DMACON = 0;
	}	
}

/**
  * @brief Get SPI Rx DMA status,wether is SET or RESET
  * @param[in] select the SPI1 or SPI3 peripheral.
  * @retval FlagStatus 
  * @note  
  */
void SPIx_ConfigSQI_IO(SPI_TypeDef* SPIx,SQI_IO_Mode mode)
{
	if(mode == Input)
	{
		SPIx->CON3 |= 1<<5;
	}
	else
	{
		SPIx->CON3 &= ~(1<<5);
	}
}

/**
  * @}
  */
/**
  * @}
  */
/**
  * @}
  */
/**
  * @}
  */

/************************ (C) COPYRIGHT TMC *****END OF FILE****/



