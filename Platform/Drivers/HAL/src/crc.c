/**
  ******************************************************************************
  * @file    CRC.c
  * @author  TMC Terminal Team
  * @version V1.0.0
  * @date    01/21/2016
  * @brief   This file provides all the CRC firmware functions.
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
#include "rcc.h"
#include "crc.h"

/** @addtogroup THM36x2
  * @{
  */
/** @addtogroup THM36x2_HAL_Driver
  * @{
  */
/** @defgroup CRC
  * @brief CRC HAL modules driver 
  * @{
  */
/** @defgroup CRC_private_defines CRC private defines
  * @{
  */


/**
  * @}
  */
/** @defgroup CRC_exported_function CRC exported function
  * @{  
  */


/**
  * @brief  Fills each CRC_InitStruct member with its default value.
  * @param[in] CRC_InitStruct: pointer to a CRC_InitTypeDef structure,which will be initialized.
  * @retval none
  * @note  none
  */
__weak void CRC_StructInit(CRC_InitTypeDef *CRC_InitStruct)
{
	assert_param(IS_CRC_MODE(CRC_InitStruct->CRC_Mode));
	assert_param(IS_CRC_READ(CRC_InitStruct->CRC_Read));
	CRC_InitStruct->CRC_Mode = CRC_MODE_CCITT;
	CRC_InitStruct->CRC_Read = CRC_LITTLE_ENDIAN;
	CRC_InitStruct->CRC_Result_Reverberate = DISABLE;
	CRC_InitStruct->CRC_Data_Reverberate = DISABLE;
}

/**
  * @brief  Initializes the SPIx  peripheral according to 
  *   the specified parameters in the SPI_InitTypeDef.
  * @param[in] select the SPI1 or SPI3 peripheral.
  * @param[in] SPI_InitStruct: pointer to a SPI_InitTypeDef structure,which will be initialized.
  * @retval none
  * @note  The default value is as following
  */
void CRC_Init(CRC_InitTypeDef *CRC_InitStruct)
{
	assert_param(IS_CRC_MODE(CRC_InitStruct->CRC_Mode));
	assert_param(IS_CRC_READ(CRC_InitStruct->CRC_Read));
	if(CRC_InitStruct->CRC_Mode == CRC_MODE_CCITT)
	{
		CRC->CON1&= CRC_MODE_CCITT;
	}
	else
	{
		CRC->CON1|= CRC_MODE_32;
	}
	if(CRC_InitStruct->CRC_Read == CRC_LITTLE_ENDIAN)
	{
		CRC->CON1&= CRC_LITTLE_ENDIAN;
	}
	else
	{
		CRC->CON1|= CRC_BIG_ENDIAN;
	}
	if(CRC_InitStruct->CRC_Data_Reverberate == DISABLE)
	{
		CRC->CON1&= ~(0x04UL);
	}
	else
	{
		CRC->CON1|= (0x04UL);
	}
	if(CRC_InitStruct->CRC_Data_Reverberate == DISABLE)
	{
		CRC->CON1&= ~(0x02UL);
	}
	else
	{
		CRC->CON1|= (0x02UL);
	}
}

/**
  * @brief calculate CRC16
  * @param[in] initial value
  * @param[in] input data
  * @param[in] input data length.
  * @retval CRC16 Value
  */
uint16_t CRC_CCITT_Kermit(uint16_t Init, uint8_t * Data, uint16_t Len)
{
	uint16_t sResult=0;
    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_CRC, ENABLE); //enable crc clock
	
	sResult = CRC->DAT;							//	Reset CRC
	CRC->CON1 = 0x0000000E;
    CRC->CON = Init;
	
	while(Len--)
		CRC->DAT = *Data++;
	
	sResult = CRC->DAT & 0xff;						//	Read CRC
	sResult <<= 8;
	sResult |= CRC->DAT& 0xff;
    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_CRC, DISABLE); //disable crc clock
	return sResult;
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

