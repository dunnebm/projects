CC := arm-none-eabi-gcc
CFLAGS := -c -g3 -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -std=gnu11 -o0
LDFLAGS := -g3 -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -std=gnu11 -o0 --specs=nano.specs -Tnucleo-f446re-linker.ld -L../mystm32lib -lmystm32
#SRC := $(wildcard *.c)
#INC := $(wildcard *.h)
#OBJ := $(SRC:.c=.o)

all: final.elf

nucleo-f446re-startup.o: nucleo-f446re-startup.c
	$(CC) $(CFLAGS) $^ -o $@

syscalls.o: syscalls.c
	$(CC) $(CFLAGS) $^ -o $@

display.o: display.c display.h
	$(CC) $(CFLAGS) $< -o $@

main.o: main.c
	$(CC) $(CFLAGS) $^ -o $@

final.elf: main.o nucleo-f446re-startup.o syscalls.o display.o
	$(CC) $^ $(LDFLAGS) -o $@

clean:
	rm -rf *.o *.elf

load:
	openocd -f board/st_nucleo_f4.cfg