/***************************************************************************
* File name    :    pxat_led.c
* Function     :    led module
* Author       :    xinght
* Date         :    2019/01/09
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
#define LEDB_PORT                           GPIOD
#define LEDR_PORT                           GPIOC
#define LEDG_PORT                           GPIOC

#define LEDB_PIN                            GPIO_PIN_12
#define LEDR_PIN                            GPIO_PIN_13
#define LEDG_PIN                            GPIO_PIN_14

/**************************************************************************
* Local Type Definition
***************************************************************************/


/**************************************************************************
* Local static Variable Declaration
***************************************************************************/


/**************************************************************************
* Global Variable Declaration
***************************************************************************/
volatile uint8_t led_wink_flag;
volatile uint32_t led_wink_cnt;

/**************************************************************************
* Local Function Declaration
***************************************************************************/



/**************************************************************************
* Function
***************************************************************************/
void led_init(void)
{
    GPIO_InitTypeDef GPIOx_Init;

    GPIOx_Init.Mode = GPIO_MODE_OUT;
    GPIOx_Init.Speed = GPIO_FAST_SPEED;
    GPIOx_Init.Pull = GPIO_PULLUP;
    GPIOx_Init.Otype = GPIO_MODE_OUTPUT_PP;
    GPIOx_Init.SMIT = GPIO_INPUTSCHMIT_DISABLE;
    GPIO_Init(GPIOD, &GPIOx_Init);

    GPIOx_Init.Pin = LEDR_PIN;
    GPIO_Init(LEDR_PORT, &GPIOx_Init);

    GPIOx_Init.Pin = LEDG_PIN;
    GPIO_Init(LEDG_PORT, &GPIOx_Init);

    GPIOx_Init.Pin = LEDB_PIN;
    GPIO_Init(LEDB_PORT, &GPIOx_Init);

    ledrgb_off();
    led_wink_flag = LED_IDLE;
    led_wink_cnt = LED_ZERO;
    ledb_on();      //LED Blue On after Power-on
}

void ledr_on(void) //red 红色
{
    LEDR_PORT->OD |= LEDR_PIN;
}

void ledg_on(void) //green 绿色
{
    LEDG_PORT->OD |= LEDG_PIN;
}

void ledb_on(void) //blue 蓝色
{
    LEDB_PORT->OD |= LEDB_PIN;
}

void ledrg_on(void) //yellow 黄色
{
    LEDR_PORT->OD |= LEDR_PIN;
    LEDG_PORT->OD |= LEDG_PIN;
}

void ledrb_on(void) //magenta 品红
{
    LEDR_PORT->OD |= LEDR_PIN;
    LEDB_PORT->OD |= LEDB_PIN;
}

void ledgb_on(void) //cyan 青
{
    LEDG_PORT->OD |= LEDG_PIN;
    LEDB_PORT->OD |= LEDB_PIN;
}

void ledrgb_on(void) //white 白
{
    LEDR_PORT->OD |= LEDR_PIN;
    LEDG_PORT->OD |= LEDG_PIN;
    LEDB_PORT->OD |= LEDB_PIN;
}

void ledr_off(void)
{
    LEDR_PORT->OD &= ~LEDR_PIN;
}

void ledg_off(void)
{
    LEDG_PORT->OD &= ~LEDG_PIN;
}

void ledb_off(void)
{
    LEDB_PORT->OD &= ~LEDB_PIN;
}

void ledrg_off(void)
{
    LEDR_PORT->OD &= ~LEDR_PIN;
    LEDG_PORT->OD &= ~LEDG_PIN;
}

void ledrb_off(void)
{
    LEDR_PORT->OD &= ~LEDR_PIN;
    LEDB_PORT->OD &= ~LEDB_PIN;
}

void ledgb_off(void)
{
    LEDG_PORT->OD &= ~LEDG_PIN;
    LEDB_PORT->OD &= ~LEDB_PIN;
}

void ledrgb_off(void)
{
    LEDR_PORT->OD &= ~LEDR_PIN;
    LEDG_PORT->OD &= ~LEDG_PIN;
    LEDB_PORT->OD &= ~LEDB_PIN;
}

void led_blinking(void)
{
    uint8_t loop = 3;
    while(loop--)
    {
        ledrgb_on();
        delay_ms(300);
        ledrgb_off();
        delay_ms(300);
    }
}

void led_handler(void)  //100ms 一次中断
{
    led_wink_cnt++;

    if(led_wink_flag == LEDB_100)   //blue led wink 100ms
    {
        if(led_wink_cnt == 1)
        {
            ledb_on();
        }
        else if(led_wink_cnt == 2)
        {
            ledrgb_off();
            led_wink_cnt = LED_ZERO;
        }
    }
    else if(led_wink_flag == LEDR_300)  //red led light on 300ms
    {
        if(led_wink_cnt == 1)
        {
            ledr_on();
        }
        else if(led_wink_cnt == 5)
        {
            ledrgb_off();
            led_wink_cnt = LED_ZERO;
            led_wink_flag = LED_IDLE;
            ledb_on();
        }
    }
    else if(led_wink_flag == LEDG_300)  //green led ligth on 300ms
    {
        if(led_wink_cnt == 1)
        {
            ledg_on();
        }
        else if(led_wink_cnt == 5)
        {
            ledrgb_off();
            led_wink_cnt = LED_ZERO;
            led_wink_flag = LED_IDLE;
            ledb_on();
        }
    }
}
