create_driver lcd8080_driver

set_sw_property min_compatible_hw_version 1.0

set_sw_property hw_class_name LCD_8080

set_sw_property auto_initialize true

add_sw_property supported_bsp_type HAL

set_sw_property bsp_subdirectory drivers

set_sw_property isr_preemption_supported true

set_sw_property supported_interrupt_apis "enhanced_interrupt_api"

add_sw_property c_source HAL/src/lcd8080_controller.c

add_sw_property include_source HAL/inc/lcd8080_controller.h

puts "included lcd8080_driver!"