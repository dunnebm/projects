CFLAGS := -c -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -std=gnu11 -o0

SRC := $(wildcard *.c)
INC := $(wildcard *.h)
OBJ := $(SRC:.c=.o)

all: libmystm32.a

cortex-m4.o: cortex-m4.c cortex-m4.h
	arm-none-eabi-gcc $(CFLAGS) $< -o $@

gpio.o: gpio.c gpio.h
	arm-none-eabi-gcc $(CFLAGS) $< -o $@

usart.o: usart.c usart.h
	arm-none-eabi-gcc $(CFLAGS) $< -o $@

adc.o: adc.c adc.h
	arm-none-eabi-gcc $(CFLAGS) $< -o $@

dma.o: dma.c dma.h
	arm-none-eabi-gcc $(CFLAGS) $< -o $@

tim.o: tim.c tim.h
	arm-none-eabi-gcc $(CFLAGS) $< -o $@

exti.o: exti.c exti.h
	arm-none-eabi-gcc $(CFLAGS) $< -o $@

syscfg.o: syscfg.c syscfg.h
	arm-none-eabi-gcc $(CFLAGS) $< -o $@

libmystm32.a: $(OBJ)
	arm-none-eabi-ar -rcs $@ $(OBJ)
	
clean:
	rm -rf *.o *.a