 /**
  ******************************************************************************
  * @file    FSMC.c
  * @author  TMC Terminal Team
  * @version V1.0.0
  * @date    06/01/2018
  * @brief   This file provides all the RCC firmware functions.
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

/* Includes ------------------------------------------------------------------*/

#include "thm36x2.h"
#include "RCC.h"
#include "FSMC.h"

/** @addtogroup THM36x2
  * @{
  */
  
/** @addtogroup THM36x2_HAL_Driver
  * @{
  */

/** @defgroup FSMC 
  * @brief FSMC HAL modules driver 
  * @{
  */ 
  
/** @defgroup FSMC_Private_Defines FSMC Private Defines
  * @{
  */
/**
  * @}
  */
/**
  * @brief  Fills each FSMC_InitTypeDef member with its default value.
  * @param[in] FSMC_InitStruct: pointer to a FSMC_InitTypeDef structure,which will be initialized.
  * @retval none
  * @note  The default value is as following
  */
void FSMC_StructInit(FSMC_InitTypeDef * FSMC_InitStruct)
{
	if(FSMC_InitStruct == NULL)
	return;
	FSMC_InitStruct->FSMC_ExtMode = FSMC_EXTEND_MODE_DISABLE;
	FSMC_InitStruct->FSMC_MemoryDataWidth = FSMC_DATA_WIDTH_16BIT;
	FSMC_InitStruct->FSMC_MemoryType = FSMC_MEMORY_TYPE_SRAM;		/*SRAM Mode is LCD Mode*/
	FSMC_InitStruct->MemoryWrite = FSMC_MEMORY_WRITE_ENABLE;
}

/**
  * @brief  Initializes the FSMC according to the specified
  *         parameters in the FSMC_InitTypeDef and create the associated handle.
  * @param  hdcmi pointer to a FSMC_InitTypeDef structure that contains
  *                the configuration information for DCMI.
  * @retval HAL status
  */  
void FSMC_Init(FSMC_InitTypeDef * FSMC_InitStruct)
{
	uint32_t temp = 0;
	assert_param(IS_POINT_NULL(FSMC_InitStruct));
	assert_param(IS_FSMC_EXTEND_MODE(FSMC_InitStruct->FSMC_ExtMode));
	assert_param(IS_FSMC_MEMORY_WRITE_MODE(FSMC_InitStruct->MemoryWrite));
	assert_param(IS_FSMC_DATA_WIDTH_MODE(FSMC_DATA_WIDTH_16BIT));
	assert_param(IS_FSMC_MEMORY_TYPE_MODE(FSMC_InitStruct->FSMC_MemoryType ));
	temp = FSMC_InitStruct->FSMC_ExtMode|FSMC_InitStruct->FSMC_MemoryDataWidth|FSMC_InitStruct->FSMC_MemoryType|FSMC_InitStruct->MemoryWrite;
	FSMC->BCR = temp;
}

/**
  * @brief   config  Read LCD Duration Time        
  * @param  FSMC_TimingStruct pointer to a FSMC_TimingTypeDef structure that contains
  *                the configuration information for DCMI.
  * @retval none
  */  
void FSMC_ConfigReadModeDurationTimes(FSMC_TimingTypeDef * FSMC_TimingStruct)
{
	uint32_t temp;
	assert_param(IS_POINT_NULL(FSMC_TimingStruct));
	assert_param(IS_FSMC_BUS_TURNS(FSMC_TimingStruct->FSMC_BusTurn));
	assert_param(IS_FSMC_DATA_STR(FSMC_TimingStruct->FSMC_DATAST));
	assert_param(IS_FSMC_ADD_SET(FSMC_TimingStruct->FSMC_ADDSET));
	assert_param(IS_FSMC_ACC_MODE(FSMC_TimingStruct->FSMC_AccMode));
	temp = (FSMC_TimingStruct->FSMC_BusTurn<<16)|(FSMC_TimingStruct->FSMC_DATAST<<8)|FSMC_TimingStruct->FSMC_ADDSET;
	FSMC->BTR = temp;	
}


/**
  * @brief   config  Write LCD Duration Time           
  * @param  FSMC_TimingStruct pointer to a FSMC_TimingTypeDef structure that contains
  *                the configuration information for DCMI.
  * @retval none
  */  
void FSMC_ConfigWriteModeDurationTimes(FSMC_TimingTypeDef * FSMC_TimingStruct)
{
	uint32_t temp;
	assert_param(IS_POINT_NULL(FSMC_TimingStruct));
	assert_param(IS_FSMC_BUS_TURNS(FSMC_TimingStruct->FSMC_BusTurn));
	assert_param(IS_FSMC_DATA_STR(FSMC_TimingStruct->FSMC_DATAST));
	assert_param(IS_FSMC_ADD_SET(FSMC_TimingStruct->FSMC_ADDSET));
	temp = (FSMC_TimingStruct->FSMC_BusTurn<<16)|(FSMC_TimingStruct->FSMC_DATAST<<8)|FSMC_TimingStruct->FSMC_ADDSET;
	FSMC->BWTR= temp;	
}

/**
  * @brief config the FSMC MSK Enable will be  optimize  performance      
  * @param  Msk : Enable or Disable MSK
  * @retval none 
  */
void FSMC_ConfigRLSNWE(uint32_t Msk)
{
	assert_param(IS_FSMC_MSK(Msk));	
	FSMC->CR2 = Msk;
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

/************************ (C) COPYRIGHT TMC *****END OF FILE***********************/

