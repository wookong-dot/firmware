/**************************************************************************
* File name    :    pxat_define.h
* Function     :    header of define module
* Author       :    xinght
* Date         :    2019/01/09
* Version      :    v1.0
* Description  :
* ModifyRecord :
***************************************************************************/
#ifndef _PXAT_DEFINE_H_
#define _PXAT_DEFINE_H_

/***************************************************************************
* Include Header Files
***************************************************************************/


/**************************************************************************
* Global Macro Definition
***************************************************************************/
#define AVALON_IRQRXBUF_SIZE                0x210
#define AVALON_TXRXBUF_SIZE                 0x210

/*################## TRANSMISSION PROTOCOL LAYER #################*/
#define TPL_MLEN                            10
#define TPLH_LEN                            8
#define TPLH_SYNCH_POS                      0
#define TPLH_SYNCL_POS                      1
#define TPLH_CIPHER_POS                     2
#define TPLH_CTYPE_POS                      3
#define TPLH_PRET_POS                       4
#define TPLH_CRET_POS                       5
#define TPLH_DLENH_POS                      6
#define TPLH_DLENL_POS                      7
#define TPL_DATA_POS                        8

#define SYNCH_BYTE                          0x55
#define SYNCL_BYTE                          0xAA

#define CIPHER_PLAIN                        0x00

#define CTYPE_DIRECT                        0x80
#define CTYPE_MASK                          0x7F

#define CTYPE_SRSIGN                        0x01
#define CTYPE_GETCHALLENGE                  0x60

#define PRET_OK                             0x00
#define PRET_ERR_SYNC                       0xF0
#define PRET_ERR_CIPHER                     0xF1
#define PRET_ERR_PRET_CRET                  0xF2
#define PRET_ERR_CRC                        0xF3
#define PRET_ERR_LEN                        0xF4

#define CRET_OK                             0x00
#define CRET_CTYPE_ERROR                    0x0E

#define CRC16_INITVAL                       (uint16_t)0x0000

/**************************************************************************
* Global Type Definition
***************************************************************************/


/**************************************************************************
* Global Variable Declaration
***************************************************************************/


/**************************************************************************
* Global Function Declaration
***************************************************************************/
#endif  //#ifndef _PXAT_DEFINE_H_
