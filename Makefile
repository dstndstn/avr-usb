
all:
	(cd v-usb && make F_CPU=12000000)
	$(MAKE) keyboard.hex


USB = v-usb/usbdrv/usbdrv.o v-usb/usbdrv/usbdrvasm.o v-usb/usbdrv/oddebug.o

# UsbKeyboard.h: from vusb-for-arduino-005/libraries/UsbKeyboard/UsbKeyboard.h

%.o: %.c
	avr-gcc -c $<

keyboard.hex: keyboard.c $(USB)
	avr-gcc -Iv-usb/usbdrv -c $<
