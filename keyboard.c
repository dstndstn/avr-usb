#include <avr/io.h>
#include "UsbKeyboard.h"

void main() {
    // USB keyboard init
    PORTD = 0;
    DDRD |= ~USBMASK;

    cli();
    usbDeviceDisconnect();
    usbDeviceConnect();
    usbInit();
    sei();
    
    // TODO: Remove the next two lines once we fix
    //       missing first keystroke bug properly.
    memset(reportBuffer, 0, sizeof(reportBuffer));      
    usbSetInterrupt(reportBuffer, sizeof(reportBuffer));


    for (;;) {
        usbPoll();

        send_usb(KEY_H);
        send_usb(KEY_E);
        send_usb(KEY_L);
        send_usb(KEY_L);
        send_usb(KEY_O);

        send_usb(KEY_SPACE);

        send_usb(KEY_W);
        send_usb(KEY_O);
        send_usb(KEY_R);
        send_usb(KEY_L);
        send_usb(KEY_D);
        send_usb(KEY_ENTER);
    }
}
