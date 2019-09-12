/**
  ******************************************************************************
  * @file    I2C.h
  * @author  TMC Terminal Team
  * @version V1.0.0
  * @date    01/21/2016
  * @brief   This file provides all the SUART firmware functions.
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
#ifndef _I2C_H
#define _I2C_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup THM36x2
  * @{
  */
/** @addtogroup THM36x2_HAL_Driver
  * @{
  */
/** @defgroup I2C
  * @brief I2C HAL modules driver 
  * @{
  */ 
/** @defgroup I2C_Exported_Constants I2C Exported Constants
  * @{
  */
	 
/** 
  * @brief  SPI Init structure definition
  * @note   This sturcture is used with  SPI   
  */	 
typedef struct
{
	uint32_t Clock_Divison;	 	/*!<systerm clock frequency Divsion, This parameter can be a value of @ref Clock_Divison_Mode*/ 
	uint32_t I2C_CLK_Divison;	/*!<I2C clock frequency Divsion, This parameter can be a value of @ref I2C_CLK_Divison_Mode*/ 
	uint8_t	 Salve_Address0;	/*!<I2C Address0, */ 
} I2C_InitTypeDef;

/** @defgroup OutStartSignal_Mode OutStartSignal Mode
  * @brief   
  * @{
  */ 
#define GENERATE_STARTING_SIGNAL		(1UL<<5)
#define NONE_GENERATE_STARTING_SIGNAL	0
/**
  * @}
  */

/** @defgroup OutStopSignal_Mode OutStopSignal Mode
  * @brief   
  * @{
  */ 
#define GENERATE_STOP_SIGNAL			(1UL<<4)
#define NONE_GENERATE_STOP_SIGNAL		0
/**
  * @}
  */

/** @defgroup Clock_Divison_Mode Clock Divison Mode
  * @brief   
  * @{
  */ 
#define PRE_FREQUENCY_DIVISON_32		(9UL<<4)
#define PRE_FREQUENCY_DIVISON_20		(8UL<<4)
#define PRE_FREQUENCY_DIVISON_15		(7UL<<4)
#define PRE_FREQUENCY_DIVISON_12		(6UL<<4)
#define PRE_FREQUENCY_DIVISON_10		(5UL<<4)
#define PRE_FREQUENCY_DIVISON_8			(4UL<<4)
#define PRE_FREQUENCY_DIVISON_7			(3UL<<4)
#define PRE_FREQUENCY_DIVISON_6			(2UL<<4)
#define PRE_FREQUENCY_DIVISON_5			(1UL<<4)
#define PRE_FREQUENCY_DIVISON_4			0
/**
  * @}
  */

/** @defgroup I2C_CLK_Divison_Mode I2C CLK Divison Mode
  * @brief   
  * @{
  */ 
#define I2C_CLK_DIVISON_32		(3UL)
#define I2C_CLK_DIVISON_16		(2UL)
#define I2C_CLK_DIVISON_8		(1UL)
#define I2C_CLK_DIVISON_4		0
/**
  * @}
  */

/** @defgroup I2C_ANSWER_MODE I2C ANSWER MODE
  * @brief   
  * @{
  */ 
#define I2C_CLK_ANSWER_ACK		(1UL<<2)
#define I2C_CLK_ANSWER_NACK		0

/**
  * @}
  */
  
/** @defgroup I2C_INT_Flag
  * @brief   
  * @{
  */ 
#define I2C_CLK_INT_Flag	(1UL<<3)


/**
  * @}
  */

/** @defgroup I2C_private_macros I2C private macros
  * @{
  */ 
#define IS_I2C_CHECK_DIVSION(mode)					((mode == PRE_FREQUENCY_DIVISON_32)|| \
												     (mode == PRE_FREQUENCY_DIVISON_20)|| \
													 (mode == PRE_FREQUENCY_DIVISON_15)|| \
													 (mode == PRE_FREQUENCY_DIVISON_12)|| \
													 (mode == PRE_FREQUENCY_DIVISON_10)|| \
													 (mode == PRE_FREQUENCY_DIVISON_8)|| \
													 (mode == PRE_FREQUENCY_DIVISON_7)|| \
													 (mode == PRE_FREQUENCY_DIVISON_6)|| \
													 (mode == PRE_FREQUENCY_DIVISON_5)|| \
													 (mode == PRE_FREQUENCY_DIVISON_4))    
#define IS_CHECK_I2C_CLOCK_DIVSION(mode)			((mode == I2C_CLK_DIVISON_32)|| \
													 (mode == I2C_CLK_DIVISON_16)|| \
													 (mode == I2C_CLK_DIVISON_8)|| \
													 (mode == I2C_CLK_DIVISON_4)) 

#define IS_I2C_CHECK(mode)							(mode == I2C)
#define IS_I2C_CHECK_START_SIGNAL(mode)				((mode == GENERATE_STARTING_SIGNAL)|| \
													 (mode == NONE_GENERATE_STARTING_SIGNAL))
													 
#define IS_I2C_CHECK_STOP_SIGNAL(mode)				((mode == GENERATE_STOP_SIGNAL)|| \
													 (mode == NONE_GENERATE_STOP_SIGNAL))
													 
#define IS_I2C_CHECK_RESPOSE(mode)					((mode == I2C_CLK_ANSWER_ACK)|| \
													 (mode == I2C_CLK_ANSWER_NACK))												 
/**
  * @}
  */

/** @addtogroup I2C_Exported_Function 
  * @{  
  */ 
void I2C_StructInit(I2C_InitTypeDef* I2C_InitStruct);
void I2C_Init(I2C_TypeDef* I2Cx,I2C_InitTypeDef* I2C_InitStruct);
void I2C_DeInit(I2C_TypeDef* I2Cx);
void I2C_OutputStartSignal(I2C_TypeDef* I2Cx,uint32_t mode);
void I2C_OutputStopSignal(I2C_TypeDef* I2Cx,uint32_t mode);
FlagStatus I2C_GetStatusChange(I2C_TypeDef* I2Cx);
void I2C_configResponse(I2C_TypeDef* I2Cx,uint32_t Response);
uint8_t I2C_GetStatus(I2C_TypeDef* I2Cx);
uint8_t I2C_GetData(I2C_TypeDef* I2Cx);
void I2C_SendData(I2C_TypeDef* I2Cx,uint8_t Data);
void I2C_Cmd(I2C_TypeDef* I2Cx,FunctionalState NewState);
void I2C_ConfigSalveAdder0(I2C_TypeDef* I2Cx,uint8_t Addr0);
void I2C_ITConfig(I2C_TypeDef* I2Cx,FunctionalState NewState);
void I2C_BroadcastEnable(I2C_TypeDef* I2Cx,FunctionalState NewState);
void I2C_ClearStatusChange(I2C_TypeDef* I2Cx);
void I2C_ConfigSlaveResponse(I2C_TypeDef* I2Cx,uint8_t mode);
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
#endif /* __TMC_SPI_H */

/************************ (C) COPYRIGHT TMC *****END OF FILE****/


