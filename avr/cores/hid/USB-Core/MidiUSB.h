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

#ifndef __MIDIUSB__
#define __MIDIUSB__

#include "Arduino.h"

#if defined(USBCON)

#include "USBDesc.h"
#include "USBCore.h"

//================================================================================
//================================================================================
//  MIDI_USB

// edit by NicoHood
#ifndef MIDI_BUFFER_SIZE
#if (RAMEND < 1000)
#define MIDI_BUFFER_SIZE 16
#else
#define MIDI_BUFFER_SIZE 64
#endif
#endif

struct midi_buffer
{
	unsigned char buffer[MIDI_BUFFER_SIZE];
	volatile int head;
	volatile int tail;
};

typedef struct
{
	uint8_t type;
	uint8_t m1;
	uint8_t m2;
	uint8_t m3;
} MIDIEvent;

extern const MIDIEvent MIDI_EVENT_NONE;

class MIDIUSB_
{
private:
	midi_buffer _rx_buffer;
public:

	virtual int available(void);
	virtual void accept(void);
	virtual MIDIEvent peek(void);
	virtual MIDIEvent read(void);
	virtual void flush(void);
	virtual size_t write(MIDIEvent);
	operator bool();
};
extern MIDIUSB_ MIDIUSB;

#endif /* if defined(USBCON) */

#endif