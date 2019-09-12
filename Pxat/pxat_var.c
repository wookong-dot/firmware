/***************************************************************************
* File name    :    pxat_var.c
* Function     :    vendor variable module
* Author       :    xinght
* Date         :    2019/01/09
* Version      :    v1.0
* Description  :
* ModifyRecord :
****************************************************************************/
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


/**************************************************************************
* Global Variable Declaration
**************************************************************************/
volatile uint8_t avalon_data_ready;
volatile uint16_t avalon_irqrxsize;
volatile uint16_t avalon_rxsize;
uint8_t avalon_irqrxbuf[AVALON_IRQRXBUF_SIZE];
uint8_t avalon_txrxbuf[AVALON_TXRXBUF_SIZE];

/**************************************************************************
* Local Function Declaration
***************************************************************************/


/**************************************************************************
* Function
***************************************************************************/
void vdrvar_init(void)
{
    avalon_data_ready = 0;
    avalon_irqrxsize = 0;
    avalon_rxsize = 0;
    memset(avalon_irqrxbuf,0x00,AVALON_IRQRXBUF_SIZE);
    memset(avalon_txrxbuf,0x00,AVALON_TXRXBUF_SIZE);
}