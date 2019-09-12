/**
  ******************************************************************************
  * @file    tmc_uart.c
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

#ifndef __TMC_AES_H
#define __TMC_AES_H

/** @addtogroup TMC_Driver
  * @{
  */
/** @defgroup TMC_AES
  * @{
  */

/**
* @brief  AES ECB 128/192/256 encryption/decryption
* @param[in] pbKey: key for encryption/decryption
* @param[in] pbDataInput: encryption/decryption data
* @param[in] bmode
* 			bmode if bit0:1 bit2:1 AES decryption
*			bmode if bit1:1 bit3:1 AES encryption
*			bmode if bit5:1 bit7:1 AES KEY is 128Bit
*			bmode if bit4:1 bit6:1 AES KEY is 192Bit
*			bmode if bit4:1 bit5:1 AES KEY is 256Bit
* @retval none
* @note	none
*/ 
void AES_ECB(uint8_t *pbKey, uint8_t *pbDataInput,uint32_t *pbDataOutput, uint32_t bmode);


/**
* @brief  AES ECB 128/192/256 encryption/decryption
* @param[in] pbKey: key for encryption/decryption
* @param[in] pbDataInput: encryption/decryption data
* @param[in] bmode
* 			bmode if bit0:1 bit2:1 AES decryption
*			bmode if bit1:1 bit3:1 AES encryption
*			bmode if bit5:1 bit7:1 AES KEY is 128Bit
*			bmode if bit4:1 bit6:1 AES KEY is 192Bit
*			bmode if bit4:1 bit5:1 AES KEY is 256Bit
* @retval none
* @note	none
*/ 
uint16_t AES_SecurityECB(uint8_t *pbKey, uint8_t *pbDataInput,uint32_t *pbDataOutput, uint32_t bmode);
#endif
/**
  * @}
  */
/**
  * @}
  */

