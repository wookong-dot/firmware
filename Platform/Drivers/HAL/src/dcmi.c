 /**
  ******************************************************************************
  * @file    DCMI.c
  * @author  TMC Terminal Team
  * @version V1.0.0
  * @date    06/01/2018
  * @brief   This file provides all the RCC firmware functions.
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
  ******************************************************************************/

/* Includes ------------------------------------------------------------------*/

#include "thm36x2.h"
#include "RCC.h"
#include "DCMI.h"

/** @addtogroup THM36x2
  * @{
  */
  
/** @addtogroup THM36x2_HAL_Driver
  * @{
  */

/** @defgroup DCMI 
  * @brief DCMI HAL modules driver 
  * @{
  */ 
  
/** @defgroup DCMI_Private_Defines DCMI Private Defines
  * @{
  */
#define DCMI_ESCR_FSC_Pos          (0U)                                        
#define DCMI_ESCR_FSC_Msk          (0xFFU << DCMI_ESCR_FSC_Pos)                /*!< 0x000000FF */
#define DCMI_ESCR_FSC              DCMI_ESCR_FSC_Msk                           
#define DCMI_ESCR_LSC_Pos          (8U)                                        
#define DCMI_ESCR_LSC_Msk          (0xFFU << DCMI_ESCR_LSC_Pos)                /*!< 0x0000FF00 */
#define DCMI_ESCR_LSC              DCMI_ESCR_LSC_Msk                           
#define DCMI_ESCR_LEC_Pos          (16U)                                       
#define DCMI_ESCR_LEC_Msk          (0xFFU << DCMI_ESCR_LEC_Pos)                /*!< 0x00FF0000 */
#define DCMI_ESCR_LEC              DCMI_ESCR_LEC_Msk                           
#define DCMI_ESCR_FEC_Pos          (24U)                                       
#define DCMI_ESCR_FEC_Msk          (0xFFU << DCMI_ESCR_FEC_Pos)                /*!< 0xFF000000 */
#define DCMI_ESCR_FEC              DCMI_ESCR_FEC_Msk                           
#define DCMI_ENABLE				   (1U<<14UL)
#define DCMI_DISABLE			   ~(1U<<14UL)
/**
  * @}
  */
  
/** @defgroup RCC_Exported_Functions RCC Exported Functions
  * @{
  */ 

/**
  * @brief  Resets the DCMI configuration to the default reset state.
  * @param  None
  * @retval None
  */
void DCMI_DeInit(void)
{
	RCC_AHBPeriphSoftReset(RCC_AHBPeriph_DCMI);
	while(RCC_AHBPeriphGetResetFlag(RCC_AHBPeriph_DCMI) == RESET);
}


/**
  * @brief  Fills each SPI_InitStruct member with its default value.
  * @param[in] SPI_InitStruct: pointer to a SPI_InitTypeDef structure,which will be initialized.
  * @retval none
  * @note  The default value is as following
  */
void DCMI_StructInit(DCMI_InitTypeDef* DCMI_InitStruct)
{
	DCMI_InitStruct->SynchroMode =  DCMI_SYNCHRO_HARDWARE;
	DCMI_InitStruct->PCKPolarity =  DCMI_PCKPOLARITY_RISING;
	DCMI_InitStruct->VSPolarity = DCMI_VSPOLARITY_LOW;
	DCMI_InitStruct->HSPolarity = DCMI_HSPOLARITY_LOW;
	DCMI_InitStruct->CaptureRate = DCMI_CR_ALL_FRAME;
	DCMI_InitStruct->ExtendedDataMode = DCMI_EXTEND_DATA_8B;
	DCMI_InitStruct->JPEGMode = DCMI_JPEG_ENABLE;
	DCMI_InitStruct->ByteSelectMode = DCMI_BSM_ALL;
	DCMI_InitStruct->ByteSelectStart = DCMI_OEBS_ODD;
	DCMI_InitStruct->LineSelectMode = DCMI_LSM_ALL;
	DCMI_InitStruct->LineSelectStart = DCMI_OEBS_ODD;
}
/**
  * @}
  */ 

/**
  * @brief  Initializes the DCMI according to the specified
  *         parameters in the DCMI_InitTypeDef and create the associated handle.
  * @param  hdcmi pointer to a DCMI_HandleTypeDef structure that contains
  *                the configuration information for DCMI.
  * @retval HAL status
  */
void DCMI_Init(DCMI_InitTypeDef* DCMI_InitStruct)
{
	/* Check function parameters */
	assert_param(IS_DCMI_PCKPOLARITY(DCMI_InitStruct->PCKPolarity));
	assert_param(IS_DCMI_VSPOLARITY(DCMI_InitStruct->VSPolarity));
	assert_param(IS_DCMI_HSPOLARITY(DCMI_InitStruct->HSPolarity));
	assert_param(IS_DCMI_SYNCHRO(DCMI_InitStruct->SynchroMode));
	assert_param(IS_DCMI_CAPTURE_RATE(DCMI_InitStruct->CaptureRate));
	assert_param(IS_DCMI_EXTENDED_DATA(DCMI_InitStruct->ExtendedDataMode));
	assert_param(IS_DCMI_MODE_JPEG(DCMI_InitStruct->JPEGMode));
	assert_param(IS_DCMI_BYTE_SELECT_MODE(DCMI_InitStruct->ByteSelectMode));
	assert_param(IS_DCMI_BYTE_SELECT_START(DCMI_InitStruct->ByteSelectStart));
	assert_param(IS_DCMI_LINE_SELECT_MODE(DCMI_InitStruct->LineSelectMode));
	assert_param(IS_DCMI_LINE_SELECT_START(DCMI_InitStruct->LineSelectStart));
	/* Set DCMI parameters */
	/* Configures the HS, VS, DE and PC polarity */
	DCMI->CR &= ~(DCMI_CR_PCKPOL | DCMI_CR_HSPOL  | DCMI_CR_VSPOL  | DCMI_CR_EDM_0 |
                  DCMI_CR_EDM_1  | DCMI_CR_FCRC_0 | DCMI_CR_FCRC_1 | DCMI_CR_JPEG  |
                  DCMI_CR_ESS);
	DCMI->CR = DCMI_InitStruct->SynchroMode|DCMI_InitStruct->PCKPolarity|DCMI_InitStruct->VSPolarity|DCMI_InitStruct->HSPolarity|DCMI_InitStruct->CaptureRate|\
			   DCMI_InitStruct->ExtendedDataMode|DCMI_InitStruct->JPEGMode|DCMI_InitStruct->ByteSelectMode|DCMI_InitStruct->ByteSelectStart|DCMI_InitStruct->LineSelectMode|\
			   DCMI_InitStruct->LineSelectStart;
	if(DCMI_InitStruct->SynchroMode == DCMI_SYNCHRO_EMBEDDED)
	{
		DCMI->ESCR = ((DCMI_InitStruct->SyncroCode.FrameStartCode)|\
		(DCMI_InitStruct->SyncroCode.LineStartCode << DCMI_ESCR_LSC_Pos)|\
		(DCMI_InitStruct->SyncroCode.LineEndCode << DCMI_ESCR_LEC_Pos) |\
		(DCMI_InitStruct->SyncroCode.FrameEndCode << DCMI_ESCR_FEC_Pos));
	}
}

/**
  * @brief Enable or Disable DMCI
  * @param[in] NewState: NewState: new state of the DCMI peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval none
  * @note  
  */
void DCMI_Cmd(FunctionalState NewState)
{
	if(NewState == ENABLE)
	{
		DCMI->CR|= DCMI_ENABLE;
	}
	else
	{
		DCMI->CR&=DCMI_DISABLE;
	}
}

/**
  * @brief Get SR's Status(DCMI  Register)
  * @param[in] Flag :
  *    @arg DCMI_SR_FNE
  *    @arg DCMI_SR_VSYNC
  *    @arg DCMI_SR_HSYNC
  * @retval FlagStatus
  *    @arg SET or RESET
  * @note  
  */
FlagStatus DCMI_GetSR_Status(uint32_t Flag)
{
	assert_param(IS_DCMI_SR_STATUS(Flag));
	if(DCMI->SR&Flag)
	{
		return SET;	
	}
	return RESET;

}


/**
  * @brief Get RISR's Status(DCMI  Register)
  * @param[in] Flag :
  *    @arg DCMI_RISR_LINE_RIS
  *    @arg DCMI_RISR_VSYNC_RIS
  *    @arg DCMI_RISR_ERR_RIS
  *    @arg DCMI_RISR_OVR_RIS
  *    @arg DCMI_RISR_FRAME_RIS
  * @retval FlagStatus
  *    @arg SET or RESET
  * @note  
  */
FlagStatus DCMI_GetRISR_Status(uint32_t Flag)
{
	assert_param(IS_DCMI_RISR_STATUS(Flag));
	if(Flag&DCMI->RISR)
	{
		return SET;	
	}
	return RESET;
}

/**
  * @brief Clear RISR's Status(DCMI  Register)
  * @param[in] Flag :
  *    @arg DCMI_RISR_LINE_RIS
  *    @arg DCMI_RISR_VSYNC_RIS
  *    @arg DCMI_RISR_ERR_RIS
  *    @arg DCMI_RISR_OVR_RIS
  *    @arg DCMI_RISR_FRAME_RIS
  * @retval FlagStatus
  *    @arg SET or RESET
  * @note  
  */
void DCMI_ClearRISR_Status(uint32_t Flag)
{
	assert_param(IS_DCMI_RISR_STATUS(Flag));
	DCMI->ICR = Flag;
}

/**
  * @brief Config DMCI's Interrupt Mask
  * @param[in] DCMI_IT :
  *    @arg DCMI_IT_LINE_MIS
  *    @arg DCMI_IT_VSYNC_MIS
  *    @arg DCMI_IT_ERR_MIS
  *    @arg DCMI_IT_OVR_MIS
  *    @arg DCMI_IT_FRAME_MIS
  * @param[in] NewState :
  *    @arg ENABLE
  *    @arg DISABLE
  * @retval none
  * @note  
  */
void DCMI_ITConfig(uint32_t DCMI_IT,FunctionalState NewState)
{
	assert_param(IS_DCMI_IT(DCMI_IT));	
	if(NewState == ENABLE)
	{
		DCMI->IER|= DCMI_IT;
	}
	else
	{
		DCMI->IER&= ~DCMI_IT;
	}
}
/**
  * @brief Config DMCI's frame separator and Line separator
  * @param[in] FEC :frame End separator
  * @param[in] LEC :Line End separator
  * @param[in] FSC :frame Start separator
  * @param[in] LSC :Line Start separator
  * @retval none
  * @note  
  */
void DCMI_ConfigESUR(uint8_t FEC,uint8_t LEC,uint8_t FSC,uint8_t LSC)
{
	uint32_t Temp;
	Temp = 0;
	Temp|=FEC<<24;
	Temp|=LEC<<16;
	Temp|=LSC<<8;
	Temp|=FSC;
	DCMI->ESCR = Temp;
}

/**
  * @brief Config Mask  separator's bit are compared to DCMI received separator's bit 
  * @param[in] FEC :frame End separator
  * @param[in] LEC :Line End separator
  * @param[in] FSC :frame Start separator
  * @param[in] LSC :Line Start separator
  * @retval none
  * @note  
  */
void DCMI_ConfigESUR_Mask(uint8_t FEC,uint8_t LEC,uint8_t FSC,uint8_t LSC)
{
	uint32_t Temp;
	Temp = 0;
	Temp|=FEC<<24;
	Temp|=LEC<<16;
	Temp|=LSC<<8;
	Temp|=FSC;
	DCMI->ESUR= Temp;
}

/**
  * @brief Config the camera capture horizontal Window Size
  * @param[in] LineSize :Number of Lines captured
  * @param[in] LinePixels :Number of pixels captured
  * @retval none
  * @note  
  */
void DCMI_ConfigCaptureHorizontalLine(uint16_t LineSize,uint16_t LinePixels)
{
	uint32_t Temp;
	Temp = 0;
	Temp|=LineSize<<16;
	Temp|=LinePixels;
	DCMI->CWSTRT = Temp;
}

/**
  * @brief Config the camera capture Vertical Window Size
  * @param[in] LineSize :Number of Lines captured
  * @param[in] LinePixels :Number of pixels captured
  * @retval none
  * @note  
  */
void DCMI_ConfigCaptureVerticalLine(uint16_t LineSize,uint16_t LinePixels)
{
	uint32_t Temp;
	Temp = 0;
	Temp|=LineSize<<16;
	Temp|=LinePixels;
	DCMI->CWSIZE= Temp;
}
/**
  * @brief Get DCMI's Data
  * @param[in] none
  * @retval uint32_t DCMI's Data
  * @note  
  */
uint32_t DCMI_GetData(void)
{
	return DCMI->DR;
}

/**
  * @brief config Enable or Disable DCMI get data, when VSYNC's PIN form High to Low  
  * @param[in] NewState: NewState: new state of the Frame Start
  *   This parameter can be: ENABLE or DISABLE.
  * @retval none
  * @note  none
  */
void DCMI_ConfigFrameStart(FunctionalState NewState)
{
	if(NewState == ENABLE)
	{
		DCMI->CR2|=1U<<3;
	}
	else
	{
		DCMI->CR2&=~(1U<<3);
	}
}

/**
  * @brief Enable or Disable DCMI Image Compress 
  * @param[in] ImageMode
  *		@arg DCMI_IMAGE_MONOCHROME
  *		@arg DCMI_IMAGE_YCBCR
  *		@arg DCMI_IMAGE_RGB
  * @param[in] NewState: NewState: new state of the Image Compress 
  *		@arg ENABLE
  *		@arg DISABLE
  * @retval none
  * @note  none
  */
void DCMI_ConfigImageCompress(uint32_t ImageMode, FunctionalState NewState)
{
	DCMI->CR2&=~((1U<<5)|(1U<<4));
	DCMI->CR2|=ImageMode;
	if(NewState == ENABLE)
	{
		DCMI->CR2|=1U<<1;
	}
	else
	{
		DCMI->CR2&=~(1U<<1);
	}
}

/**
  * @brief Clear DCMI FIFO Data
  * @retval none
  * @note  none
  */
void DCMI_ClearFIFO(void)
{
	DCMI->CR2|=1;
}

/**
  * @brief config DCMI DMA
  * @param[in] NewState: NewState: new state of the DCMI DMA
  *		@arg ENABLE
  *		@arg DISABLE
  * @retval none
  * @note  none
  */
void DCMI_ConfigDMA(FunctionalState NewState)
{
	if(NewState == ENABLE)
	{
		DCMI->CR2|=1<<2;
	}
	else
	{
		DCMI->CR2&=~(1<<2);
	}
}


/**
  * @brief config DCMI Capture Mode
  * @param[in] CaptureMode
  *		@arg DCMI_CAPTURE_SNAPSHOT
  *		@arg DCMI_CAPTURE_CONTINUOUS_GRAB
  * @retval none
  * @note  none
  */
void DCMI_ConfigCaptureMode(uint32_t CaptureMode)
{
	assert_param(IS_DCMI_CAPTURE_MODE(CaptureMode));
	if(CaptureMode == DCMI_CAPTURE_SNAPSHOT)
	{
		DCMI->CR|=DCMI_CAPTURE_SNAPSHOT;
	}
	else
	{
		DCMI->CR&=DCMI_CAPTURE_CONTINUOUS_GRAB;
	}
}

/**
  * @brief config DCMI Capture Mode
  * @param[in] NewState: NewState: new state of Capture Cmd
  *		@arg ENABLE
  *		@arg DISABLE
  * @retval none
  * @note  none
  */
void DCMI_CaptureCmd(FunctionalState NewState)
{
	if(NewState == ENABLE)
	{
		DCMI->CR|=1U;
	}
	else
	{
		DCMI->CR&=~(1U);
	}
	
}


/**
  * @brief config DCMI Capture Mode
  * @param[in] NewState: NewState: new state of the DCMI Image Cut
  *		@arg ENABLE
  *		@arg DISABLE
  * @retval none
  * @note  none
  */
void DCMI_ImageCut(FunctionalState NewState)
{
	if(NewState == ENABLE)
	{
		DCMI->CR|=2U;
	}
	else
	{
		DCMI->CR&=~(2U);
	}
	
}



/**
  * @}
  */
/**
  * @}
  */   
/**
  * @}
  */ 

/************************ (C) COPYRIGHT TMC *****END OF FILE***********************/

