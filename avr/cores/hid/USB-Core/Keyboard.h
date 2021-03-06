/*
Keyboard.h
Copyright (c) 2005-2014 Arduino.  All right reserved.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

/*
Copyright (c) 2014 NicoHood
See the readme for credit to other people.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef __KEYBOARDAPI__
#define __KEYBOARDAPI__

// to access the HID_SendReport via USBAPI.h, report number and the Print class
#include "Arduino.h"

//================================================================================
//================================================================================
//	Keyboard

#define KEY_PRINT			0xCE
#define KEY_NUM_LOCK		0xDB
#define KEY_SCROLL_LOCK		0xCF
#define KEY_PAUSE			0xD0
#define KEY_MENU			0xED // 0x65 in the official docs

#define KEY_LEFT_CTRL		0x80
#define KEY_LEFT_SHIFT		0x81
#define KEY_LEFT_ALT		0x82
#define KEY_LEFT_GUI		0x83
#define KEY_LEFT_WINDOWS KEY_LEFT_GUI
#define KEY_RIGHT_CTRL		0x84
#define KEY_RIGHT_SHIFT		0x85
#define KEY_RIGHT_ALT		0x86
#define KEY_RIGHT_GUI		0x87
#define KEY_RIGHT_WINDOWS KEY_RIGHT_GUI

#define KEY_UP_ARROW		0xDA
#define KEY_DOWN_ARROW		0xD9
#define KEY_LEFT_ARROW		0xD8
#define KEY_RIGHT_ARROW		0xD7
#define KEY_BACKSPACE		0xB2
#define KEY_TAB				0xB3
#define KEY_RETURN			0xB0
#define KEY_ESC				0xB1
#define KEY_INSERT			0xD1
#define KEY_DELETE			0xD4
#define KEY_PAGE_UP			0xD3
#define KEY_PAGE_DOWN		0xD6
#define KEY_HOME			0xD2
#define KEY_END				0xD5
#define KEY_CAPS_LOCK		0xC1
#define KEY_F1				0xC2
#define KEY_F2				0xC3
#define KEY_F3				0xC4
#define KEY_F4				0xC5
#define KEY_F5				0xC6
#define KEY_F6				0xC7
#define KEY_F7				0xC8
#define KEY_F8				0xC9
#define KEY_F9				0xCA
#define KEY_F10				0xCB
#define KEY_F11				0xCC
#define KEY_F12				0xCD

#define LED_NUM_LOCK			0x01
#define LED_CAPS_LOCK			0x02
#define LED_SCROLL_LOCK			0x04

//Raw Keyboard definitions
#define RAW_KEYBOARD_LEFT_CTRL   (1 << 0)
#define RAW_KEYBOARD_LEFT_SHIFT  (1 << 1)
#define RAW_KEYBOARD_LEFT_ALT    (1 << 2)
#define RAW_KEYBOARD_LEFT_GUI  	 (1 << 3)
#define RAW_KEYBOARD_RIGHT_CTRL  (1 << 4)
#define RAW_KEYBOARD_RIGHT_SHIFT (1 << 5)
#define RAW_KEYBOARD_RIGHT_ALT   (1 << 6)
#define RAW_KEYBOARD_RIGHT_GUI 	 (1 << 7)

#define RAW_KEYBOARD_KEY(key) ((key>='a' && key<='z') ? (0x04 + key-'a') :\
(key>='A' && key<='Z') ? (0x04 + key-'A') : (key>='1' && key<='9') ? (0x1E + key-'1') : 0x27)

#define RAW_KEYBOARD_UP_ARROW		0x52
#define RAW_KEYBOARD_DOWN_ARROW		0x51
#define RAW_KEYBOARD_LEFT_ARROW		0x50
#define RAW_KEYBOARD_RIGHT_ARROW	0x4F
#define RAW_KEYBOARD_SPACEBAR		0x2C
#define RAW_KEYBOARD_BACKSPACE		0x2A
#define RAW_KEYBOARD_TAB			0x2B
#define RAW_KEYBOARD_RETURN			0x28
#define RAW_KEYBOARD_ESC			0x29
#define RAW_KEYBOARD_INSERT			0x49
#define RAW_KEYBOARD_DELETE			0x4C
#define RAW_KEYBOARD_PAGE_UP		0x4B
#define RAW_KEYBOARD_PAGE_DOWN		0x4E
#define RAW_KEYBOARD_HOME			0x4A
#define RAW_KEYBOARD_END			0x4D
#define RAW_KEYBOARD_CAPS_LOCK		0x39
#define RAW_KEYBOARD_F1				0x3A
#define RAW_KEYBOARD_F2				0x3B
#define RAW_KEYBOARD_F3				0x3C
#define RAW_KEYBOARD_F4				0x3D
#define RAW_KEYBOARD_F5				0x3E
#define RAW_KEYBOARD_F6				0x3F
#define RAW_KEYBOARD_F7				0x40
#define RAW_KEYBOARD_F8				0x41
#define RAW_KEYBOARD_F9				0x42
#define RAW_KEYBOARD_F10			0x43
#define RAW_KEYBOARD_F11			0x44
#define RAW_KEYBOARD_F12			0x45
#define RAW_KEYBOARD_PRINT			0x46
#define RAW_KEYBOARD_SCROLL_LOCK	0x47
#define RAW_KEYBOARD_PAUSE			0x48

typedef union{
	// Low level key report: up to 6 keys and shift, ctrl etc at once
	uint8_t whole8[];
	uint16_t whole16[];
	uint32_t whole32[];
	struct{
		uint8_t modifiers;
		uint8_t reserved;
		uint8_t keys[6];
	};
} HID_KeyboardReport_Data_t;

class Keyboard_ : public Print
{
protected:
	HID_KeyboardReport_Data_t _keyReport;
	void sendReport(HID_KeyboardReport_Data_t* keys);
public:
	inline Keyboard_(void){
		// empty
	}

	inline void begin(void){
		// edit by NicoHood
		end();
	}

	inline void end(void){
		// edit by NicoHood
		releaseAll();
	}

	size_t write(uint8_t k);
	size_t press(uint8_t k);
	size_t release(uint8_t k);
	void releaseAll(void);

	size_t writeKeycode(uint8_t k);
	size_t pressKeycode(uint8_t k);
	size_t releaseKeycode(uint8_t k);
	size_t addKeycodeToReport(uint8_t k);
	size_t removeKeycodeFromReport(uint8_t k);

#if defined(HID_KEYBOARD_LEDS_ENABLED)
	inline uint8_t getLeds(void){ return hid_keyboard_leds; }
#endif
};
extern Keyboard_ Keyboard;

#endif
