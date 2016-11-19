#  avrdude -p m168 -c bsd -U flash:w:charger.hex

# To hit RESET:
#  avrdude -p m168 -c bsd -E noreset

PRG            := charger

F_CPU := 12000000UL
MCU_TARGET     := atmega168

# Use minimal vfprintf implementation.
#LDFLAGS += -Wl,-u,vfprintf -lprintf_min
# Use full floating-point vfprintf implementation.
LDFLAGS += -Wl,-u,vfprintf -lprintf_flt -lm
# Use minimal vscanf implementation.
LDFLAGS += -Wl,-u,vfscanf -lscanf_min -lm

OBJCOPY        = avr-objcopy
OBJDUMP        = avr-objdump

HEX := keyboard.hex

all: $(HEX) keyboard.lst

USB = v-usb/usbdrv/usbdrv.o v-usb/usbdrv/usbdrvasm.o v-usb/usbdrv/oddebug.o

CC := avr-gcc

program:
	avrdude -p m168 -c bsd -U flash:w:$(HEX)
.PHONY: program

reset:
	avrdude -p m168 -c bsd -E noreset
.PHONY: reset

# UsbKeyboard.h: from vusb-for-arduino-005/libraries/UsbKeyboard/UsbKeyboard.h

# v-usb: git clone https://github.com/obdev/v-usb.git

CFLAGS := -DF_CPU=$(F_CPU) -Iv-usb/usbdrv -I. -mmcu=$(MCU_TARGET)
#LDFLAGS       := -Wl,-Map,$(PRG).map

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

keyboard.elf: keyboard.o $(USB)
	$(CC) $(CFLAGS) -Wl,-Map,keyboard.map -o $@ $^

%.lst: %.elf
	$(OBJDUMP) -h -S $< > $@

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

clean:
	rm *.elf *.o *.hex *.lst *.map $(USB)
