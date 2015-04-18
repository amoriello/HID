/*
 Copyright (c) 2014 NicoHood
 See the readme for credit to other people.

 Keyboard NKRO example

 Press a button to write some text to your pc.
 This methode uses the NKRO keyboard which can press up to 113 keys at the same time.
 See official and HID Project documentation for more infos
 https://github.com/NicoHood/HID/wiki/Keyboard-API
*/

const int pinLed = LED_BUILTIN;
const int pinButton = 2;

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // Sends a clean report to the host. This is important on any Arduino type.
  KeyboardNKRO.begin();
}


void loop() {
  if (!digitalRead(pinButton)) {
    digitalWrite(pinLed, HIGH);

    // Same use as the official library, pretty much self explaining
    KeyboardNKRO.println(F("This keyboard can press 113 keys at the same time!"));

    // Demonstrate that keys can be pressed at the same time. Be careful with this!
    //    KeyboardNKRO.press(KEY_F1);
    //    KeyboardNKRO.press(KEY_F2);
    //    KeyboardNKRO.press(KEY_F3);
    //    KeyboardNKRO.press(KEY_F4);
    //    KeyboardNKRO.press(KEY_F5);
    //    KeyboardNKRO.press(KEY_F6);
    //    KeyboardNKRO.press(KEY_F7);
    //    KeyboardNKRO.press(KEY_F8);
    //    KeyboardNKRO.press(KEY_F9);
    //    KeyboardNKRO.press(KEY_F10);
    //    KeyboardNKRO.press(KEY_F11);
    //    KeyboardNKRO.press(KEY_F12);
    //
    //    delay(1000);
    //    KeyboardNKRO.releaseAll();

    // simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }
}

