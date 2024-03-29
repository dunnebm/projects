# Repository Outline

## ARM Cortex-m4 projects

Skills used:
- C programming
- custom linker script
- custom startup code
- GPIO
- Timer used as a pulse-width-modulator for driving servo motors
- Timer used as trigger for periodic ADC sampling
- ADC
- DMA
- SPI
- I2C

### lcd
This project tests the ILI9486 LCD's SPI interface by drawing a red square. The SPI interface is located in
the mystm32lib directory

### mystm32lib
This directory is an archive of API's for commonly used hardware components on my Nucleo board

### pan_tilt_servos
This project consisted of a joystick controlling two servos that were in a pan-tilt configuration. The
joystick-data was sampled by an ADC periodically, and triggered by a timer, then written to SRAM using DMA.
Servos were driven by pulse-width-modulated waveforms using one of the timers on board.

## AXI memory slave
In this project, I designed a component that contained a block of SRAM. The AXI interface was used
to control burst-capable read/write transfers.
  
Skills used:
- VHDL
- Hardware design
- Verification using a VHDL testbench with OSVVM library

## Matrix
This project implementats a matrix class using C++. To test the class, I decided to use Numpy (a Python library) 
because it gives me an excuse to practice Python scripting and socket programming. The Python script sets up a server 
and waits for the test program to send request. These request are the matrix operands and the type of operation. 
With this information, the server performs the desired operation on the desired matrices, and sends back the result.
  
Skill used:
- C++
- Python
- Object oriented programming
- TCP/IP socket programming
- linear algebra

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

![](max10_fpga_projects/lcd_and_camera/LCD_camera_diagram.svg)
