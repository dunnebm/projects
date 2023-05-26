# Repository Outline

## ARM Cortex-m4 projects
### lcd
---
### mystm32lib
---
### pan_tilt_servos
---

## AXI memory slave
  In this project, I designed a component that contained a block of SRAM. The AXI interface was used
  to control burst-capable read/write transfers.
  
  Skills used:
  - VHDL
  - Hardware design
  - Verification using a VHDL testbench with OSVVM library

## Max10 FPGA projects
###  lcd_camera
  In this project, I designed hardware to control an LCD and Camera. For software, I wrote drivers for both
  components, and integrated them into the HAL provided by Intel.
  
  Skills used:
  - VHDL
  - System-on-chip design
  - Hardware design
  - Verification using a VHDL testbench with OSVVM library
  - C programming
  - HAL driver development
  - DMA and interrupt-driven programing
  - I2C was used to send commands to the camera
