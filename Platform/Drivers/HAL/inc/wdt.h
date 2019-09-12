/**
  ******************************************************************************
  * @file    WDT.h
  * @author  TMC  Team
  * @version V3.1.0
  * @date    06/19/2009
  * @brief   This file contains all the functions prototypes for the WDT firmware 
  *          library.
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
#ifndef __WDT_H
#define __WDT_H

#ifdef __cplusplus
 extern "C" {
#endif
/** @addtogroup THM36x2
  * @{
  */
/** @addtogroup THM36x2_HAL_Driver
  * @{
  */
/** @defgroup WDT
  * @brief WDT HAL modules driver 
  * @{
  */ 

/** @defgroup WDT_Exported_Types HAL WDT Exported Types
  * @{
  */
	 
/** 
  * @brief  WDT Init structure definition
  */
typedef struct
{
	uint32_t			Loadvalue;       /*!< Specifies the WDT counter value.
										This parameter must be a number between Min_Data = 0x01 and Max_Data = 0xFFFFFFFF */
	
	uint32_t			Mode;       	/*!< Specifies the WDT Mode.
										This parameter can be a value of @ref WDT_set_mode							 */
}WDT_InitTypeDef;

/**
  * @}
  */

/** @defgroup WDT_Exported_Constants WDT Exported Constants
  * @{
  */

/** @defgroup WDT_set_mode WDT set mode 
  * @{
  */

#define WDT_MODE_ALARM				0x00000002UL
#define WDT_MODE_INT				0x00000000UL


/**
  * @}
  */
/**
  * @}
  */

/** @addtogroup WDT_Exported_Function 
  * @{  
  */   
void WDT_DeInit(void);
void WDT_Init(WWDT_TypeDef *WDT, WDT_InitTypeDef * init);
void WDT_Cmd(WWDT_TypeDef *WDT, FunctionalState NewState);
FlagStatus WDT_GetFlagStatus(WWDT_TypeDef *WDT);
FlagStatus WDT_GetITStatus(WWDT_TypeDef *WDT);
void WDT_ClearFlag(WWDT_TypeDef *WDT);
uint32_t WDT_ReadCurrentValue(WWDT_TypeDef *WDT);
void WDT_FeedDog(WWDT_TypeDef *WDT, WDT_InitTypeDef * init);
void WDT_StructInit(WDT_InitTypeDef * init);
/**
  * @}
  */

/** @defgroup WDT_private_macros WDT private macros
  * @{
  */

#define IS_WDT_LOADVALUE(b) ((b>0)&&(b<=0xFFFFFFFF))
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

#endif   
  

  
  



