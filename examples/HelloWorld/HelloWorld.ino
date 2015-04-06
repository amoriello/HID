/*
 Copyright (c) 2014-2015 NicoHood
 See the readme for credit to other people.

 Hello World Keyboard Beginner example

 Press a button to write some text to your pc.
 See official and HID Project documentation for more information.
*/

const int pinLed = LED_BUILTIN;
const int pinButton = 2;

void setup() {
  // hardware setup
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // Serial setup
  Serial.begin(115200);

  // Sends a clean report to the host. This is important on any Arduino type.
  Keyboard.begin();
}

void loop() {
  // check if button is pressed
  if (digitalRead(pinButton) == LOW) {
    digitalWrite(pinLed, HIGH);

    // Same use as the official library, pretty much self explaining
    Keyboard.println("Hello World");

    // check if Serial port is still working
    Serial.println("Working Serial");

    // simple debounce
    delay(500);
    digitalWrite(pinLed, LOW);
  }
}