ENTRY(Reset_Handler)

_stack = 0x20000000 + 1024*128;
_min_stack_size = 0x400;
_min_heap_size = 0x200;

MEMORY
{
  FLASH(rx): ORIGIN = 0x08000000, LENGTH = 512k
  SRAM(rwx): ORIGIN = 0x20000000, LENGTH = 128k
}

SECTIONS
{
  .isr_vectors :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector))
    . = ALIGN(4);
  }> FLASH

  .text :
  {
    . = ALIGN(4);
    _text_start = .;
    *(.text)
    *(.text.*)
    *(.glue_7)
    *(.glue_7t)
    *(.eh_frame)
    . = ALIGN(4);
    _text_end = .;
  }> FLASH

  .rodata :
  {
    . = ALIGN(4);
    _rodata_start = .;
    *(.rodata)
    *(.rodata.*)
    . = ALIGN(4);
    _rodata_end = .;
  }> FLASH

  _la_data = LOADADDR(.data);
  .data :
  {
    . = ALIGN(4);
    _data_start = .;
    *(.data)
    *(.data.*)
    . = ALIGN(4);
    _data_end = .;
  }> SRAM AT> FLASH

  .bss :
  {
    . = ALIGN(4);
    _bss_start = .;
    __bss_start__ = _bss_start;
    *(.bss)
    *(.bss.*)
    *(COMMON)
    . = ALIGN(4);
    _bss_end = .;
    __bss_end__ = _bss_end;
    end = _bss_end;
    _end = _bss_end;
  }> SRAM

  .ARM.attributes 0 : { *(.ARM.attributes) }
}