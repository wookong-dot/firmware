/**************************************************************************//**
 * @file     startup_ARMCM3.s
 * @brief    CMSIS Core Device Startup File for
 *           ARMCM3 Device Series
 * @version  V5.00
 * @date     02. March 2016
 ******************************************************************************/
/*
 * Copyright (c) 2009-2016 ARM Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

	.syntax	unified
	.arch	armv7-m

	.section .stack
	.align	3
#ifdef __STACK_SIZE
	.equ	Stack_Size, __STACK_SIZE
#else
	.equ	Stack_Size, 0x00000400
#endif
	.globl	__StackTop
	.globl	__StackLimit
__StackLimit:
	.space	Stack_Size
	.size	__StackLimit, . - __StackLimit
__StackTop:
	.size	__StackTop, . - __StackTop

	.section .heap
	.align	3
#ifdef __HEAP_SIZE
	.equ	Heap_Size, __HEAP_SIZE
#else
	.equ	Heap_Size, 0x00000C00
#endif
	.globl	__HeapBase
	.globl	__HeapLimit
__HeapBase:
	.if	Heap_Size
	.space	Heap_Size
	.endif
	.size	__HeapBase, . - __HeapBase
__HeapLimit:
	.size	__HeapLimit, . - __HeapLimit

	.section .vectors
	.align	2
	.globl	__Vectors
Default_Handler:
	b	.
	.size	Default_Handler, . - Default_Handler

/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
	.macro	def_irq_handler	handler_name
	.weak	\handler_name
	.set	\handler_name, Default_Handler
	.endm

	def_irq_handler	NMI_Handler
	def_irq_handler	HardFault_Handler
	def_irq_handler	MemManage_Handler
	def_irq_handler	BusFault_Handler
	def_irq_handler	UsageFault_Handler
	def_irq_handler	SVC_Handler
	def_irq_handler	DebugMon_Handler
	def_irq_handler	PendSV_Handler
	def_irq_handler	SysTick_Handler

	def_irq_handler	WDT_IRQHandler
	def_irq_handler	RTC_IRQHandler
	def_irq_handler	TIM0_IRQHandler
	def_irq_handler	TIM2_IRQHandler
	def_irq_handler	MCIA_IRQHandler
	def_irq_handler	MCIB_IRQHandler
	def_irq_handler	UART0_IRQHandler
	def_irq_handler	UART1_IRQHandler
	def_irq_handler	UART2_IRQHandler
	def_irq_handler	UART3_IRQHandler
	def_irq_handler	UART4_IRQHandler
	def_irq_handler	AACI_IRQHandler
	def_irq_handler	CLCD_IRQHandler
	def_irq_handler	ENET_IRQHandler
	def_irq_handler	USBDC_IRQHandler
	def_irq_handler	USBHC_IRQHandler
	def_irq_handler	CHLCD_IRQHandler
	def_irq_handler	FLEXRAY_IRQHandler
	def_irq_handler	CAN_IRQHandler
	def_irq_handler	LIN_IRQHandler
	def_irq_handler	I2C_IRQHandler
	def_irq_handler	CPU_CLCD_IRQHandler
	def_irq_handler	SPI_IRQHandler

	.end
