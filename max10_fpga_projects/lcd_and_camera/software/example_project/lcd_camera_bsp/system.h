/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'Nios2' in SOPC Builder design 'Computer_System'
 * SOPC Builder design path: C:/intelfpga_lite/20.1/university_program/computer_systems/de10-lite/de10-lite_computer/verilog/LCD_Camera_Computer_System/Computer_System.sopcinfo
 *
 * Generated: Wed May 17 16:09:31 CDT 2023
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2_gen2"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x0a000020
#define ALT_CPU_CPU_ARCH_NIOS2_R1
#define ALT_CPU_CPU_FREQ 100000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "fast"
#define ALT_CPU_DATA_ADDR_WIDTH 0x20
#define ALT_CPU_DCACHE_LINE_SIZE 0
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_DCACHE_SIZE 0
#define ALT_CPU_EXCEPTION_ADDR 0x00000020
#define ALT_CPU_FLASH_ACCELERATOR_LINES 0
#define ALT_CPU_FLASH_ACCELERATOR_LINE_SIZE 0
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 100000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 1
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 1
#define ALT_CPU_HARDWARE_MULX_PRESENT 1
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_DIVISION_ERROR_EXCEPTION
#define ALT_CPU_HAS_EXTRA_EXCEPTION_INFO
#define ALT_CPU_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 32
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_ICACHE_SIZE 4096
#define ALT_CPU_INST_ADDR_WIDTH 0x1c
#define ALT_CPU_NAME "Nios2"
#define ALT_CPU_NUM_OF_SHADOW_REG_SETS 0
#define ALT_CPU_OCI_VERSION 1
#define ALT_CPU_RESET_ADDR 0x00000000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x0a000020
#define NIOS2_CPU_ARCH_NIOS2_R1
#define NIOS2_CPU_FREQ 100000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "fast"
#define NIOS2_DATA_ADDR_WIDTH 0x20
#define NIOS2_DCACHE_LINE_SIZE 0
#define NIOS2_DCACHE_LINE_SIZE_LOG2 0
#define NIOS2_DCACHE_SIZE 0
#define NIOS2_EXCEPTION_ADDR 0x00000020
#define NIOS2_FLASH_ACCELERATOR_LINES 0
#define NIOS2_FLASH_ACCELERATOR_LINE_SIZE 0
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 1
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 1
#define NIOS2_HARDWARE_MULX_PRESENT 1
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_DIVISION_ERROR_EXCEPTION
#define NIOS2_HAS_EXTRA_EXCEPTION_INFO
#define NIOS2_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 32
#define NIOS2_ICACHE_LINE_SIZE_LOG2 5
#define NIOS2_ICACHE_SIZE 4096
#define NIOS2_INST_ADDR_WIDTH 0x1c
#define NIOS2_NUM_OF_SHADOW_REG_SETS 0
#define NIOS2_OCI_VERSION 1
#define NIOS2_RESET_ADDR 0x00000000


/*
 * Custom instruction macros
 *
 */

#define ALT_CI_NIOS2_FLOATING_POINT(n,A,B) __builtin_custom_inii(ALT_CI_NIOS2_FLOATING_POINT_N+(n&ALT_CI_NIOS2_FLOATING_POINT_N_MASK),(A),(B))
#define ALT_CI_NIOS2_FLOATING_POINT_N 0xfc
#define ALT_CI_NIOS2_FLOATING_POINT_N_MASK ((1<<2)-1)


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_I2C
#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_NEW_SDRAM_CONTROLLER
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_TIMER
#define __ALTERA_NIOS2_GEN2
#define __ALTERA_NIOS_CUSTOM_INSTR_FLOATING_POINT
#define __DMA_AVALON_ST_SINK_TO_MM_MASTER
#define __LCD8080


/*
 * HEX3_HEX0 configuration
 *
 */

#define ALT_MODULE_CLASS_HEX3_HEX0 altera_avalon_pio
#define HEX3_HEX0_BASE 0xff200020
#define HEX3_HEX0_BIT_CLEARING_EDGE_REGISTER 0
#define HEX3_HEX0_BIT_MODIFYING_OUTPUT_REGISTER 0
#define HEX3_HEX0_CAPTURE 0
#define HEX3_HEX0_DATA_WIDTH 32
#define HEX3_HEX0_DO_TEST_BENCH_WIRING 0
#define HEX3_HEX0_DRIVEN_SIM_VALUE 0
#define HEX3_HEX0_EDGE_TYPE "NONE"
#define HEX3_HEX0_FREQ 100000000
#define HEX3_HEX0_HAS_IN 0
#define HEX3_HEX0_HAS_OUT 1
#define HEX3_HEX0_HAS_TRI 0
#define HEX3_HEX0_IRQ -1
#define HEX3_HEX0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define HEX3_HEX0_IRQ_TYPE "NONE"
#define HEX3_HEX0_NAME "/dev/HEX3_HEX0"
#define HEX3_HEX0_RESET_VALUE 0
#define HEX3_HEX0_SPAN 16
#define HEX3_HEX0_TYPE "altera_avalon_pio"


/*
 * HEX5_HEX4 configuration
 *
 */

#define ALT_MODULE_CLASS_HEX5_HEX4 altera_avalon_pio
#define HEX5_HEX4_BASE 0xff200030
#define HEX5_HEX4_BIT_CLEARING_EDGE_REGISTER 0
#define HEX5_HEX4_BIT_MODIFYING_OUTPUT_REGISTER 0
#define HEX5_HEX4_CAPTURE 0
#define HEX5_HEX4_DATA_WIDTH 16
#define HEX5_HEX4_DO_TEST_BENCH_WIRING 0
#define HEX5_HEX4_DRIVEN_SIM_VALUE 0
#define HEX5_HEX4_EDGE_TYPE "NONE"
#define HEX5_HEX4_FREQ 100000000
#define HEX5_HEX4_HAS_IN 0
#define HEX5_HEX4_HAS_OUT 1
#define HEX5_HEX4_HAS_TRI 0
#define HEX5_HEX4_IRQ -1
#define HEX5_HEX4_IRQ_INTERRUPT_CONTROLLER_ID -1
#define HEX5_HEX4_IRQ_TYPE "NONE"
#define HEX5_HEX4_NAME "/dev/HEX5_HEX4"
#define HEX5_HEX4_RESET_VALUE 0
#define HEX5_HEX4_SPAN 16
#define HEX5_HEX4_TYPE "altera_avalon_pio"


/*
 * Interval_Timer configuration
 *
 */

#define ALT_MODULE_CLASS_Interval_Timer altera_avalon_timer
#define INTERVAL_TIMER_ALWAYS_RUN 0
#define INTERVAL_TIMER_BASE 0xff202000
#define INTERVAL_TIMER_COUNTER_SIZE 32
#define INTERVAL_TIMER_FIXED_PERIOD 0
#define INTERVAL_TIMER_FREQ 100000000
#define INTERVAL_TIMER_IRQ 3
#define INTERVAL_TIMER_IRQ_INTERRUPT_CONTROLLER_ID 0
#define INTERVAL_TIMER_LOAD_VALUE 12499999
#define INTERVAL_TIMER_MULT 0.001
#define INTERVAL_TIMER_NAME "/dev/Interval_Timer"
#define INTERVAL_TIMER_PERIOD 125.0
#define INTERVAL_TIMER_PERIOD_UNITS "ms"
#define INTERVAL_TIMER_RESET_OUTPUT 0
#define INTERVAL_TIMER_SNAPSHOT 1
#define INTERVAL_TIMER_SPAN 32
#define INTERVAL_TIMER_TICKS_PER_SEC 8
#define INTERVAL_TIMER_TIMEOUT_PULSE_OUTPUT 0
#define INTERVAL_TIMER_TYPE "altera_avalon_timer"


/*
 * Interval_Timer_2 configuration
 *
 */

#define ALT_MODULE_CLASS_Interval_Timer_2 altera_avalon_timer
#define INTERVAL_TIMER_2_ALWAYS_RUN 0
#define INTERVAL_TIMER_2_BASE 0xff202020
#define INTERVAL_TIMER_2_COUNTER_SIZE 32
#define INTERVAL_TIMER_2_FIXED_PERIOD 0
#define INTERVAL_TIMER_2_FREQ 100000000
#define INTERVAL_TIMER_2_IRQ 4
#define INTERVAL_TIMER_2_IRQ_INTERRUPT_CONTROLLER_ID 0
#define INTERVAL_TIMER_2_LOAD_VALUE 12499999
#define INTERVAL_TIMER_2_MULT 0.001
#define INTERVAL_TIMER_2_NAME "/dev/Interval_Timer_2"
#define INTERVAL_TIMER_2_PERIOD 125.0
#define INTERVAL_TIMER_2_PERIOD_UNITS "ms"
#define INTERVAL_TIMER_2_RESET_OUTPUT 0
#define INTERVAL_TIMER_2_SNAPSHOT 1
#define INTERVAL_TIMER_2_SPAN 32
#define INTERVAL_TIMER_2_TICKS_PER_SEC 8
#define INTERVAL_TIMER_2_TIMEOUT_PULSE_OUTPUT 0
#define INTERVAL_TIMER_2_TYPE "altera_avalon_timer"


/*
 * JTAG_UART configuration
 *
 */

#define ALT_MODULE_CLASS_JTAG_UART altera_avalon_jtag_uart
#define JTAG_UART_BASE 0xff201000
#define JTAG_UART_IRQ 2
#define JTAG_UART_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_UART_NAME "/dev/JTAG_UART"
#define JTAG_UART_READ_DEPTH 64
#define JTAG_UART_READ_THRESHOLD 8
#define JTAG_UART_SPAN 8
#define JTAG_UART_TYPE "altera_avalon_jtag_uart"
#define JTAG_UART_WRITE_DEPTH 64
#define JTAG_UART_WRITE_THRESHOLD 8


/*
 * LEDs configuration
 *
 */

#define ALT_MODULE_CLASS_LEDs altera_avalon_pio
#define LEDS_BASE 0xff200000
#define LEDS_BIT_CLEARING_EDGE_REGISTER 0
#define LEDS_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LEDS_CAPTURE 0
#define LEDS_DATA_WIDTH 10
#define LEDS_DO_TEST_BENCH_WIRING 0
#define LEDS_DRIVEN_SIM_VALUE 0
#define LEDS_EDGE_TYPE "NONE"
#define LEDS_FREQ 100000000
#define LEDS_HAS_IN 0
#define LEDS_HAS_OUT 1
#define LEDS_HAS_TRI 0
#define LEDS_IRQ -1
#define LEDS_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LEDS_IRQ_TYPE "NONE"
#define LEDS_NAME "/dev/LEDs"
#define LEDS_RESET_VALUE 0
#define LEDS_SPAN 16
#define LEDS_TYPE "altera_avalon_pio"


/*
 * Pushbuttons configuration
 *
 */

#define ALT_MODULE_CLASS_Pushbuttons altera_avalon_pio
#define PUSHBUTTONS_BASE 0xff200050
#define PUSHBUTTONS_BIT_CLEARING_EDGE_REGISTER 1
#define PUSHBUTTONS_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PUSHBUTTONS_CAPTURE 1
#define PUSHBUTTONS_DATA_WIDTH 2
#define PUSHBUTTONS_DO_TEST_BENCH_WIRING 1
#define PUSHBUTTONS_DRIVEN_SIM_VALUE 0
#define PUSHBUTTONS_EDGE_TYPE "FALLING"
#define PUSHBUTTONS_FREQ 100000000
#define PUSHBUTTONS_HAS_IN 1
#define PUSHBUTTONS_HAS_OUT 0
#define PUSHBUTTONS_HAS_TRI 0
#define PUSHBUTTONS_IRQ 1
#define PUSHBUTTONS_IRQ_INTERRUPT_CONTROLLER_ID 0
#define PUSHBUTTONS_IRQ_TYPE "EDGE"
#define PUSHBUTTONS_NAME "/dev/Pushbuttons"
#define PUSHBUTTONS_RESET_VALUE 0
#define PUSHBUTTONS_SPAN 16
#define PUSHBUTTONS_TYPE "altera_avalon_pio"


/*
 * SDRAM configuration
 *
 */

#define ALT_MODULE_CLASS_SDRAM altera_avalon_new_sdram_controller
#define SDRAM_BASE 0x0
#define SDRAM_CAS_LATENCY 3
#define SDRAM_CONTENTS_INFO
#define SDRAM_INIT_NOP_DELAY 0.0
#define SDRAM_INIT_REFRESH_COMMANDS 2
#define SDRAM_IRQ -1
#define SDRAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SDRAM_IS_INITIALIZED 1
#define SDRAM_NAME "/dev/SDRAM"
#define SDRAM_POWERUP_DELAY 100.0
#define SDRAM_REFRESH_PERIOD 15.625
#define SDRAM_REGISTER_DATA_IN 1
#define SDRAM_SDRAM_ADDR_WIDTH 0x19
#define SDRAM_SDRAM_BANK_WIDTH 2
#define SDRAM_SDRAM_COL_WIDTH 10
#define SDRAM_SDRAM_DATA_WIDTH 16
#define SDRAM_SDRAM_NUM_BANKS 4
#define SDRAM_SDRAM_NUM_CHIPSELECTS 1
#define SDRAM_SDRAM_ROW_WIDTH 13
#define SDRAM_SHARED_DATA 0
#define SDRAM_SIM_MODEL_BASE 1
#define SDRAM_SPAN 67108864
#define SDRAM_STARVATION_INDICATOR 0
#define SDRAM_TRISTATE_BRIDGE_SLAVE ""
#define SDRAM_TYPE "altera_avalon_new_sdram_controller"
#define SDRAM_T_AC 5.5
#define SDRAM_T_MRD 3
#define SDRAM_T_RCD 20.0
#define SDRAM_T_RFC 70.0
#define SDRAM_T_RP 20.0
#define SDRAM_T_WR 14.0


/*
 * Slider_Switches configuration
 *
 */

#define ALT_MODULE_CLASS_Slider_Switches altera_avalon_pio
#define SLIDER_SWITCHES_BASE 0xff200040
#define SLIDER_SWITCHES_BIT_CLEARING_EDGE_REGISTER 0
#define SLIDER_SWITCHES_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SLIDER_SWITCHES_CAPTURE 0
#define SLIDER_SWITCHES_DATA_WIDTH 10
#define SLIDER_SWITCHES_DO_TEST_BENCH_WIRING 1
#define SLIDER_SWITCHES_DRIVEN_SIM_VALUE 0
#define SLIDER_SWITCHES_EDGE_TYPE "NONE"
#define SLIDER_SWITCHES_FREQ 100000000
#define SLIDER_SWITCHES_HAS_IN 1
#define SLIDER_SWITCHES_HAS_OUT 0
#define SLIDER_SWITCHES_HAS_TRI 0
#define SLIDER_SWITCHES_IRQ -1
#define SLIDER_SWITCHES_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SLIDER_SWITCHES_IRQ_TYPE "NONE"
#define SLIDER_SWITCHES_NAME "/dev/Slider_Switches"
#define SLIDER_SWITCHES_RESET_VALUE 0
#define SLIDER_SWITCHES_SPAN 16
#define SLIDER_SWITCHES_TYPE "altera_avalon_pio"


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "MAX 10"
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/JTAG_UART"
#define ALT_STDERR_BASE 0xff201000
#define ALT_STDERR_DEV JTAG_UART
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/JTAG_UART"
#define ALT_STDIN_BASE 0xff201000
#define ALT_STDIN_DEV JTAG_UART
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/JTAG_UART"
#define ALT_STDOUT_BASE 0xff201000
#define ALT_STDOUT_DEV JTAG_UART
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "Computer_System"


/*
 * dma_avalon_st_sink_to_mm_master_0 configuration
 *
 */

#define ALT_MODULE_CLASS_dma_avalon_st_sink_to_mm_master_0 dma_avalon_st_sink_to_mm_master
#define DMA_AVALON_ST_SINK_TO_MM_MASTER_0_BASE 0x4000040
#define DMA_AVALON_ST_SINK_TO_MM_MASTER_0_IRQ 5
#define DMA_AVALON_ST_SINK_TO_MM_MASTER_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define DMA_AVALON_ST_SINK_TO_MM_MASTER_0_NAME "/dev/dma_avalon_st_sink_to_mm_master_0"
#define DMA_AVALON_ST_SINK_TO_MM_MASTER_0_SPAN 8
#define DMA_AVALON_ST_SINK_TO_MM_MASTER_0_TYPE "dma_avalon_st_sink_to_mm_master"


/*
 * hal configuration
 *
 */

#define ALT_INCLUDE_INSTRUCTION_RELATED_EXCEPTION_API
#define ALT_MAX_FD 32
#define ALT_SYS_CLK INTERVAL_TIMER
#define ALT_TIMESTAMP_CLK none


/*
 * i2c configuration
 *
 */

#define ALT_MODULE_CLASS_i2c altera_avalon_i2c
#define I2C_BASE 0x4000000
#define I2C_FIFO_DEPTH 4
#define I2C_FREQ 100000000
#define I2C_IRQ 0
#define I2C_IRQ_INTERRUPT_CONTROLLER_ID 0
#define I2C_NAME "/dev/i2c"
#define I2C_SPAN 64
#define I2C_TYPE "altera_avalon_i2c"
#define I2C_USE_AV_ST 0


/*
 * lcd8080 configuration
 *
 */

#define ALT_MODULE_CLASS_lcd8080 lcd8080
#define LCD8080_BASE 0x4000048
#define LCD8080_IRQ -1
#define LCD8080_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LCD8080_NAME "/dev/lcd8080"
#define LCD8080_SPAN 4
#define LCD8080_TYPE "lcd8080"

#endif /* __SYSTEM_H_ */
