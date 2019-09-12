/**
  ******************************************************************************
  * @file    ADC.h
  * @author  TMC Terminal Team
  * @version V1.0.0
  * @date    01/21/2016
  * @brief   This file provides all the ADC.h firmware functions.
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
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _CRC_H
#define _CRC_H

#ifdef __cplusplus
 extern "C" {
#endif
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
/** @defgroup CRC_Exported_Constants CRC Exported Constants
  * @{
  */
/** 
  * @brief  CRC Init structure definition
  * @note   This sturcture is used with  PWM   
  */	 
typedef struct
{
	uint32_t	CRC_Mode;
	uint32_t	CRC_Read;
	FunctionalState	CRC_Result_Reverberate;
	FunctionalState	CRC_Data_Reverberate;
} CRC_InitTypeDef;


/** @defgroup CRC_Mode CRC Mode
  * @{
  */
#define  CRC_MODE_32		0x30UL
#define  CRC_MODE_CCITT		~(0x30UL)

/**
  * @}
  */

/** @defgroup CRC_Read CRC Read
  * @{
  */
#define  CRC_BIG_ENDIAN		1UL<<3
#define  CRC_LITTLE_ENDIAN	~(1UL<<3)

/**
  * @}
  */


/** @defgroup CRC_Private_Macros CRC Private Macros
  * @{
  */
#define  IS_CRC_MODE(x)	((x == CRC_MODE_32)||(x == CRC_MODE_CCITT))
#define  IS_CRC_READ(x)	((x == CRC_BIG_ENDIAN)||(x == CRC_LITTLE_ENDIAN))

/**
  * @}
  */

  
/** @addtogroup CRC_Exported_Function 
  * @{  
  */   
void CRC_StructInit(CRC_InitTypeDef *CRC_InitStruct);
void CRC_Init(CRC_InitTypeDef *CRC_InitStruct);
uint16_t CRC_CCITT_Kermit(uint16_t Init, uint8_t * Data, uint16_t Len);
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
/**
  * @}
  */
#ifdef __cplusplus
}
#endif
#endif /* __TMC_PWM_H */

/************************ (C) COPYRIGHT TMC *****END OF FILE****/


