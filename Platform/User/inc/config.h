/***************************************************************************
* File name    :    config.h
* Function     :    Header of Configuration Module
* Author       :    XHT
* Date         :    2019/02/13
* Version      :    v1.0
* Description  :
* ModifyRecord :
***************************************************************************/
#ifndef _CONFIG_H_
#define _CONFIG_H_

/****************************************************************/
/* Attention: start all directives for the Configuration        */
/*            Wizard in column 1 with '//'.                     */
/*            A directive for the Configuration Wizard starting */
/*            in column 2 or later with '//' is neither         */
/*            recognized nor execured.                          */
/****************************************************************/

//*** <<< Use Configuration Wizard in Context Menu >>> ***

// nothing...

//*** <<< end of configuration section >>>  ***

#define SECT(name)                          __attribute__ ((section (#name)))
#define ALIGN(addr)                         __attribute__ ((aligned (addr)))
#define AT(addr)                            __attribute__ ((at(addr)))

#endif  //#ifndef _CONFIG_H_
