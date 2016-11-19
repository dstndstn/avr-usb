

uchar reportBuffer[4];    // buffer for HID reports [ 1 modifier byte + (le

void send_usb(byte keyStroke) { //, byte modifiers) {
    byte modifiers = 0;
    // Note: We wait until we can send keystroke
    //       so we know the previous keystroke was
    //       sent.
    while (!usbInterruptIsReady());

    memset(reportBuffer, 0, sizeof(reportBuffer));

    reportBuffer[0] = modifiers;
    reportBuffer[1] = keyStroke;
        
    usbSetInterrupt(reportBuffer, sizeof(reportBuffer));

    while (!usbInterruptIsReady());
      
    // This stops endlessly repeating keystrokes:
    memset(reportBuffer, 0, sizeof(reportBuffer));      
    usbSetInterrupt(reportBuffer, sizeof(reportBuffer));
}

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
