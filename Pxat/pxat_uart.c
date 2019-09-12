/**************************************************************************
* File name    :    pxat_uart.c
* Function     :    uart module
* Author       :    xinght
* Date         :    2019/03/05
* Version      :    v1.0
* Description  :
* ModifyRecord :
***************************************************************************/
/***************************************************************************
* Include Header Files
***************************************************************************/
#include "config.h"
#include "thm36x2.h"
#include "pxat_include.h"

/**************************************************************************
* Local Macro Definition
***************************************************************************/


/**************************************************************************
* Local Type Definition
***************************************************************************/


/**************************************************************************
* Local static Variable Declaration
***************************************************************************/
static uint16_t rxlen;
static uint8_t ret;

/**************************************************************************
* Global Variable Declaration
***************************************************************************/


/**************************************************************************
* Local Function Declaration
***************************************************************************/
static void avalon_uart_transmit(uint8_t * txbuf, uint16_t len)
{
    uint16_t i;

    for(i = 0; i < len; i++)
    {
        while(!(UART1->STS & UART_FLAG_TXE));
        UART1->TxDATA = txbuf[i];
    }
}

static void avalon_protocol_return(uint8_t * msg, uint8_t pret)
{
    uint16_t crc16val;

    msg[TPLH_SYNCH_POS]= SYNCH_BYTE;
    msg[TPLH_SYNCL_POS]= SYNCL_BYTE;
    msg[TPLH_CIPHER_POS]= CIPHER_PLAIN;
    msg[TPLH_CTYPE_POS] |= CTYPE_DIRECT;
    msg[TPLH_PRET_POS] = pret;
    msg[TPLH_CRET_POS] = CRET_OK;
    msg[TPLH_DLENH_POS] = 0x00;
    msg[TPLH_DLENL_POS] = 0x00;
    crc16val = CRC_CCITT_Kermit(CRC16_INITVAL,msg,TPLH_LEN);
    msg[TPL_DATA_POS] = (uint8_t)(crc16val>>8);
    msg[TPL_DATA_POS+1] = (uint8_t)crc16val;

    avalon_uart_transmit(msg,TPL_MLEN);
}

static uint8_t avalon_protocol_check(uint8_t * msg, uint16_t len)
{
    uint16_t crc16val;

    if(msg[TPLH_CIPHER_POS] != CIPHER_PLAIN)
        return PRET_ERR_CIPHER;
    if((msg[TPLH_PRET_POS] != 0) || (msg[TPLH_CRET_POS] != 0))
        return PRET_ERR_PRET_CRET;
   // crc16val = CRC_CCITT_Kermit(CRC16_INITVAL,msg,len-2);
   // if(crc16val != ((uint16_t)msg[len-2]<<8|msg[len-1]))
   //     return PRET_ERR_CRC;

    return PRET_OK;
}

/**************************************************************************
* Function
***************************************************************************/
void UART1_IRQHandler(void)
{
    uint8_t tmpreg;

    if(UART1->STS & UART_FLAG_RXF)
    {
        tmpreg = UART1->RxDATA;

        if(avalon_irqrxsize == 0)
        {
            if(tmpreg == SYNCH_BYTE)
            {
                avalon_irqrxbuf[avalon_irqrxsize++] = tmpreg;
            }
        }
        else if(avalon_irqrxsize == 1)
        {
            if(tmpreg == SYNCL_BYTE)
            {
                avalon_irqrxbuf[avalon_irqrxsize++] = tmpreg;
            }
            else
            {
                avalon_irqrxsize = 0;
            }
        }
        else
        {
            if(avalon_irqrxsize < AVALON_IRQRXBUF_SIZE)
            {
                avalon_irqrxbuf[avalon_irqrxsize++] = tmpreg;
            }
            if(avalon_irqrxsize == TPLH_LEN)
            {
                rxlen = ((uint16_t)avalon_irqrxbuf[TPLH_DLENH_POS]<<8) | avalon_irqrxbuf[TPLH_DLENL_POS];
            }
            else if(avalon_irqrxsize >= TPL_MLEN)
            {
                if(((rxlen+TPL_MLEN) == avalon_irqrxsize) || (avalon_irqrxsize == AVALON_IRQRXBUF_SIZE))
                {
                    ret = avalon_protocol_check(avalon_irqrxbuf,avalon_irqrxsize);
                    if(ret != PRET_OK)
                    {
                        avalon_protocol_return(avalon_irqrxbuf,ret);
                    }
                    else if(avalon_rxsize == 0)
                    {
                        memcpy(avalon_txrxbuf,avalon_irqrxbuf,avalon_irqrxsize);
                        avalon_rxsize = avalon_irqrxsize;
                        avalon_data_ready = 1;
                    }
                    avalon_irqrxsize = 0;
                }
            }
        }
    }
}

void avalon_cmd_return(uint8_t cret, uint8_t * databuf, uint16_t dlen)
{
    uint16_t crc16val;

    avalon_txrxbuf[TPLH_CTYPE_POS] |= CTYPE_DIRECT;
    avalon_txrxbuf[TPLH_CRET_POS] = cret;
    avalon_txrxbuf[TPLH_DLENH_POS] = (uint8_t)(dlen>>8);
    avalon_txrxbuf[TPLH_DLENL_POS] = (uint8_t)dlen;
    if(dlen)
    {
        memcpy(avalon_txrxbuf+TPL_DATA_POS,databuf,dlen);
    }
    crc16val = CRC_CCITT_Kermit(CRC16_INITVAL,avalon_txrxbuf,TPLH_LEN+dlen);
    avalon_txrxbuf[TPL_DATA_POS+dlen] = (uint8_t)(crc16val>>8);
    avalon_txrxbuf[TPL_DATA_POS+dlen+1] = (uint8_t)crc16val;

    avalon_uart_transmit(avalon_txrxbuf,TPL_MLEN+dlen);
    ledrgb_off();
    led_wink_cnt = LED_ZERO;
    led_wink_flag = LEDG_300;
}
