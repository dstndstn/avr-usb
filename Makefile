F_CPU := 12000000UL
MCU_TARGET     := atmega168

all: keyboard.hex

USB = v-usb/usbdrv/usbdrv.o v-usb/usbdrv/usbdrvasm.o v-usb/usbdrv/oddebug.o

CC := avr-gcc

# UsbKeyboard.h: from vusb-for-arduino-005/libraries/UsbKeyboard/UsbKeyboard.h

CFLAGS := -DF_CPU=$(F_CPU) -Iv-usb/usbdrv -I. -mmcu=$(MCU_TARGET)
LDFLAGS       := -Wl,-Map,$(PRG).map

%.o: %.c
	avr-gcc $(CFLAGS) -c $< -o $@

%.o: %.S
	avr-gcc $(CFLAGS) -c $< -o $@

keyboard.hex: keyboard.o $(USB)
	avr-gcc -o $@ $^
