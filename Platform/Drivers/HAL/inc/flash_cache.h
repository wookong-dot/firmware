/**
  ******************************************************************************
  * @file    FLASH_CACHE.h
  * @author  TMC  Team
  * @version V3.1.0
  * @date    06/19/2009
  * @brief   This file contains all the functions prototypes for the FLASH_CACHE firmware 
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
#ifndef __FLASH_CACHE_H
#define __FLASH_CACHE_H

#ifdef __cplusplus
 extern "C" {
#endif
/** @addtogroup THM36x2
  * @{
  */
/** @addtogroup THM36x2_HAL_Driver
  * @{
  */
/** @defgroup FLASH_CACHE
  * @brief FLASH_CACHE HAL modules driver 
  * @{
  */ 
/** @defgroup FLASH_CACHE_Exported_Types HAL FLASH CACHE Exported Types
  * @{
  */ 
typedef enum {IDLE = 0, BUSY = !IDLE} CacheStatus;
/** 
  * @brief  Flash cache Init structure definition
  * @note   This sturcture is used with  Flash cache  
  */
typedef struct
{
	uint32_t ASSOCCFG;
	uint32_t LINESIZE;
	uint32_t CRAMSIZE;
} Flash_Cache_InitTypeDef; 	

/** @defgroup FLASH_cache_assoccfg FLASH cache assoccfg
  * @brief   
  * @{
  */ 
#define FLASH_CACHE_ASSOCCFG_1_WAY				(0x00000000UL)
#define FLASH_CACHE_ASSOCCFG_2_WAY				(0x00000100UL)
#define FLASH_CACHE_ASSOCCFG_4_WAY				(0x00000200UL)
/**
  * @}
  */

/** @defgroup FLASH_cache_line_size FLASH cache line size
  * @brief   
  * @{
  */ 
#define FLASH_CACHE_LINESIZE_8_BYTE      		(0x00000000UL)
#define FLASH_CACHE_LINESIZE_16_BYTE    		(0x00000010UL)
#define FLASH_CACHE_LINESIZE_32_BYTE      		(0x00000020UL) 

/**
  * @}
  */

/** @defgroup FLASH_cache_cram_size FLASH cache cram size
  * @brief   
  * @{
  */ 
#define FLASH_CACHE_CRAM_SIZE_4K				(0x00000000UL)
/**
  * @}
  */
  
/** @defgroup FLASH_cache_flag FLASH cache flag
  * @brief   
  * @{
  */ 
#define FLASH_CACHE_Flag_ICACHE					(0x00000002UL)
#define FLASH_CACHE_Flag_DCACHE					(0x00000001UL)

/**
  * @}
  */
  
/** @addtogroup FLASH_CACHE_Exported_Function 
  * @{
  */ 
void Flash_CacheRest(void);
void Flash_IcacheStructInit(Flash_Cache_InitTypeDef* hicache);
void Flash_DcacheStructInit(Flash_Cache_InitTypeDef* hdcache);
void Flash_IcacheInit(Flash_Cache_TypeDef *Flash_Cache, Flash_Cache_InitTypeDef *hicache);
void Flash_DcacheInit(Flash_Cache_TypeDef *Flash_Cache,Flash_Cache_InitTypeDef* hdcache);
void Flash_IcacheDeInit(Flash_Cache_TypeDef *Flash_Cache);
void Flash_DcacheDeInit(Flash_Cache_TypeDef *Flash_Cache);
void Flash_IcacheCmd(Flash_Cache_TypeDef *Flash_Cache,FunctionalState NewState);
void Flash_DcacheCmd(Flash_Cache_TypeDef *Flash_Cache,FunctionalState NewState);
void Flash_IcacheRest(Flash_Cache_TypeDef *Flash_Cache,FunctionalState NewState);
void Flash_DcacheRest(Flash_Cache_TypeDef *Flash_Cache,FunctionalState NewState);
void Flash_DcacheConfigAddress(Flash_Cache_TypeDef *Flash_Cache,uint32_t StartAddress,uint32_t EndAddress);
void Flash_IcacheConfigAddress(Flash_Cache_TypeDef *Flash_Cache,uint32_t StartAddress,uint32_t EndAddress);
CacheStatus Flash_CacheGetStatus(Flash_Cache_TypeDef *Flash_Cache,uint32_t CacheFlag);
FlagStatus Flash_GetDcacheEnable(Flash_Cache_TypeDef *Flash_Cache);
FlagStatus Flash_GetIcacheEnable(Flash_Cache_TypeDef *Flash_Cache);
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

#endif /* __Thm36x2_TMC_FLASH_CACHE_H */  


