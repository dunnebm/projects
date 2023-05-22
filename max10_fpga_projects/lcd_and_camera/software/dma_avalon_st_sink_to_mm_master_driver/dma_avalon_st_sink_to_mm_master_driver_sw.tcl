create_driver dma_avalon_st_sink_to_mm_master_driver

set_sw_property min_compatible_hw_version 1.0

set_sw_property hw_class_name dma_avalon_st_sink_to_mm_master

set_sw_property auto_initialize true

add_sw_property supported_bsp_type HAL

set_sw_property bsp_subdirectory drivers

set_sw_property isr_preemption_supported true

set_sw_property supported_interrupt_apis "enhanced_interrupt_api"

add_sw_property c_source HAL/src/dma_avalon_st_sink_to_mm_master.c

add_sw_property include_source HAL/inc/dma_avalon_st_sink_to_mm_master.h

puts "included dma_avalon_st_sink_to_mm_master_driver!"