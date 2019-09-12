/**
  ******************************************************************************
  * @file    FSMC.h
  * @author  TMC  Team
  * @version V3.1.0
  * @date    06/19/2009
  * @brief   This file contains all the functions prototypes for the TIM firmware 
  *          library.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FSMC_H
#define __FSMC_H

#ifdef __cplusplus
 extern "C" {
#endif

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

/** @defgroup FSMC_Exported_Constants DCMI Exported Constants
  * @{
  */
//typedef enum {WIDTH8 = 0,WIDTH16 = 1} Data_Width;
//typedef enum {SRAM = 0,PSRAM = 1,FLASH = 2} Memory_Type;
//typedef enum {MODEA = 0,MODEB = 1,MODEC = 2,MODED = 3} Access_Mode;
/** 
  * @brief   FSMC Init structure definition
  */  
typedef struct
{
	uint32_t FSMC_ExtMode;	/*!< Extended Mode: Enable LCD_BWTR valid,Disable LCD_BWTR Not valid,This parameter can be a value of @ref FSMC_EXTEND_MODE*/
	
	uint32_t MemoryWrite;	/*!< Memory Write Enable or Disable,This parameter can be a value of @ref FSMC_MEMORY_WRITE*/
	
	uint32_t FSMC_MemoryDataWidth;	/*!< the Data Width of Memory,This parameter can be a value of @ref Data_Width_Mode*/

	uint32_t FSMC_MemoryType;		/*!< FSMC Access Memory Type,This parameter can be a value of @ref MEMORY_TYPE*/

}FSMC_InitTypeDef;	 

/** 
  * @brief   FSMC Timing structure definition
  */  
typedef struct
{
	uint32_t FSMC_AccMode;   /*!< Access Mode: FSMC Access Mode,This parameter can be a value of @ref FSMC_AccMode*/         
	
	uint32_t FSMC_BusTurn;	/*!<Bus Turnaround stage duration*/  
	
	uint32_t FSMC_DATAST;	/*!<data phase  duration*/ 			
	
	uint32_t FSMC_ADDSET;	/*!<Address Setup  duration*/ 				
	
}FSMC_TimingTypeDef;


/** @defgroup FSMC_AccMode FSMC AccMode
  * @{
  */ 		
#define FSMC_ACC_MODE     		(0U)  

/**
  * @}
  */

/** @defgroup FSMC_EXTEND_MODE FSMC EXTEND MODE
  * @{
  */ 
#define FSMC_EXTEND_MODE_ENABLE      		(1U<<14)   		
#define FSMC_EXTEND_MODE_DISABLE       		(0U)  

/**
  * @}
  */

/** @defgroup FSMC_MEMORY_WRITE FSMC MEMORY WRITE
  * @{
  */ 
#define FSMC_MEMORY_WRITE_ENABLE      		(1U<<12)   		
#define FSMC_MEMORY_WRITE_DISABLE        	(0U)  

/**
  * @}
  */

/** @defgroup Data_Width_Mode Data Width Mode
  * @{
  */ 
#define FSMC_DATA_WIDTH_16BIT       (0x10U)   		
#define FSMC_DATA_WIDTH_8BIT        (0U) 

/**
  * @}
  */

/** @defgroup MEMORY_TYPE MEMORY TYPE
  * @{
  */ 
#define FSMC_MEMORY_TYPE_SRAM      (0x00U)   		
 
/**
  * @}
  */

/** @defgroup RLSNWE_MSK RLSNWE MSK
  * @{
  */ 
#define   FSMC_RLSNWE_MSK_ENABLE    (0x01U)   		
#define   FSMC_RLSNWE_MSK_DISABLE   (0x00U)   
/**
  * @}
  */

/** @defgroup FSMC_Private_Macros FSMC Private Macros
  * @{
  */
#define IS_FSMC_EXTEND_MODE(x)			((x == FSMC_EXTEND_MODE_ENABLE)||(x == FSMC_EXTEND_MODE_DISABLE))
#define IS_FSMC_MEMORY_WRITE_MODE(x)	((x == FSMC_MEMORY_WRITE_ENABLE)||(x == FSMC_MEMORY_WRITE_DISABLE))
#define IS_FSMC_DATA_WIDTH_MODE(x)		((x == FSMC_DATA_WIDTH_16BIT)||(x == FSMC_DATA_WIDTH_8BIT))
#define IS_FSMC_MEMORY_TYPE_MODE(x)		(x == FSMC_MEMORY_TYPE_SRAM)
#define IS_FSMC_ACC_MODE(x)				(x == FSMC_ACC_MODE)
#define IS_FSMC_BUS_TURNS(x)			(x<=0x0FU)
#define IS_FSMC_DATA_STR(x)				(x<=0xFFU)
#define IS_FSMC_ADD_SET(x)				(x<=0x0FU)
#define IS_FSMC_MSK(x)					((x==FSMC_RLSNWE_MSK_ENABLE)||(x==FSMC_RLSNWE_MSK_DISABLE))

/**
  * @}
  */  
/**
  * @}
  */ 
/** @addtogroup FSMC_exported_function FSMC exported function
  * @{
  */
void FSMC_StructInit(FSMC_InitTypeDef * FSMC_InitStruct);
void FSMC_Init(FSMC_InitTypeDef * FSMC_InitStruct);
void FSMC_ConfigReadModeDurationTimes(FSMC_TimingTypeDef * FSMC_TimingStruct);
void FSMC_ConfigWriteModeDurationTimes(FSMC_TimingTypeDef * FSMC_TimingStruct);
void FSMC_ConfigRLSNWE(uint32_t Msk);
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

/************************ (C) COPYRIGHT TMC *****END OF FILE***********************/

