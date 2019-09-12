/***************************************************************************
* File name    :    pxat_led.h
* Function     :    header of led module
* Author       :    xinght
* Date         :    2019/01/09
* Version      :    v1.0
* Description  :
* ModifyRecord :
****************************************************************************/
#ifndef _PXAT_LED_H_
#define _PXAT_LED_H_

/***************************************************************************
* Include Header Files
***************************************************************************/


/**************************************************************************
* Global Macro Definition
***************************************************************************/
#define LED_IDLE                            0
#define LED_ZERO                            0

#define LEDB_100                            1
#define LEDR_300                            2
#define LEDG_300                            3

/**************************************************************************
* Global Type Definition
***************************************************************************/


/**************************************************************************
* Global Variable Declaration
***************************************************************************/
extern volatile uint8_t led_wink_flag;
extern volatile uint32_t led_wink_cnt;

/**************************************************************************
* Global Function Declaration
***************************************************************************/
void led_init(void);
void ledr_on(void);
void ledg_on(void);
void ledb_on(void);
void ledrg_on(void);
void ledrb_on(void);
void ledgb_on(void);
void ledrgb_on(void);
void ledr_off(void);
void ledg_off(void);
void ledb_off(void);
void ledrg_off(void);
void ledrb_off(void);
void ledgb_off(void);
void ledrgb_off(void);
void led_blinking(void);
void led_handler(void);

#endif  //#ifndef _PXAT_LED_H_
