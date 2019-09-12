#include <stdint.h>

typedef struct
{
	volatile uint32_t CLKCON;
	volatile uint32_t CLKPLL;
	volatile uint32_t CLKPLLFREQ;
	volatile uint32_t CLKHSE;
	volatile uint32_t CLKINTMSK;
	volatile uint32_t RFU[3];
	volatile uint32_t CLKSYSSEL;
	volatile uint32_t RFU1[3];
	volatile uint32_t CLKSLV1SCON;
	volatile uint32_t CLKSLV2SCON;
	volatile uint32_t CLKSLV3SCON;
	volatile uint32_t CLKSLV4SCON;
	volatile uint32_t CLKSLV5SCON;
	volatile uint32_t RFU2[3];
	volatile uint32_t CLKSLV1LPSCON;
	volatile uint32_t CLKSLV2LPSCON;
	volatile uint32_t CLKSLV3LPSCON;
	volatile uint32_t CLKSLV4LPSCON;
	volatile uint32_t CLKSLV5LPSCON;
	volatile uint32_t RFU3[3];
	volatile uint32_t CLKUSBSEL;
	volatile uint32_t CLKEXSPISEL;
	volatile uint32_t CLKADCSEL;
	volatile uint32_t RFU4[2];
	volatile uint32_t CLKGENAL2SEL;
	volatile uint32_t CLKGENAL3SEL;
	volatile uint32_t CLKGENAL4SEL;
	volatile uint32_t CLKGENAL5SEL;
	volatile uint32_t CLKGENAL6SEL;
	volatile uint32_t CLKGENAL7SEL;
	volatile uint32_t RFU5;
	volatile uint32_t CLKTIM1SEL;
	volatile uint32_t CLKTIM2SEL;
	volatile uint32_t CLKTIM3SEL;
	volatile uint32_t CLKTIM4SEL;
	volatile uint32_t CLKTIM5SEL;
	volatile uint32_t CLKTIM6SEL;
	volatile uint32_t CLKTIM7SEL;
	volatile uint32_t RFU6[4];
	volatile uint32_t CLKSYSTIMSEL;
}SCU_CLK_TypeDef;

#define RCC_CLK_BASE_ADDR	    		0x40000C00
#define RCC_CLK		   	((SCU_CLK_TypeDef *) RCC_CLK_BASE_ADDR)

#define RCC_CLKC_PLLRDY_Pos			(5U)
#define RCC_CLKC_PLLRDY_Msk			(0x1UL << RCC_CLKC_PLLRDY_Pos)		/*!< 0x00000020 */
#define RCC_CLKC_PLLRDY				RCC_CLKC_PLLRDY_Msk
#define RCC_CLKC_PLLON_Pos			(4U)
#define RCC_CLKC_PLLON_Msk			(0x1UL << RCC_CLKC_PLLON_Pos)		/*!< 0x00000010 */
#define RCC_CLKC_PLLON				RCC_CLKC_PLLON_Msk


typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;

#include"pll_enable.h"
static void RCC_Cmd(FunctionalState NewState);
/**
  * @brief  Turn on or turn off the PLL clock.
  * @param[in] NewState: new state of the specified PLL clock
  * 	This parameter can be one of the following values: 
  *		@arg DISABLE :disable PLL
  *     @arg ENABLE  :enable PLL
  * @retval none
  * @note	none
  */  
static void RCC_Cmd(FunctionalState NewState)
{
	/* Reset HSEON before configuring the HSE ------------------*/
	if(NewState != DISABLE)
	{
		RCC_CLK->CLKCON |= RCC_CLKC_PLLON;
	}
	else
	{
		RCC_CLK->CLKCON &= ~RCC_CLKC_PLLON;
	}
}

void RCC_Enable(void)
{
	volatile uint32_t i = 0;
	while(1)
	{
		i = 0;
		RCC_Cmd(ENABLE);
		while((!(RCC_CLK->CLKCON&(1UL<<5)))&&(i<193))
		{
			i++;
		}
		if(i>=193)
		{
			RCC_Cmd(DISABLE);
		}
		else
		{
			return;
		}
	}
}

