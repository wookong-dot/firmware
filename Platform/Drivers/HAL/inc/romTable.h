/**
  ******************************************************************************
  * @file    THK88_demo_CCID_7816/ALGRITHM/romtable.h
  * @author  Zhou Min
  * @version V1.0
  * @date    30/11/2016
  * @brief   This file provides all the algorithm functions.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, TMC SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2016 TMC</center></h2>
  */

/** @addtogroup THK88_demo_CCID_7816
  * @{
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ROMTABLE_H__
#define __ROMTABLE_H__
/* Exported struct ---------------------------------------------------------- */
typedef struct{
	unsigned char* p;
	unsigned short length;
}BigNum_t;

/* SM3 */
typedef struct
{
	uint32_t blocks;
	uint8_t result[32];	
	uint32_t buffer[16];
	uint32_t length;	
}SM3_Context_t;
/* SM3 end */

/* SHA1 */
//typedef struct
//{
//	uint16_t blocks;
//	uint8_t result[20];
//	uint32_t buffer[16];
//	uint16_t length;
//}SHA1_Context_t;
#define  SHA1_Context_t  SM3_Context_t
/* SHA1 end */

/* SHA256 */
//typedef struct
//{
//	uint16_t blocks;
//	uint8_t result[32];
//	uint32_t buffer[16];
//	uint16_t length;
//}SHA256_Context_t;
#define  SHA256_Context_t  SM3_Context_t
#define  SHA1_Context_t SM3_Context_t
/* SHA256 end */

/* RSA */
typedef struct
{
    BigNum_t N;
    BigNum_t E;
}RSAPubKey_t;

typedef struct
{
    BigNum_t N;
    BigNum_t D;
}RSAPrivKey_t;

typedef struct
{
    BigNum_t P;
    BigNum_t Q;
    BigNum_t DP;
    BigNum_t DQ;
    BigNum_t QInv;
}RSAPrivKeyCrt_t;

typedef struct {
    RSAPrivKey_t PriKey;
    RSAPrivKeyCrt_t PriCrtKey;
}RSAKeyGenOut_t;

/* PKE defined */
typedef struct{
	unsigned char* pucN;
	unsigned char* pucD;
	unsigned char* pucP;
	unsigned char* pucQ;
	unsigned char* pucDp;
	unsigned char* pucDq;
	unsigned char* pucIq;
}RSAKGOut_t;
/* RSA end */

/* SM2 */
typedef struct
{
	uint8_t isSender;
	uint8_t *pbThisPriKey;
	uint8_t *pbThisTempPriKey;
	uint8_t *pbThisTempPubKey;
	uint8_t *pbThisZ;
	uint8_t *pbOtherPubKey;
	uint8_t *pbOtherTempPubKey;
	uint8_t *pbOtherZ;
}SM2KeyExchangeParam_t;

typedef struct{
	unsigned char* pucDA;
	unsigned char* pucRDA;
	unsigned char* pucRPA;
	unsigned char* pucZA;
	unsigned char* pucPB;
	unsigned char* pucRPB;
	unsigned char* pucZB;
}SM2KEIn_t;
typedef struct
{
	uint8_t *pbSymKey;
	uint8_t *pbThisVerifyData;
	uint8_t *pbOtherVerifyData;
}SM2KeyExchangeOut_t;
/* SM2 end */

/* ECC */
typedef struct{
	BigNum_t* pbnP;
	BigNum_t* pbnN;
	BigNum_t* pbnA;
	BigNum_t* pbnB;
	BigNum_t* pbnGx;
	BigNum_t* pbnGy;
}ECC_Domain_t;
/* ECC end */

/* Function pointer ---------------------------------------------------------*/
/* RSA */
typedef uint16_t (* ptmcRSAEncrypt)(BigNum_t *pResult, BigNum_t *pMessage,RSAPubKey_t *pPubKey);
typedef uint16_t (* ptmcRSADecrypt)(BigNum_t *pResult, BigNum_t *pMessage, RSAPrivKey_t *pPrivKey);
typedef uint16_t (* ptmcRSADecrypt_SU)(BigNum_t *pResult, BigNum_t *pMessage, RSAPrivKey_t *pPrivKey, BigNum_t *pE);
typedef uint16_t (* ptmcRSAKeyPairGen)(RSAKeyGenOut_t *pKey,BigNum_t *pE, uint16_t usBitLenKey, uint8_t mode);
typedef uint16_t (* ptmcRSADecryptCrt_SU)(BigNum_t *pResult,BigNum_t *pMessage, RSAPrivKeyCrt_t *pPrivKeyCrt,BigNum_t *pE);
typedef uint16_t (* ptmcRSACrtGetE)(BigNum_t *pE,  BigNum_t *pP,BigNum_t *pQ, BigNum_t *pDP, BigNum_t *pDQ);
/* Pke interface */
typedef uint16_t (* pPkeRSASec_Keygen)(RSAKGOut_t* prkOut, BigNum_t* pbnE, uint16_t usCLenP, uint16_t usCLenQ, uint8_t ucMode);

/* SM2 */
typedef uint16_t (* ptmcSM2GetHashData)(uint8_t *pbHashData, uint8_t *pbPubKey, BigNum_t *pID, BigNum_t *pMessage);
typedef uint16_t (* ptmcSM2Sign)(uint8_t *pbSignature, uint8_t *pbPriKey, uint8_t *pbInput);
typedef uint16_t (* ptmcSM2Verify)(uint8_t *pbPubKey, uint8_t *pbInput, uint8_t *pbSignature);
typedef uint16_t (* ptmcSM2Encrypt)(BigNum_t *pCrypto, BigNum_t *pMessage, uint8_t *pbPublicKey);
typedef uint16_t (* ptmcSM2Decrypt)(BigNum_t *pMessage, BigNum_t *pCrypto, uint8_t *pbPrivateKey);
typedef uint16_t (* ptmcSM2KeyPairGen)(uint8_t *pbPubkey, uint8_t *pbPrikey, uint8_t mode);
typedef uint16_t (* ptmcSM2ZGen)(uint8_t *pbHashData, uint8_t *pbPubKey, BigNum_t *pID);
typedef uint16_t (* ptmcSM2KeyExchange)(SM2KeyExchangeOut_t *pOut, SM2KeyExchangeParam_t *pParam,uint8_t symKeyLen);

/* Pke interface */
typedef uint16_t  (* pPkeSM2Sec_PtChk)(uint8_t * pucPt);
/* ECC */	
typedef uint16_t (* ptmcECCParamCheck)(ECC_Domain_t *domain);
typedef uint16_t (* ptmcECCPointAdd)(BigNum_t *output, BigNum_t *point1, BigNum_t *point2, ECC_Domain_t *domain);
typedef uint16_t (* ptmcECCPointMul)(BigNum_t *output, BigNum_t *point, BigNum_t *K, ECC_Domain_t *domain);
typedef uint16_t (* ptmcECCKeyGen)(BigNum_t *publicKey, BigNum_t *privateKey, ECC_Domain_t *domain, uint8_t mode);
typedef uint16_t (* ptmcECCSign)(BigNum_t *output, BigNum_t* E, BigNum_t *privateKey, ECC_Domain_t *domain);
typedef uint16_t (* ptmcECCVerify)(BigNum_t *E, BigNum_t *publicKey, BigNum_t *signature, ECC_Domain_t *domain);

/* HASH */
typedef void 		(* ptmcSM3Init)(SM3_Context_t *c);
typedef void 		(* ptmcSM3Update)(SM3_Context_t *c,const void *data,uint32_t length);
typedef uint16_t 	(* ptmcSM3Final)(uint8_t *output,SM3_Context_t *c);
typedef void 		(* ptmcSHA1Init)(SHA1_Context_t *c);
typedef void 		(* ptmcSHA1Update)(SHA1_Context_t *c,const void *data,uint32_t length);
typedef uint16_t 	(* ptmcSHA1Final)(uint8_t *output,SHA1_Context_t *c);
typedef void 		(* ptmcSHA256Init)(SHA256_Context_t *c);
typedef void 		(* ptmcSHA256Update)(SHA256_Context_t *c,const void *data,uint32_t length);
typedef uint16_t 	(* ptmcSHA256Final)(uint8_t *output,SHA256_Context_t *c);



/*-------------------------------------SEC DEPARTMENT API------------------------------*/
/* SM2 */
typedef	void 	 (* pPkeSM2Sec_GetVer)(unsigned char* pucVer);
typedef	uint16_t (* pPkeSM2Sec_Enc)(BigNum_t* pbnCpr, BigNum_t* pbnMsg, unsigned char *pucPubK);
typedef	uint16_t (* pPkeSM2Sec_Dec)(BigNum_t* pbnMsg, BigNum_t* pbnCpr, unsigned char *pucPriK);
typedef	uint16_t (* pPkeSM2Sec_Sign)(unsigned char* pucSign, unsigned char *pucE, unsigned char *pucPriK);
typedef	uint16_t (* pPkeSM2Sec_Verify)(unsigned char *pucSign, unsigned char *pucE, unsigned char *pucPubK);
typedef	uint16_t (* pPkeSM2Sec_KeyExc)(unsigned char* pucKa, unsigned char* pucS1, unsigned char* pucSa, SM2KEIn_t* pskIn, unsigned char ucTag, unsigned char ucCLenK);
typedef	uint16_t (* pPkeSM2Sec_ZGen)(unsigned char* pucZ, BigNum_t* pbnID, unsigned char* pucPa);
typedef	uint16_t (* pPkeSM2Sec_EGen)(unsigned char* pucE, BigNum_t* pbnID, BigNum_t* pbnMsg, unsigned char* pucPa);
typedef	uint16_t (* pPkeSM2Sec_Keygen)(unsigned char *pucPubK, unsigned char *pucPriK, unsigned char ucMode);
typedef	uint16_t (* pPkeSM2Sec_PtChk)(unsigned char* pucPt);

/* ECC */
typedef	void 	 (* pPkeECCSec_GetVer)(unsigned char* pucVer);
typedef	uint16_t (* pPkeECCSec_ParaChk)(ECC_Domain_t* pedDom);
typedef	uint16_t (* pPkeECCSec_KeyGen)(BigNum_t* pbnPubK, BigNum_t* pbnPriK, ECC_Domain_t* pedDom, unsigned char ucMode);
typedef	uint16_t (* pPkeECCSec_ECDSASign)(BigNum_t* pbnSign, BigNum_t* pbnHash, BigNum_t* pbnPriKey, ECC_Domain_t* pedDom);
typedef	uint16_t (* pPkeECCSec_ECDSAVerify)(BigNum_t* pbnSign, BigNum_t* pbnHash, BigNum_t* pbnPubKey, ECC_Domain_t* pedDom);
typedef	uint16_t (* pPkeECCSec_PtAdd)(BigNum_t* pbnPtOut, BigNum_t* pbnPt1, BigNum_t* pbnPt2, ECC_Domain_t* pedDom);
typedef	uint16_t (* pPkeECCSec_PtMul)(BigNum_t* pbnPtOut, BigNum_t* pbnPtIn, BigNum_t* pbnK, ECC_Domain_t* pedDom);

/* RSA */
typedef	void 	 (* pPkeRSASec_GetVer)(unsigned char* pucVer);
typedef	uint16_t (* pPkeRSASec_Enc)(BigNum_t* pbnC, BigNum_t* pbnM, BigNum_t* pbnN, BigNum_t*pbnE);
typedef	uint16_t (* pPkeRSASec_Dec)(BigNum_t* pbnM, BigNum_t* pbnC, BigNum_t* pbnN, BigNum_t*pbnD);
typedef	uint16_t (* pPkeRSASec_DecCRT)(BigNum_t* pbnM, BigNum_t* pbnC, BigNum_t* pbnP, BigNum_t*pbnQ, BigNum_t* pbnDp, BigNum_t* pbnDq, BigNum_t* pbnIq, BigNum_t* pbnE);
typedef	uint16_t (* pPkeRSASec_DecSTD)(BigNum_t* pbnM, BigNum_t* pbnC, BigNum_t* pbnN, BigNum_t*pbnD, BigNum_t* pbnE);
typedef	uint16_t (* pPkeRSASec_Keygen)(RSAKGOut_t* prkOut, BigNum_t* pbnE,uint16_t usCLenP, uint16_t usCLenQ, unsigned char ucMode);
typedef	uint16_t (* pPkeRSASec_GetE)(BigNum_t* pbnE, BigNum_t* pbnP, BigNum_t* pbnQ, BigNum_t* pbnDp, BigNum_t* pbnDq);


/* HASH */
typedef	void 	 (* pPkeHash_GetVer)(unsigned char* pucVer);
typedef	void 	 (* pPkeSHA1_Update)(unsigned char* pucOut, unsigned char* pucIn,unsigned char* pucLastBlk, unsigned char ucInit);
typedef	uint16_t (* pPkeSHA1_Final)(unsigned char* pucOut, unsigned char* pucIn, unsigned char* pucLastBlk, uint16_t usBlkDone, uint16_t usBitLen);
typedef	uint16_t (* pPkeSHA1_Compute)(unsigned char* pucOut, unsigned char* pucIn, uint16_t usBitLen);
typedef	void 	 (* pPkeSHA256_Update)(unsigned char* pucOut, unsigned char* pucIn,unsigned char* pucLastBlk, unsigned char ucInit);
typedef	uint16_t (* pPkeSHA256_Final)(unsigned char* pucOut, unsigned char* pucIn, unsigned char* pucLastBlk, uint16_t usBlkDone, uint16_t usBitLen);
typedef	uint16_t (* pPkeSHA256_Compute)(unsigned char* pucOut, unsigned char* pucIn, uint16_t usBitLen);
typedef	void 	 (* pPkeSM3_GetVer)(unsigned char* pucVer); 
typedef	void 	 (* pPkeSM3_Update)(unsigned char* pucOut, unsigned char* pucIn,unsigned char* pucLastBlk, unsigned char ucInit);
typedef	uint16_t (* pPkeSM3_Final)(unsigned char* pucOut, unsigned char* pucIn, unsigned char* pucLastBlk, uint16_t usBlkDone, uint16_t usBitLen);
typedef	uint16_t (* pPkeSM3_Compute)(unsigned char* pucOut, unsigned char* pucIn, uint16_t usBitLen);

/* Get version */
typedef void (* ptmcPkeGetVer)(uint8_t* pucVer);

/* PKE basic api */
typedef uint8_t (* pPkeGetRandomNum)(uint8_t *buf,uint16_t len);
typedef void (* pGetVer)(uint8_t* pucVer);
typedef void (*	pPkeCfg)(uint8_t eccA,uint8_t eccZ1,uint8_t mulCfg);
typedef void (*pInputRamMaskHandler)(unsigned char * pucMask);
typedef void (*pInputFlashWriteMaskHandler)(unsigned long StartAdder,unsigned long EndAdder,unsigned char * pucMask);
typedef void (*pEnableFlashWriteMaskHandler)(unsigned char Mode);
typedef void (*pInputFlashReadMaskHandler)(unsigned long StartAdder,unsigned long EndAdder,unsigned char * pucMask);
typedef void (*pEnableFlashReadMaskHandler)(unsigned char Mode);
typedef void (*pInputRamWriteMaskHandler)(unsigned long StartAdder,unsigned long EndAdder,unsigned char * pucMask);
typedef void (*pEnableRamWriteMaskHandler)(unsigned char Mode);
typedef void (*pInputRamReadMaskHandler)(unsigned long StartAdder,unsigned long EndAdder,unsigned char * pucMask);
typedef void (*pEnableRamReadMaskHandler)(unsigned char Mode);
////for flash test
//#define RSAFUNCADDR				0x00030000
//#define SM2FUNCADDR				0x00030018
//#define	ECCFUNCADDR				0x00030038
//#define	HASHFUNCADDR			0x00030050
//#define PKERSAFUNCADDR			0x00030074

/* Address */
#define ROM_START_ADDRESS		0x1A000000
#define RSAFUNCADDR				0x1A000000
#define SM2FUNCADDR				0x1A000018
#define	ECCFUNCADDR				0x1A000038
#define	HASHFUNCADDR			0x1A000050
#define PKERSAFUNCADDR			0x1A000074
#define PKESM2FUNCADDR		    0x1A000090
#define PKEECCFUNCADDR		    0x1A0000b8
#define PKEHASHFUNCADDR		    0x1A0000d4
#define PKEBASEAPIADDR			0x1A000100

/* RSA */
#define			tmcRSAEncrypt 				((ptmcRSAEncrypt)(*(uint32_t *)(RSAFUNCADDR + 0)))
#define			tmcRSADecrypt 				((ptmcRSADecrypt)(*(uint32_t *)(RSAFUNCADDR + 4)))
#define			tmcRSADecrypt_SU 			((ptmcRSADecrypt_SU)(*(uint32_t *)(RSAFUNCADDR + 8)))
#define			tmcRSAKeyPairGen 			((ptmcRSAKeyPairGen)(*(uint32_t *)(RSAFUNCADDR + 0xC)))
#define			tmcRSADecryptCrt_SU 		((ptmcRSADecryptCrt_SU)(*(uint32_t *)(RSAFUNCADDR + 0x10)))
#define			tmcRSACrtGetE 				((ptmcRSACrtGetE)(*(uint32_t *)(RSAFUNCADDR + 0x14)))
/* Pke defined */
#define 		PkeRSASec_Keygen			((pPkeRSASec_Keygen)(*(uint32_t *)(PKERSAFUNCADDR + 0x0C)))
/* SM2 */
#define			tmcSM2GetHashData 			((ptmcSM2GetHashData)(*(uint32_t *)(SM2FUNCADDR + 0)))
#define			tmcSM2Sign 					((ptmcSM2Sign)(*(uint32_t *)(SM2FUNCADDR + 4)))
#define			tmcSM2Verify 				((ptmcSM2Verify)(*(uint32_t *)(SM2FUNCADDR + 8)))
#define			tmcSM2Encrypt 				((ptmcSM2Encrypt)(*(uint32_t *)(SM2FUNCADDR + 0x0C)))
#define			tmcSM2Decrypt 				((ptmcSM2Decrypt)(*(uint32_t *)(SM2FUNCADDR + 0x10)))
#define			tmcSM2KeyPairGen 			((ptmcSM2KeyPairGen)(*(uint32_t *)(SM2FUNCADDR + 0x14)))
#define			tmcSM2ZGen 					((ptmcSM2ZGen)(*(uint32_t *)(SM2FUNCADDR + 0x18)))
#define			tmcSM2KeyExchange 			((ptmcSM2KeyExchange)(*(uint32_t *)(SM2FUNCADDR + 0x1C)))
/* Pke defined */
//#define			PkeSM2Sec_PtChk				((pPkeSM2Sec_PtChk)(*((uint32_t *)(PKESM2FUNCADDR + 0))))
/* ECC */
#define			tmcECCParamCheck 			((ptmcECCParamCheck)(*(uint32_t *)(ECCFUNCADDR + 0)))
#define			tmcECCPointAdd 				((ptmcECCPointAdd)(*(uint32_t *)(ECCFUNCADDR + 4)))
#define			tmcECCPointMul 				((ptmcECCPointMul)(*(uint32_t *)(ECCFUNCADDR + 8)))
#define			tmcECCKeyGen 				((ptmcECCKeyGen)(*(uint32_t *)(ECCFUNCADDR + 0x0C)))
#define			tmcECCSign 					((ptmcECCSign)(*(uint32_t *)(ECCFUNCADDR + 0x10)))
#define			tmcECCVerify 				((ptmcECCVerify)(*(uint32_t *)(ECCFUNCADDR + 0x14)))

/* Hash */
#define			tmcSM3Init 					((ptmcSM3Init)(*(uint32_t *)(HASHFUNCADDR + 0)))
#define			tmcSM3Update 				((ptmcSM3Update)(*(uint32_t *)(HASHFUNCADDR + 4)))
#define			tmcSM3Final 				((ptmcSM3Final)(*(uint32_t *)(HASHFUNCADDR + 8)))
#define			tmcSHA1Init 				((ptmcSHA1Init)(*(uint32_t *)(HASHFUNCADDR + 0xC)))
#define			tmcSHA1Update 				((ptmcSHA1Update)(*(uint32_t *)(HASHFUNCADDR + 0x10)))
#define			tmcSHA1Final 				((ptmcSHA1Final)(*(uint32_t *)(HASHFUNCADDR + 0x14))) 
#define			tmcSHA256Init 				((ptmcSHA256Init)(*(uint32_t *)(HASHFUNCADDR + 0x18)))
#define			tmcSHA256Update 			((ptmcSHA256Update)(*(uint32_t *)(HASHFUNCADDR + 0x1C)))
#define			tmcSHA256Final 				((ptmcSHA256Final)(*(uint32_t *)(HASHFUNCADDR + 0x20)))

#define         PkeSM2Sec_PtChk  			((pPkeSM2Sec_PtChk)(*(uint32_t *)(PKESM2FUNCADDR + 0)))
#define         PkeSM2Sec_EGen  			((pPkeSM2Sec_EGen)(*(uint32_t *)(PKESM2FUNCADDR + 4)))
#define         PkeSM2Sec_Sign  			((pPkeSM2Sec_Sign)(*(uint32_t *)(PKESM2FUNCADDR + 8)))
#define         PkeSM2Sec_Verify  			((pPkeSM2Sec_Verify)(*(uint32_t *)(PKESM2FUNCADDR + 0x0C)))
#define         PkeSM2Sec_Enc  				((pPkeSM2Sec_Enc)(*(uint32_t *)(PKESM2FUNCADDR + 0x10)))
#define         PkeSM2Sec_Dec  				((pPkeSM2Sec_Dec)(*(uint32_t *)(PKESM2FUNCADDR + 0x14)))
#define         PkeSM2Sec_Keygen  			((pPkeSM2Sec_Keygen)(*(uint32_t *)(PKESM2FUNCADDR + 0x18)))
#define         PkeSM2Sec_ZGen  			((pPkeSM2Sec_ZGen)(*(uint32_t *)(PKESM2FUNCADDR + 0x1C)))
#define         PkeSM2Sec_KeyExc  			((pPkeSM2Sec_KeyExc)(*(uint32_t *)(PKESM2FUNCADDR + 0x20)))
#define         PkeSM2Sec_GetVer  			((pPkeSM2Sec_GetVer)(*(uint32_t *)(PKESM2FUNCADDR + 24)))
/*-------------------------------------SEC DEPARTMENT API------------------------------*/

#define         PkeECCSec_ParaChk  			((pPkeECCSec_ParaChk)(*(uint32_t *)(PKEECCFUNCADDR + 0)))
#define         PkeECCSec_PtAdd  			((pPkeECCSec_PtAdd)(*(uint32_t *)(PKEECCFUNCADDR + 4)))
#define         PkeECCSec_PtMul				((pPkeECCSec_PtMul)(*(uint32_t *)(PKEECCFUNCADDR + 8)))
#define         PkeECCSec_KeyGen			((pPkeECCSec_KeyGen)(*(uint32_t *)(PKEECCFUNCADDR + 0x0c)))
#define         PkeECCSec_ECDSASign			((pPkeECCSec_ECDSASign)(*(uint32_t *)(PKEECCFUNCADDR + 0x10)))
#define         PkeECCSec_ECDSAVerify		((pPkeECCSec_ECDSAVerify)(*(uint32_t *)(PKEECCFUNCADDR + 0x14)))
#define         PkeECCSec_GetVer			((pPkeECCSec_GetVer)(*(uint32_t *)(PKEECCFUNCADDR + 0x18)))

#define         PkeRSASec_Enc  				((pPkeRSASec_Enc)(*(uint32_t *)(PKERSAFUNCADDR + 0)))
#define         PkeRSASec_Dec  				((pPkeRSASec_Dec)(*(uint32_t *)(PKERSAFUNCADDR + 4)))
#define         PkeRSASec_DecSTD			((pPkeRSASec_DecSTD)(*(uint32_t *)(PKERSAFUNCADDR + 8)))
#define         PkeRSASec_Keygen			((pPkeRSASec_Keygen)(*(uint32_t *)(PKERSAFUNCADDR + 0x0C)))
#define         PkeRSASec_DecCRT			((pPkeRSASec_DecCRT)(*(uint32_t *)(PKERSAFUNCADDR + 0x0C)))
#define 		PkeRSASec_GetE				((pPkeRSASec_DecCRT)(*(uint32_t *)(PKERSAFUNCADDR + 0x10)))
#define			PkeRSASec_GetVer			((pPkeRSASec_GetVer)(*(uint32_t *)(PKERSAFUNCADDR + 0x14)))

#define         PkeSM3_Update  				((pPkeSM3_Update)(*(uint32_t *)(PKEHASHFUNCADDR + 0)))
#define         PkeSM3_Final				((pPkeSM3_Final)(*(uint32_t *)(PKEHASHFUNCADDR + 4)))
#define			PkeSM3_Compute				((pPkeSM3_Compute)(*(uint32_t *)(PKEHASHFUNCADDR + 8)))
#define         PkeSHA1_Update				((pPkeSHA1_Update)(*(uint32_t *)(PKEHASHFUNCADDR + 0x0C)))
#define         PkeSHA1_Final				((pPkeSHA1_Final)(*(uint32_t *)(PKEHASHFUNCADDR + 0x10)))
#define         PkeSHA1_Compute				((pPkeSHA1_Compute)(*(uint32_t *)(PKEHASHFUNCADDR + 0x14)))
#define         PkeSHA256_Update			((pPkeSHA256_Update)(*(uint32_t *)(PKEHASHFUNCADDR + 0x18)))
#define         PkeSHA256_Final				((pPkeSHA256_Final)(*(uint32_t *)(PKEHASHFUNCADDR + 0x1C)))
#define         PkeSHA256_Compute			((pPkeSHA256_Compute)(*(uint32_t *)(PKEHASHFUNCADDR + 0x20)))
#define         PkeSM3_GetVer				((pPkeSM3_GetVer)(*(uint32_t *)(PKEHASHFUNCADDR + 0x24)))
#define         PkeHash_GetVer				((pPkeSM3_GetVer)(*(uint32_t *)(PKEHASHFUNCADDR + 0x28)))


#define			pkeConfig						((pPkeCfg)(*(uint32_t *)(PKEBASEAPIADDR + 0)))
#define 		pkeGetRandomNum					((pPkeGetRandomNum)(*(uint32_t *)(PKEBASEAPIADDR + 0x04)))
#define 		pkeGetVer						((pGetVer)(*(uint32_t *)(PKEBASEAPIADDR + 0x08)))
#define         pkeInputRamMaskHandler			((pInputRamMaskHandler)(*(uint32_t *)(PKEBASEAPIADDR + 0x0C)))
#define  		pkeInputFlashWriteMask			((pInputFlashWriteMaskHandler)(*(uint32_t *)(PKEBASEAPIADDR + 0x10)))
#define  		pkeEnableFlashWriteMask			((pEnableFlashWriteMaskHandler)(*(uint32_t *)(PKEBASEAPIADDR + 0x14)))
#define  		pkeInputFlashReadMask			((pInputFlashReadMaskHandler)(*(uint32_t *)(PKEBASEAPIADDR + 0x18)))
#define  		pkeEnableFlashReadMask			((pEnableFlashReadMaskHandler)(*(uint32_t *)(PKEBASEAPIADDR + 0x1C)))
#define         PkeInputRamWriteMaskHandler 	((pInputRamWriteMaskHandler)(*(uint32_t *)(PKEBASEAPIADDR + 0x20)))
#define			pkeEnableRamWriteMaskHandler	((pEnableRamWriteMaskHandler)(*(uint32_t *)(PKEBASEAPIADDR + 0x24)))
#define			pkeInputRamReadMaskHandler		((pInputRamReadMaskHandler)(*(uint32_t *)(PKEBASEAPIADDR + 0x28)))
#define 		pkeEnableRamReadMaskHandler		((pEnableRamReadMaskHandler)(*(uint32_t *)(PKEBASEAPIADDR + 0x2C)))


#endif

