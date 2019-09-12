/****************************************************************************
* File name    :    THM36-2.ld
* Function     :    Linker script to configure memory regions for THM36-2
* Author       :    xinght
* Date         :    2019/08/13
* Version      :    v1.0
* Description  :
* ModifyRecord :
****************************************************************************/

/***************************************************************************
************************** Flash Memory Map (512K)*************************
***************************************************************************/
/*           ___________    0x0007_FFFF [512k]
**          |           |
**          |   TMC     |
**          |   LOADER  |
**          |   28k     |
**          |___________|   0x0007_9000 [484k]
**          |           |
**          |   RFU     |
**          |   4k      |
**          |___________|   0x0007_8000 [480k]
**          |           |
**          |   EGIS    |
**          |   32k     |
**          |___________|   0x0007_0000 [448k]
**          |           |
**          |   USER    |
**          |   DATA    |
**          |   8k      |
**          |___________|   0x0006_E000 [440k]
**          |           |
**          |   FP      |
**          |   DATA    |
**          |   312k    |
**          |___________|   0x0002_0000 [128k]
**          |           |
**          |   CODE    |
**          |   127.5k  |
**          |___________|   0x0000_0200 [0.5K]
**          |           |
**          |   RESET   |
**          |___________|   0x0000_0000
***************************************************************************/

/***************************************************************************
************************** SRAM Memory Map ****************************
***************************************************************************/
/*           ___________    0x2007_FFFF
**          |           |
**          |   KSP     |
**          |   192K    |
**          |___________|   0x2005_0000

**           ___________    0x2002_FFFF
**          |           |
**          |   KSP     |
**          |   120K    |
**          |___________|   0x2001_2000
**          |           |
**          |   STACK   |
**          |   8K      |
**          |___________|   0x2001_0000
**          |           |
**          |   HEAP    |
**          |   KSP     |
**          |___________|   0x2001_0000
**          |           |
**          |   DATA    |
**          |___________|   0x2000_0170
**          |           |
**          |   RESET   |
**          |___________|   0x2000_0000
***************************************************************************/
/* higher address of the user mode stack */
_Stack_Top = 0x20012000;

/* default user mode stack size */
_Stack_Size = 0x2000;

/* include the memory spaces definitions sub-script */
/* Memory Spaces Definitions */

MEMORY
{
    RAM1 (xrw)  : ORIGIN = 0x20000170, LENGTH = 0x2FE90
    RESET (xr)  : ORIGIN = 0x00000000, LENGTH = 0x200
    CODE (xr)   : ORIGIN = 0x00000200, LENGTH = 0x1FE00
}

/* include the sections management sub-script for FLASH mode */
/* Sections Definitions */

SECTIONS
{
    /* for Cortex devices, the beginning of the startup code is stored in the .isr_vector section, which goes to FLASH */
    .isr_vector :
    {
    . = ALIGN(4);
        KEEP(*(.isr_vector))            /* Startup code */
    . = ALIGN(4);
    } >RESET

    /* the program code is stored in the .text section, which goes to Flash */
    .text :
    {
        . = ALIGN(4);
        *(.text)                   /* remaining code */
        *(.text*)                 /* remaining code */
        *(.rodata)                 /* read-only data (constants) */
        *(.rodata*)
        *(.glue_7)
        *(.glue_7t)
        KEEP (*(.init))
        KEEP (*(.fini))
        . = ALIGN(4);
        _etext = .;
        /* This is used by the startup in order to initialize the .data secion */
        _sidata = _etext;
    } >CODE

    /* This is the initialized data section
    The program executes knowing that the data is in the RAM
    but the loader puts the initial values in the FLASH (inidata).
    It is one task of the startup to copy the initial values from FLASH to RAM. */
    .data :
    {
        . = ALIGN(4);
        /* This is used by the startup in order to initialize the .data secion */
        _sdata = . ;

        *(.data)
        *(.data.*)

        . = ALIGN(4);
        /* This is used by the startup in order to initialize the .data secion */
        _edata = . ;
    } >RAM1

    /* This is the uninitialized data section */
    .bss :
    {
        . = ALIGN(4);
        /* This is used by the startup in order to initialize the .bss secion */
        _sbss = .;

        *(.bss)
        *(COMMON)

        . = ALIGN(4);
        /* This is used by the startup in order to initialize the .bss secion */
        _ebss = . ;
    } >RAM1

    PROVIDE ( end = _ebss );
    PROVIDE ( _end = _ebss );

    /* This is the user stack section
    This is just to check that there is enough RAM left for the User mode stack
    It should generate an error if it's full.
     */
    ._usrstack :
    {
        . = ALIGN(4);
        _susrstack = .;

        . = . + _Stack_Size ;

        . = ALIGN(4);
        _eusrstack = .;
    } >RAM1

    /* after that it's only debugging information. */
    /* remove the debugging information from the standard libraries */
    /DISCARD/ :
    {
        libc.a ( * )
        libm.a ( * )
        libgcc.a ( * )
    }
}
