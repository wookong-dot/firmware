/***************************************************************************
* File name    :    pxat_vendor.c
* Function     :    vendor module
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
typedef struct
{
    unsigned char type;
    void (*CmdProc)(void);
} sCmdTable,*pCmdTable;

/**************************************************************************
* Local static Variable Declaration
***************************************************************************/
static const sCmdTable VdrCmdTable[] =
{
    CTYPE_SRSIGN,            cmd_srsign,
    CTYPE_GETCHALLENGE,      cmd_getchallenge,
    0xFF, 00,
};

/**************************************************************************
* Global Variable Declaration
**************************************************************************/


/**************************************************************************
* Local Function Declaration
***************************************************************************/
static pCmdTable GetVdrCmdTable(void)
{
    pCmdTable pCmdTb;

    pCmdTb = (pCmdTable)VdrCmdTable;

    while (pCmdTb->type != 0xFF)
    {
        if(pCmdTb->type == avalon_txrxbuf[TPLH_CTYPE_POS])
        {
            return pCmdTb;
        }
        pCmdTb++;
    }
    return 0;
}

/**************************************************************************
* Function
***************************************************************************/
void vdrmsg_deal(void)
{
    pCmdTable pVdrCmd;

    if(avalon_data_ready)
    {
        pVdrCmd = GetVdrCmdTable();
        if(pVdrCmd != 0)
        {
            pVdrCmd->CmdProc();
        }
        else
        {
            avalon_cmd_return(CRET_CTYPE_ERROR,NULL,0);
        }
        avalon_rxsize = 0;
        avalon_data_ready = 0;
    }
}
