/**
  ******************************************************************************
  * @file    XDES.h
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
#ifndef _SM4_H
#define _SM4_H

#ifdef __cplusplus
 extern "C" {
#endif
/**
* @brief  SM4 ECB none Security
* @param[in] pbKey: key for encryption/decryption
* @param[in] pbDataInput: encryption/decryption data
* @param[Out] pbDataOutput: Return data	 
* @param[in] bmode 0x0A EncryptEcb
*			 bmode 0x05 Decrypt
* @retval none
* @note	none
*/ 
void Sm4_ECB(uint8_t *pbKey, uint8_t *pbDataInput,uint8_t *pbDataOutput, uint8_t bmode);
/**
* @brief  SM4 ECB none Security
* @param[in] pbKey: key for encryption/decryption
* @param[in] pbDataInput: encryption/decryption data
* @param[Out] pbDataOutput: Return data	 
* @param[Out] iv: iv Value	
* @param[in] bmode 0x0A EncryptEcb
*			 bmode 0x05 Decrypt
* @retval none
* @note	none
*/ 
void Sm4_CBC(uint8_t *pbKey, uint8_t *pbDataInput,uint8_t *pbDataOutput, uint8_t *iv,uint8_t bmode);
/**
* @brief  SM4 ECB Security
* @param[in] pbKey: key for encryption/decryption
* @param[in] pbDataInput: encryption/decryption data
* @param[Out] pbDataOutput: Return data	 
* @param[in] bmode 0x0A EncryptEcb
*			 bmode 0x05 Decrypt
* @retval uint16_t: 0xAAAA Success
					0x5555 error
* @note	none
*/
uint16_t Sm4_SecurityECB(uint8_t *pbKey, uint8_t *pbDataInput,uint8_t *pbDataOutput, uint8_t bmode);

/**
* @brief  SM4 CBC Security
* @param[in] pbKey: key for encryption/decryption
* @param[in] pbDataInput: encryption/decryption data
* @param[Out] pbDataOutput: Return data	 
* @param[in] bmode 0x0A EncryptEcb
*			 bmode 0x05 Decrypt
* @retval uint16_t: 0xAAAA Success
					0x5555 error
* @note	none
*/
uint16_t Sm4_SecurityCBC(uint8_t *pbKey, uint8_t *pbDataInput,uint8_t *pbDataOutput, uint8_t *iv,uint8_t bmode);

void Sm4EnableClock(void);
void Sm4DisableClock(void);
void Sm4ConfigKey(uint8_t *Key);
void Sm4Encrypt(uint8_t *plaintext,uint8_t *ciphertextBuf);
void Sm4Decrypt(uint8_t *ciphertext,uint8_t *plaintextBuf);
#ifdef __cplusplus
}
#endif
#endif /* __TMC_USART_H */
/**
  * @}
  */
/**
  * @}
  */
/**
  * @}
  */

