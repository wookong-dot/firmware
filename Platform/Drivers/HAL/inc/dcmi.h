/**
  ******************************************************************************
  * @file    DCMI.h
  * @author  TMC  Team
  * @version V3.1.0
  * @date    06/19/2009
  * @brief   This file contains all the functions prototypes for the TIM firmware 
  *          library.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DCMI_H
#define __DCMI_H

#ifdef __cplusplus
 extern "C" {
#endif

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
/* Exported constants --------------------------------------------------------*/
/** @defgroup DCMI_Exported_Constants DCMI Exported Constants
  * @{
  */
	 
/** 
  * @brief  DCMI Init structure definition
  * @note   This sturcture is used with  DCMI   
  */
  
/** 
  * @brief   DCMIEx Embedded Synchronisation CODE Init structure definition
  */ 
typedef struct
{
  uint8_t FrameStartCode; /*!< Specifies the code of the frame start delimiter. */
  uint8_t LineStartCode;  /*!< Specifies the code of the line start delimiter.  */
  uint8_t LineEndCode;    /*!< Specifies the code of the line end delimiter.    */
  uint8_t FrameEndCode;   /*!< Specifies the code of the frame end delimiter.   */
}DCMI_CodesInitTypeDef;

/** 
  * @brief   DCMI Init structure definition
  */  
typedef struct
{
  uint32_t  SynchroMode;                /*!< Specifies the Synchronization Mode: Hardware or Embedded.
                                             This parameter can be a value of @ref DCMI_Synchronization_Mode */

  uint32_t  PCKPolarity;                /*!< Specifies the Pixel clock polarity: Falling or Rising.
                                             This parameter can be a value of @ref DCMI_PIXCK_Polarity       */

  uint32_t  VSPolarity;                 /*!< Specifies the Vertical synchronization polarity: High or Low.
                                             This parameter can be a value of @ref DCMI_VSYNC_Polarity       */

  uint32_t  HSPolarity;                 /*!< Specifies the Horizontal synchronization polarity: High or Low.
                                             This parameter can be a value of @ref DCMI_HSYNC_Polarity       */

  uint32_t  CaptureRate;                /*!< Specifies the frequency of frame capture: All, 1/2 or 1/4.
                                             This parameter can be a value of @ref DCMI_Capture_Rate         */

  uint32_t  ExtendedDataMode;           /*!< Specifies the data width: 8-bit, 10-bit, 12-bit or 14-bit.
                                             This parameter can be a value of @ref DCMI_Extended_Data_Mode   */

  DCMI_CodesInitTypeDef SyncroCode;     /*!< Specifies the code of the line/frame start delimiter and the
                                             line/frame end delimiter */

  uint32_t JPEGMode;                    /*!< Enable or Disable the JPEG mode.                                
                                             This parameter can be a value of @ref DCMI_MODE_JPEG            */

  uint32_t ByteSelectMode;              /*!< Specifies the data to be captured by the interface 
                                            This parameter can be a value of @ref DCMI_Byte_Select_Mode      */
                                            
  uint32_t ByteSelectStart;             /*!< Specifies if the data to be captured by the interface is even or odd
                                            This parameter can be a value of @ref DCMI_Byte_Select_Start     */

  uint32_t LineSelectMode;              /*!< Specifies the line of data to be captured by the interface 
                                            This parameter can be a value of @ref DCMI_Line_Select_Mode      */
                                            
  uint32_t LineSelectStart;             /*!< Specifies if the line of data to be captured by the interface is even or odd
                                            This parameter can be a value of @ref DCMI_Line_Select_Start     */
  
}DCMI_InitTypeDef;


/** @defgroup DCMI_Synchronization_Mode DCMI Synchronization Mode
  * @{
  */ 
#define DCMI_CR_ESS_Pos             (4U)                                        
#define DCMI_CR_ESS_Msk             (0x1U << DCMI_CR_ESS_Pos)         /*!< 0x00000010 */
#define DCMI_CR_ESS                	DCMI_CR_ESS_Msk  
#define DCMI_SYNCHRO_HARDWARE       ((uint32_t)0x00000000U)   		/*!< Hardware synchronization data capture (frame/line start/stop)                                                                  is synchronized with the HSYNC/VSYNC signals                  */
#define DCMI_SYNCHRO_EMBEDDED       ((uint32_t)DCMI_CR_ESS)  		/*!< Embedded synchronization data capture is synchronized with 
																		synchronization codes embedded in the data flow*/

/**
  * @}
  */

/** @defgroup DCMI_PIXCK_Polarity DCMI PIXCK Polarity
  * @{
  */
#define DCMI_CR_PCKPOL_Pos         (5U)                                        
#define DCMI_CR_PCKPOL_Msk         (0x1U << DCMI_CR_PCKPOL_Pos)              /*!< 0x00000020 */
#define DCMI_CR_PCKPOL             DCMI_CR_PCKPOL_Msk  
#define DCMI_PCKPOLARITY_FALLING    ((uint32_t)0x00000000U)      			/*!< Pixel clock active on Falling edge */
#define DCMI_PCKPOLARITY_RISING     ((uint32_t)DCMI_CR_PCKPOL)  			/*!< Pixel clock active on Rising edge  */

/**
  * @}
  */
  
/** @defgroup DCMI_VSYNC_Polarity DCMI VSYNC Polarity
  * @{
  */
  
#define DCMI_CR_VSPOL_Pos       (7U)                                        
#define DCMI_CR_VSPOL_Msk       (0x1U << DCMI_CR_VSPOL_Pos)					/*!< 0x00000080 */
#define DCMI_CR_VSPOL           DCMI_CR_VSPOL_Msk   
#define DCMI_VSPOLARITY_LOW     ((uint32_t)0x00000000U)     				/*!< Vertical synchronization active Low  */
#define DCMI_VSPOLARITY_HIGH    ((uint32_t)DCMI_CR_VSPOL)  					/*!< Vertical synchronization active High */

/**
  * @}
  */          
  
/** @defgroup DCMI_HSYNC_Polarity DCMI HSYNC Polarity
  * @{
  */ 
#define DCMI_CR_HSPOL_Pos			(6U)                                        
#define DCMI_CR_HSPOL_Msk          	(0x1U << DCMI_CR_HSPOL_Pos)					/*!< 0x00000040 */
#define DCMI_CR_HSPOL              	DCMI_CR_HSPOL_Msk  
#define DCMI_HSPOLARITY_LOW     	((uint32_t)0x00000000U)     				/*!< Horizontal synchronization active Low  */
#define DCMI_HSPOLARITY_HIGH    	((uint32_t)DCMI_CR_HSPOL)  					/*!< Horizontal synchronization active High */

/**
  * @}
  */ 
  
/** @defgroup DCMI_Capture_Rate DCMI Capture Rate
  * @{
  */
#define DCMI_CR_FCRC_0             	0x00000100U                                 
#define DCMI_CR_FCRC_1             	0x00000200U   
#define DCMI_CR_ALL_FRAME           ((uint32_t)0x00000000U)      					/*!< All frames are captured        */
#define DCMI_CR_ALTERNATE_2_FRAME   ((uint32_t)DCMI_CR_FCRC_0)  					/*!< Every alternate frame captured */
#define DCMI_CR_ALTERNATE_4_FRAME   ((uint32_t)DCMI_CR_FCRC_1)  					/*!< One frame in 4 frames captured */

/**
  * @}
  */  
  
/** @defgroup DCMI_Extended_Data_Mode DCMI Extended Data Mode
  * @{
  */
#define DCMI_CR_EDM_0              	0x00000400U                                 
#define DCMI_CR_EDM_1              	0x00000800U     
#define DCMI_EXTEND_DATA_8B     	((uint32_t)0x00000000U)                       	/*!< Interface captures 8-bit data on every pixel clock  */
#define DCMI_EXTEND_DATA_10B    	((uint32_t)DCMI_CR_EDM_0)                    	/*!< Interface captures 10-bit data on every pixel clock */
#define DCMI_EXTEND_DATA_12B    	((uint32_t)DCMI_CR_EDM_1)                    	/*!< Interface captures 12-bit data on every pixel clock */
#define DCMI_EXTEND_DATA_14B    	((uint32_t)(DCMI_CR_EDM_0 | DCMI_CR_EDM_1))  	/*!< Interface captures 14-bit data on every pixel clock */

/**
  * @}
  */
/** @defgroup DCMI_MODE_JPEG DCMI MODE JPEG
  * @{
  */
  
#define DCMI_CR_JPEG_Pos			(3U)                                        
#define DCMI_CR_JPEG_Msk			(0x1U << DCMI_CR_JPEG_Pos)                  /*!< 0x00000008 */
#define DCMI_CR_JPEG				DCMI_CR_JPEG_Msk  
#define DCMI_JPEG_DISABLE			((uint32_t)0x00000000U)    					/*!< Mode JPEG Disabled  */
#define DCMI_JPEG_ENABLE			((uint32_t)DCMI_CR_JPEG)  					/*!< Mode JPEG Enabled   */

/**
  * @}
  */

/** @defgroup DCMI_Image_Mode DCMI Image Mode
  * @{
  */
  
#define DCMI_IMAGE_MONOCHROME	 (1U<<5)                                     
#define DCMI_IMAGE_YCBCR		 (1U<<4) 
#define DCMI_IMAGE_RGB 		     ~((1U<<4)|(1U<<5)) 
/**
  * @}
  */
  
/** @defgroup DCMI_Byte_Select_Mode DCMI Byte Select Mode
  * @{
  */
#define DCMI_CR_BSM_0_Pos			(16U) 
#define DCMI_CR_BSM_1_Pos			(17U)   
#define DCMI_CR_BSM_0_Msk			(0x1U<<DCMI_CR_BSM_0_Pos) 
#define DCMI_CR_BSM_1_Msk			(0x1U<<DCMI_CR_BSM_1_Pos) 
#define DCMI_CR_BSM_0				DCMI_CR_BSM_0_Msk	 
#define DCMI_CR_BSM_1				DCMI_CR_BSM_1_Msk
#define DCMI_BSM_ALL				((uint32_t)0x00000000U)					 	/*!< Interface captures all received data */
#define DCMI_BSM_OTHER				((uint32_t)DCMI_CR_BSM_0) 					/*!< Interface captures every other byte from the received data */
#define DCMI_BSM_ALTERNATE_4		((uint32_t)DCMI_CR_BSM_1) 					/*!< Interface captures one byte out of four */
#define DCMI_BSM_ALTERNATE_2		((uint32_t)(DCMI_CR_BSM_0 | DCMI_CR_BSM_1)) /*!< Interface captures two bytes out of four */

/**
  * @}
  */

/** @defgroup DCMI_Line_Select_Start DCMI Line Select Start
  * @{
  */ 
#define DCMI_CR_OELS_Pos			(20U) 
#define DCMI_CR_OELS_Msk			(0x1U<<DCMI_CR_OELS_Pos) 
#define DCMI_CR_OELS				DCMI_CR_OELS_Msk
#define DCMI_OELS_ODD               ((uint32_t)0x00000000U) 					/*!< Interface captures first line from the frame start, second one being dropped */
#define DCMI_OELS_EVEN              ((uint32_t)DCMI_CR_OELS) 					/*!< Interface captures second line from the frame start, first one being dropped */

/**
  * @}
  */
/** @defgroup DCMI_Line_Select_Mode DCMI Line Select Mode
  * @{
  */
#define DCMI_CR_LSM_Pos				(19U) 
#define DCMI_CR_LSM_Msk				(0x1U<<DCMI_CR_LSM_Pos) 
#define DCMI_CR_LSM					 DCMI_CR_LSM_Msk
#define DCMI_LSM_ALL				((uint32_t)0x00000000U) 					/*!< Interface captures all received lines */
#define DCMI_LSM_ALTERNATE_2		((uint32_t)DCMI_CR_LSM) 					/*!< Interface captures one line out of two */

/**
  * @}
  */
  
/** @defgroup DCMI_Byte_Select_Start DCMI Byte Select Start
  * @{
  */ 
#define DCMI_CR_OEBS_Pos			(18U) 
#define DCMI_CR_OEBS_Msk			(0x1U<<DCMI_CR_OEBS_Pos) 
#define DCMI_CR_OEBS				DCMI_CR_OEBS_Msk
#define DCMI_OEBS_ODD               ((uint32_t)0x00000000U)  /*!< Interface captures first data from the frame/line start, second one being dropped */
#define DCMI_OEBS_EVEN              ((uint32_t)DCMI_CR_OEBS) /*!< Interface captures second data from the frame/line start, first one being dropped */

/**
  * @}
  */
  
/** @defgroup DCMI_Status DCMI_Status
  * @{
  */ 
#define DCMI_SR_FNE			(1U<<2)		/*!< State of FIFO, SET is uesful data stored in FIFO,RESET is FIFO empty*/
#define DCMI_SR_VSYNC		(1U<<1)		/*!< State of VSYNC's Pin, SET is Synchronization between farmes,RESET is Valid farme*/
#define DCMI_SR_HSYNC		(1U<<0)		/*!< State of HSYNC's Pin, SET is Synchronization between rows,RESET is Valid row*/

#define DCMI_RISR_LINE_RIS	(1U<<4)		/*!< Status of Raw interrupt,SET is HSYNC signal form invalid to valid,RESET is invalid
											 SET ICR to Clear the Status of DCMI_RISR*/
#define DCMI_RISR_VSYNC_RIS	(1U<<3)		/*!< Status of farme interrupt,SET is VSYNC signal form invalid to valid,RESET is invalid
											 SET ICR to Clear the Status of DCMI_RISR*/
#define DCMI_RISR_ERR_RIS	(1U<<2)		/*!< Status of ERR,RESET is NO sync errors detected,SET is Inline code sync characters are not received
											 SET ICR to Clear the Status of DCMI_RISR*/
#define DCMI_RISR_OVR_RIS	(1U<<1)		/*!< Status of overflow,SET is Data overflow,FIFO err,RESET is not overflow
											 SET ICR to Clear the Status of DCMI_RISR*/
#define DCMI_RISR_FRAME_RIS	(1U)		/*!< Status of capture,SET is capture one frame data,RESET is not capture one frame data
											 SET ICR to Clear the Status of DCMI_RISR*/
/**
  * @}
  */  

/** @defgroup DCMI_IT_Msk DCMI IT Msk
  * @{
  */ 
#define DCMI_IT_LINE_MIS	(1U<<4)		
											 
#define DCMI_IT_VSYNC_MIS	(1U<<3)		
											
#define DCMI_IT_ERR_MIS		(1U<<2)		
											 
#define DCMI_IT_OVR_MIS		(1U<<1)		
									
#define DCMI_IT_FRAME_MIS	(1U)	

/**
  * @}
  */

/** @defgroup DCMI_Capture_Mode DCMI Capture Mode
  * @{
  */ 
#define DCMI_CAPTURE_SNAPSHOT			(2U)		
											 
#define DCMI_CAPTURE_CONTINUOUS_GRAB 	~(2U)		
												

/**
  * @}
  */

/** @defgroup DCMI_Private_Macros DCMI Private Macros
  * @{
  */
#define IS_DCMI_CAPTURE_MODE(MODE)(((MODE) == DCMI_CAPTURE_SNAPSHOT) || \
                                   ((MODE) == DCMI_CAPTURE_CONTINUOUS_GRAB))
																			 
#define IS_DCMI_SYNCHRO(MODE)(((MODE) == DCMI_SYNCHRO_HARDWARE) || \
                              ((MODE) == DCMI_SYNCHRO_EMBEDDED))
																	
#define IS_DCMI_PCKPOLARITY(POLARITY)(((POLARITY) == DCMI_PCKPOLARITY_FALLING) || \
                                      ((POLARITY) == DCMI_PCKPOLARITY_RISING))
																					
#define IS_DCMI_VSPOLARITY(POLARITY)(((POLARITY) == DCMI_VSPOLARITY_LOW) || \
                                     ((POLARITY) == DCMI_VSPOLARITY_HIGH))
																				 
#define IS_DCMI_HSPOLARITY(POLARITY)(((POLARITY) == DCMI_HSPOLARITY_LOW) || \
                                     ((POLARITY) == DCMI_HSPOLARITY_HIGH))
																				 
#define IS_DCMI_MODE_JPEG(JPEG_MODE)(((JPEG_MODE) == DCMI_JPEG_DISABLE) || \
                                     ((JPEG_MODE) == DCMI_JPEG_ENABLE))
																				 
#define IS_DCMI_CAPTURE_RATE(RATE) (((RATE) == DCMI_CR_ALL_FRAME)         || \
                                    ((RATE) == DCMI_CR_ALTERNATE_2_FRAME) || \
                                    ((RATE) == DCMI_CR_ALTERNATE_4_FRAME))
																				
#define IS_DCMI_EXTENDED_DATA(DATA)(((DATA) == DCMI_EXTEND_DATA_8B)  || \
                                    ((DATA) == DCMI_EXTEND_DATA_10B) || \
                                    ((DATA) == DCMI_EXTEND_DATA_12B) || \
                                    ((DATA) == DCMI_EXTEND_DATA_14B))
																				
#define IS_DCMI_WINDOW_COORDINATE(COORDINATE) ((COORDINATE) <= DCMI_WINDOW_COORDINATE)

#define IS_DCMI_WINDOW_HEIGHT(HEIGHT) ((HEIGHT) <= DCMI_WINDOW_HEIGHT)

#define IS_DCMI_BYTE_SELECT_MODE(MODE)(((MODE) == DCMI_BSM_ALL) || \
                                       ((MODE) == DCMI_BSM_OTHER) || \
                                       ((MODE) == DCMI_BSM_ALTERNATE_4) || \
                                       ((MODE) == DCMI_BSM_ALTERNATE_2))
                                                                                                
#define IS_DCMI_BYTE_SELECT_START(POLARITY)(((POLARITY) == DCMI_OEBS_ODD) || \
                                            ((POLARITY) == DCMI_OEBS_EVEN))
                              
#define IS_DCMI_LINE_SELECT_MODE(MODE)(((MODE) == DCMI_LSM_ALL) || \
                                       ((MODE) == DCMI_LSM_ALTERNATE_2))
                                      
#define IS_DCMI_LINE_SELECT_START(POLARITY)(((POLARITY) == DCMI_OELS_ODD) || \
                                            ((POLARITY) == DCMI_OELS_EVEN))

#define IS_DCMI_SR_STATUS(x)			   (((x) == DCMI_SR_FNE) || \
                                            ((x) == DCMI_SR_VSYNC)|| \
											((x) == DCMI_SR_HSYNC))
											
#define IS_DCMI_RISR_STATUS(x)			   (((x) & DCMI_RISR_LINE_RIS) || \
                                            ((x) & DCMI_RISR_VSYNC_RIS)|| \
											((x) & DCMI_RISR_ERR_RIS)|| \
											((x) & DCMI_RISR_OVR_RIS)|| \
											((x) & DCMI_RISR_FRAME_RIS))
											
#define IS_DCMI_IT(x)			   			(((x)& DCMI_IT_LINE_MIS) || \
                                            ((x) & DCMI_IT_VSYNC_MIS)|| \
											((x) & DCMI_IT_ERR_MIS)|| \
											((x) & DCMI_IT_OVR_MIS)|| \
											((x) & DCMI_IT_FRAME_MIS))
											
//#define IS_DCMI_CAPTURE_MODE(x)				(((x) == DCMI_CAPTURE_SNAPSHOT)||((x) == DCMI_CAPTURE_CONTINUOUS_GRAB))
/**
  * @}
  */  
/**
  * @}
  */ 
/** @addtogroup DCMI_exported_function
  * @{
  */
void DCMI_DeInit(void);
void DCMI_StructInit(DCMI_InitTypeDef* DCMI_InitStruct);
void DCMI_Init(DCMI_InitTypeDef* DCMI_InitStruct);
void DCMI_Cmd(FunctionalState NewState);
FlagStatus DCMI_GetSR_Status(uint32_t Flag);
FlagStatus DCMI_GetRISR_Status(uint32_t Flag);
void DCMI_ClearRISR_Status(uint32_t Flag);
void DCMI_ITConfig(uint32_t DCMI_IT,FunctionalState NewState);
void DCMI_ConfigESUR(uint8_t FEC,uint8_t LEC,uint8_t FSC,uint8_t LSC);
void DCMI_ConfigESUR_Mask(uint8_t FEC,uint8_t LEC,uint8_t FSC,uint8_t LSC);
void DCMI_ConfigCaptureHorizontalLine(uint16_t LineSize,uint16_t LinePixels);
void DCMI_ConfigCaptureVerticalLine(uint16_t LineSize,uint16_t LinePixels);
uint32_t DCMI_GetData(void);
void DCMI_ConfigFrameStart(FunctionalState NewState);
void DCMI_ConfigImageCompress(uint32_t ImageMode, FunctionalState NewState);
void DCMI_ClearFIFO(void);
void DCMI_ConfigDMA(FunctionalState NewState);
void DCMI_ConfigCaptureMode(uint32_t CaptureMode);
void DCMI_CaptureCmd(FunctionalState NewState);
void DCMI_ImageCut(FunctionalState NewState);
/**
  * @}
  */
/**
  * @}
  */
/**
  * @}
  */
/**
  * @}
  */
#ifdef __cplusplus
}
#endif

#endif 

/************************ (C) COPYRIGHT TMC *****END OF FILE***********************/
