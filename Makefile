chain=avr-gcc
src=c
mcu=atmega328p
file=blink_led/c/
srcName=main
prgmType=arduino
prgmDev=/dev/ttyACM0
baud=115200

ifeq ($(origin FOLDER), command line)
	file := $(FOLDER)
endif

all: compile hex flash

compile:
	$(chain) -g -mmcu=$(mcu) -o $(file)$(srcName).elf $(file)*.$(src)

hex:
	avr-objcopy -j .text -j .data -O ihex $(file)$(srcName).elf $(file)$(srcName).hex

flash:
	avrdude -v -c $(prgmType) -p $(mcu) -P \
	$(prgmDev) -b $(baud) -D -U flash:w:$(file)$(srcName).hex:i
