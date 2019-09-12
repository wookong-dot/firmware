/**
  ******************************************************************************
  * @file      startup_thm36_gcc.s
  * @author    xinght
  * @version   V1.0.0
  * @date      13-Aug-2019
  * @brief     Copy from stm32f10x project & Change
  *            This module performs:
  *                - Set the initial SP
  *                - Set the initial PC == Reset_Handler,
  *                - Set the vector table entries with the exceptions ISR address
  *                - Configure the clock system and the external SRAM mounted on
  *                  STM3210E-EVAL board to be used as data memory (optional,
  *                  to be enabled by user)
  *                - Branches to main in the C library (which eventually
  *                  calls main()).
  *            After Reset the Cortex-M3 processor is in Thread mode,
  *            priority is Privileged, and the Stack is set to Main.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

  .syntax unified       /*表示使用了统一的汇编语言语法 ARM和THUMB通用的格式*/
  .cpu cortex-m3        /*MCU为ARM Cortex-M3*/
  .fpu softvfp          /*vector float point 使用软浮点*/
  .thumb                /*指定指令集*/

.global  g_pfnVectors   /*定义g_pfnVectors为全局可引用标号 类似extern*/
.global  Default_Handler/*定义Default_Handler为全局可引用标号 类似extern*/

/* start address for the initialization values of the .data section.
defined in linker script */
.word  _sidata          /*在链接脚本中定义了改变量的值*/
/* start address for the .data section. defined in linker script */
.word  _sdata
/* end address for the .data section. defined in linker script */
.word  _edata
/* start address for the .bss section. defined in linker script */
.word  _sbss
/* end address for the .bss section. defined in linker script */
.word  _ebss
/* stack used for SystemInit_ExtMemCtl; always internal RAM used */

/**
 * @brief  This is the code that gets called when the processor first
 *          starts execution following a reset event. Only the absolutely
 *          necessary set is performed, after which the application
 *          supplied main() routine is called.
 * @param  None
 * @retval : None
*/

    .section  .text.Reset_Handler   /*开始新的代码或数据段.text 代码段 .data 初始化数据段  .bss 未初始化数据段*/
  .weak  Reset_Handler      /*Reset_Handler 弱定义*/
  .type  Reset_Handler, %function /*用来指定符号类型*/
Reset_Handler:      /*定义符号 Reset_Handler 并置该符号的值为段当前的地址*/

/* Copy the data segment initializers from flash to SRAM */
  movs  r1, #0      /*将0赋值为r1寄存器*/
  b  LoopCopyDataInit   /*跳转到LoopCopyDataInit*/

CopyDataInit:
  ldr  r3, =_sidata     /*这个地址放在代码段的后面 保存了ram初始化的值*/
  ldr  r3, [r3, r1]     /*从r3指向的flash地址 load 4个字节到r3寄存器*/
  str  r3, [r0, r1]     /*将r3里的值赋予给ram起始地址r0 + r1的ram中*/
  adds  r1, r1, #4      /*r1向后偏移4个字节 方便进行后续ram的初始化*/

LoopCopyDataInit:
  ldr  r0, =_sdata      /*copy 数据段起始地址到r0*/
  ldr  r3, =_edata      /*copy 数据段结束地址到r3*/
  adds  r2, r0, r1
  cmp  r2, r3           /*比较R2与R3*/
  bcc  CopyDataInit     /*如果两者相等则执行下面的语句 两者不等执行ram初始化 从flash中copy ram init data到ram中*/
  ldr  r2, =_sbss       /*将未初始化的ram的起始地址赋给r2*/
  b  LoopFillZerobss    /*跳转执行未初始化ram全部fill成0*/
/* Zero fill the bss segment. */
FillZerobss:
  movs  r3, #0
  str  r3, [r2], #4     /*将寄存器r3的值存储到r2地址 然后r2+4*/

LoopFillZerobss:
  ldr  r3, = _ebss
  cmp  r2, r3
  bcc  FillZerobss      /*同上反复执行 直到所有bss段均被初始化为0*/
/* Call the clock system intitialization function.*/
  bl  SystemInit   /*执行systeminit函数*/
/* Call the application's entry point.*/
  bl  main          /*执行main函数*/
  bx  lr            /*转移到地址lr 等同于mov pc lr*/
.size  Reset_Handler, .-Reset_Handler   /*设定Reset_Handler符号的size属性 不同于EQU重新定义一个符号为大小 size就是当前段地址减去符号之前表示的地址*/

/**
 * @brief  This is the code that gets called when the processor receives an
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 * @param  None
 * @retval None
*/
    .section  .text.Default_Handler,"ax",%progbits  /*定义代码段 Default_Handler ax表示权限 分配内存并且可执行 %progbits 表示类型 为程序数据*/
Default_Handler:
Infinite_Loop:
  b  Infinite_Loop              /*无限循环*/
  .size  Default_Handler, .-Default_Handler
/******************************************************************************
*
* The minimal vector table for a Cortex M3. Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
*******************************************************************************/
   .section  .isr_vector,"a",%progbits  /*定义中断向量表程序段 权限a 分配内存 %progbits表示程序数据*/
  .type  g_pfnVectors, %object  /*定义g_pfnVectors符号的类型是 object 数据对象*/
  .size  g_pfnVectors, .-g_pfnVectors   /*定义g_pfnVectors的size属性*/


g_pfnVectors:
  .word  _Stack_Top                /* Top of Stack          */
  .word  Reset_Handler             /* Reset Handler         */
  .word  NMI_Handler               /* NMI Handler           */
  .word  HardFault_Handler         /* Hard Fault Handler    */
  .word  MemManage_Handler         /* MPU Fault Handler     */
  .word  BusFault_Handler          /* Bus Fault Handler     */
  .word  UsageFault_Handler        /* Usage Fault Handler   */
  .word  0                         /* Reserved              */
  .word  0                         /* Reserved              */
  .word  0                         /* Reserved              */
  .word  0                         /* Reserved              */
  .word  SVC_Handler               /* SVCall Handler        */
  .word  DebugMon_Handler          /* Debug Monitor Handler */
  .word  0                         /* Reserved              */
  .word  PendSV_Handler            /* PendSV Handler        */
  .word  SysTick_Handler           /* SysTick Handler       */

  .word  RCC_IRQHandler            /* 0:     */
  .word  0                         /* 1:     */
  .word  0                         /* 2:     */
  .word  DMA_IRQHandler            /* 3:     */
  .word  AHBMMU_IRQHandler         /* 4:     */
  .word  0                         /* 5:     */
  .word  0                         /* 6:     */
  .word  MPU_IRQHandler            /* 7:     */
  .word  0                         /* 8:     */
  .word  0                         /* 9:     */
  .word  SM4_IRQHandler            /* 10:    */
  .word  AES_IRQHandler            /* 11:    */
  .word  DES_IRQHandler            /* 12:    */
  .word  PKE_IRQHandler            /* 13:    */
  .word  0                         /* 14:    */
  .word  EGS_IRQHandler            /* 15:    */
  .word  LD_IRQHandler             /* 16:    */
  .word  TRNG_IRQHandler           /* 17:    */
  .word  FD2_IRQHandler            /* 18:    */
  .word  FD3_IRQHandler            /* 19:    */
  .word  VB_SENSOR_IRQHandler      /* 20:    */
  .word  ASH_IRQHandler            /* 21:    */
  .word  WWDT_IRQHandler           /* 22:    */
  .word  TIMER1_IRQHandler         /* 23:    */
  .word  TIMER2_IRQHandler         /* 24:    */
  .word  TIMER3_IRQHandler         /* 25:    */
  .word  TIMER4_IRQHandler         /* 26:    */
  .word  TIMER5_IRQHandler         /* 27:    */
  .word  TIMER6_IRQHandler         /* 28:    */
  .word  0                         /* 29:    */
  .word  0                         /* 30:    */
  .word  0                         /* 31:    */
  .word  0                         /* 32: 0  */
  .word  FLASH1_IRQHandler         /* 33: 1  */
  .word  0                         /* 34: 2  */
  .word  0                         /* 35: 3  */
  .word  GPIO_IRQHandler           /* 36: 4  */
  .word  SPI1_IRQHandler           /* 37: 5  */
  .word  SPI2_IRQHandler           /* 38: 6  */
  .word  SPI3_IRQHandler           /* 39: 7  */
  .word  UART1_IRQHandler          /* 40: 8  */
  .word  UART2_IRQHandler          /* 41: 9  */
  .word  UART3_IRQHandler          /* 42: 10 */
  .word  0                         /* 43: 11 */
  .word  I2C_IRQHandler            /* 44: 12 */
  .word  ISO7816M1_IRQHandler      /* 45: 13 */
  .word  ISO7816M2_IRQHandler      /* 46: 14 */
  .word  ISO7816M3_IRQHandler      /* 47: 15 */
  .word  PWM1_IRQHandler           /* 48: 16 */
  .word  PWM2_IRQHandler           /* 49: 17 */
  .word  DCMI_IRQHandler           /* 50: 18 */
  .word  USB_IRQHandler            /* 51: 19 */
  .word  UART4_IRQHandler          /* 52: 20 */
  .word  ADC_IRQHandler            /* 53: 21 */
  .word  ISO7816S_IRQHandler       /* 54: 22 */
  .word  0                         /* 55: 23 */
  .word  0                         /* 56: 23 */
  .word  0                         /* 57: 23 */
  .word  0                         /* 58: 23 */
  .word  0                         /* 59: 23 */
  .word  0                         /* 60: 23 */
  .word  0                         /* 61: 23 */
  .word  0                         /* 62: 23 */
  .word  0                         /* 63: 23 */
  .word  EXTI0_15_IRQHandler       /* 64: 23 */
  .word  EXTI16_31_IRQHandler      /* 65: 23 */
  .word  EXTI32_47_IRQHandler      /* 66: 23 */
  .word  EXTI48_63_IRQHandler      /* 67: 23 */
  .word  EXTI64_79_IRQHandler      /* 68: 23 */
  .word  EXTI80_IRQHandler         /* 69: 23 */
  .word  EXTI81_IRQHandler         /* 70: 23 */
  .word  EXTI82_IRQHandler         /* 71: 23 */
  .word  EXTI83_IRQHandler         /* 72: 23 */
  .word  EXTI84_IRQHandler         /* 73: 23 */
  .word  EXTI85_IRQHandler         /* 74: 23 */

/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler.
* As they are weak aliases, any function with the same name will override
* this definition.
*
*******************************************************************************/

  .weak  NMI_Handler
  .thumb_set NMI_Handler,Default_Handler

  .weak  HardFault_Handler
  .thumb_set HardFault_Handler,Default_Handler

  .weak  MemManage_Handler
  .thumb_set MemManage_Handler,Default_Handler

  .weak  BusFault_Handler
  .thumb_set BusFault_Handler,Default_Handler

  .weak  UsageFault_Handler
  .thumb_set UsageFault_Handler,Default_Handler

  .weak  SVC_Handler
  .thumb_set SVC_Handler,Default_Handler

  .weak  DebugMon_Handler
  .thumb_set DebugMon_Handler,Default_Handler

  .weak  PendSV_Handler
  .thumb_set PendSV_Handler,Default_Handler

  .weak  SysTick_Handler
  .thumb_set SysTick_Handler,Default_Handler

  .weak  RCC_IRQHandler
  .thumb_set RCC_IRQHandler,Default_Handler

  .weak  DMA_IRQHandler
  .thumb_set DMA_IRQHandler,Default_Handler

  .weak  AHBMMU_IRQHandler
  .thumb_set AHBMMU_IRQHandler,Default_Handler

  .weak  MPU_IRQHandler
  .thumb_set MPU_IRQHandler,Default_Handler

  .weak  SM4_IRQHandler
  .thumb_set SM4_IRQHandler,Default_Handler

  .weak  AES_IRQHandler
  .thumb_set AES_IRQHandler,Default_Handler

  .weak  DES_IRQHandler
  .thumb_set DES_IRQHandler,Default_Handler

  .weak  PKE_IRQHandler
  .thumb_set PKE_IRQHandler,Default_Handler

  .weak  EGS_IRQHandler
  .thumb_set EGS_IRQHandler,Default_Handler

  .weak  LD_IRQHandler
  .thumb_set LD_IRQHandler,Default_Handler

  .weak  TRNG_IRQHandler
  .thumb_set TRNG_IRQHandler,Default_Handler

  .weak  FD2_IRQHandler
  .thumb_set FD2_IRQHandler,Default_Handler

  .weak  FD3_IRQHandler
  .thumb_set FD3_IRQHandler,Default_Handler

  .weak  VB_SENSOR_IRQHandler
  .thumb_set VB_SENSOR_IRQHandler,Default_Handler

  .weak  ASH_IRQHandler
  .thumb_set ASH_IRQHandler,Default_Handler

  .weak  WWDT_IRQHandler
  .thumb_set WWDT_IRQHandler,Default_Handler

  .weak  TIMER1_IRQHandler
  .thumb_set TIMER1_IRQHandler,Default_Handler

  .weak  TIMER2_IRQHandler
  .thumb_set TIMER2_IRQHandler,Default_Handler

  .weak  TIMER3_IRQHandler
  .thumb_set TIMER3_IRQHandler,Default_Handler

  .weak  TIMER4_IRQHandler
  .thumb_set TIMER4_IRQHandler,Default_Handler

  .weak  TIMER5_IRQHandler
  .thumb_set TIMER5_IRQHandler,Default_Handler

  .weak  TIMER6_IRQHandler
  .thumb_set TIMER6_IRQHandler,Default_Handler

  .weak  FLASH1_IRQHandler
  .thumb_set FLASH1_IRQHandler,Default_Handler

  .weak  GPIO_IRQHandler
  .thumb_set GPIO_IRQHandler,Default_Handler

  .weak  SPI1_IRQHandler
  .thumb_set SPI1_IRQHandler,Default_Handler

  .weak  SPI2_IRQHandler
  .thumb_set SPI2_IRQHandler,Default_Handler

  .weak  SPI3_IRQHandler
  .thumb_set SPI3_IRQHandler,Default_Handler

  .weak  UART1_IRQHandler
  .thumb_set UART1_IRQHandler,Default_Handler

  .weak  UART2_IRQHandler
  .thumb_set UART2_IRQHandler,Default_Handler

  .weak  UART3_IRQHandler
  .thumb_set UART3_IRQHandler,Default_Handler

  .weak  I2C_IRQHandler
  .thumb_set I2C_IRQHandler,Default_Handler

  .weak  ISO7816M1_IRQHandler
  .thumb_set ISO7816M1_IRQHandler,Default_Handler

  .weak  ISO7816M2_IRQHandler
  .thumb_set ISO7816M2_IRQHandler,Default_Handler

  .weak  ISO7816M3_IRQHandler
  .thumb_set ISO7816M3_IRQHandler,Default_Handler

  .weak  PWM1_IRQHandler
  .thumb_set PWM1_IRQHandler,Default_Handler

  .weak  PWM2_IRQHandler
  .thumb_set PWM2_IRQHandler,Default_Handler

  .weak  DCMI_IRQHandler
  .thumb_set DCMI_IRQHandler,Default_Handler

  .weak  USB_IRQHandler
  .thumb_set USB_IRQHandler,Default_Handler

  .weak  UART4_IRQHandler
  .thumb_set UART4_IRQHandler,Default_Handler

  .weak  ADC_IRQHandler
  .thumb_set ADC_IRQHandler,Default_Handler

  .weak  ISO7816S_IRQHandler
  .thumb_set ISO7816S_IRQHandler,Default_Handler

  .weak  EXTI0_15_IRQHandler
  .thumb_set EXTI0_15_IRQHandler,Default_Handler

  .weak  EXTI16_31_IRQHandler
  .thumb_set EXTI16_31_IRQHandler,Default_Handler

  .weak  EXTI32_47_IRQHandler
  .thumb_set EXTI32_47_IRQHandler,Default_Handler

  .weak  EXTI48_63_IRQHandler
  .thumb_set EXTI48_63_IRQHandler,Default_Handler

  .weak  EXTI64_79_IRQHandler
  .thumb_set EXTI64_79_IRQHandler,Default_Handler

  .weak  EXTI80_IRQHandler
  .thumb_set EXTI80_IRQHandler,Default_Handler

  .weak  EXTI81_IRQHandler
  .thumb_set EXTI81_IRQHandler,Default_Handler

  .weak  EXTI82_IRQHandler
  .thumb_set EXTI82_IRQHandler,Default_Handler

  .weak  EXTI83_IRQHandler
  .thumb_set EXTI83_IRQHandler,Default_Handler

  .weak  EXTI84_IRQHandler
  .thumb_set EXTI84_IRQHandler,Default_Handler

  .weak  EXTI85_IRQHandler
  .thumb_set EXTI85_IRQHandler,Default_Handler

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
