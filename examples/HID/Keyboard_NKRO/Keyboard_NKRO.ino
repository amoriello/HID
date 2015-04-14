/*

http://www.usb.org/developers/hidpage/Hut1_12v2.pdf
*/

typedef union {
  // NKRO Keyboard report, with keymap
  uint8_t whole8[];
  uint16_t whole16[];
  uint32_t whole32[];
  uint8_t keys[NKRO_KEY_COUNT / 8];
} HID_KeyboardNKROReport_Data_t;

HID_KeyboardNKROReport_Data_t report;

void setup() {
  // put your setup code here, to run once:
  memset(&report, 0x00, sizeof(report));
  HID_SendReport(HID_REPORTID_KEYBOARD, &report, sizeof(report));
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  // press button b
  report.keys[0] = (1 << 5); 
  HID_SendReport(HID_REPORTID_KEYBOARD, &report, sizeof(report));

  memset(&report, 0x00, sizeof(report));
  HID_SendReport(HID_REPORTID_KEYBOARD, &report, sizeof(report));
}
