#include <avr/io.h>
#include <util/delay.h>

#include "UsbKeyboard.h"

void main() {
    // USB keyboard init
    PORTC = 0;
    DDRC |= ~USBMASK;

    DDRB = 0x3;

    cli();
    usbDeviceDisconnect();
    usbDeviceConnect();
    usbInit();
    sei();

    // TODO: Remove the next two lines once we fix
    //       missing first keystroke bug properly.
    memset(reportBuffer, 0, sizeof(reportBuffer));      
    usbSetInterrupt(reportBuffer, sizeof(reportBuffer));

    int i;

    PORTB = 1;
    for (i=0; i<40; i++) {
        // Must be called ~ every 50 ms
        usbPoll();
        _delay_ms(25);
    }
    PORTB = 0;

    for (i=0;; i++) {

        if (i % 64 == 0) {
            PORTB = 3;
        } else if (i % 64 == 32) {
            PORTB = 0;
        }
        // Must be called ~ every 50 ms
        usbPoll();

        _delay_ms(25);

        if (i % 32 == 0) {
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
}
