/*
  HID.h

  Copyright (c) 2015, Arduino LLC
  Original code (pre-library): Copyright (c) 2011, Peter Barrett

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

#pragma once

#define HID_h

#include <Arduino.h>

#if defined(USBCON)

#define _USING_HID

//================================================================================
//================================================================================
//  HID 'Driver'

#define HID_GET_REPORT        0x01
#define HID_GET_IDLE          0x02
#define HID_GET_PROTOCOL      0x03
#define HID_SET_REPORT        0x09
#define HID_SET_IDLE          0x0A
#define HID_SET_PROTOCOL      0x0B

#define HID_HID_DESCRIPTOR_TYPE         0x21
#define HID_REPORT_DESCRIPTOR_TYPE      0x22
#define HID_PHYSICAL_DESCRIPTOR_TYPE    0x23

class HIDDevice;

typedef struct
{
  u8 len;     // 9
  u8 dtype;   // 0x21
  u8 addr;
  u8  versionL; // 0x101
  u8  versionH; // 0x101
  u8  country;
  u8  desctype; // 0x22 report
  u8  descLenL;
  u8  descLenH;
} HIDDescDescriptor;

typedef struct 
{
  InterfaceDescriptor     hid;
  HIDDescDescriptor     desc;
  EndpointDescriptor      in;
} HIDDescriptor;

#include "USBDevice.h"

class HID_ : private CUSBDevice
{
public:
  HID_(void);
  operator bool();
  
  // Only access this class via the HIDDevice
private:
  friend HIDDevice;
  int begin(void);
  void SendReport(uint8_t id, const void* data, int len);
  void AppendDescriptor(HIDDevice* device);
  void SetInterface(InterfaceDescriptor interface);
  
  // TODO virtual required here again?
  virtual bool setup(USBSetup& setup, u8 i);
  virtual int getInterface(u8* interfaceNum);
  virtual int getDescriptor(int8_t t);
  uint8_t endpointType[1];
  
  // Static functions
  static int HID_GetInterface(u8* interfaceNum);
  static int HID_GetDescriptor(int8_t t);
  static bool HID_Setup(USBSetup& setup, u8 i);
  
  // Static variables
  static uint8_t HID_ENDPOINT_INT;
  static uint8_t HID_INTERFACE;
  static HIDDescriptor _hidInterface;
  static HIDDevice* rootDevice;
  static uint16_t sizeof_hidReportDescriptor;
  static uint8_t modules_count;
  static uint8_t _hid_protocol;
  static uint8_t _hid_idle;
};

#define HID_TX HID_ENDPOINT_INT

#define D_HIDREPORT(_descriptorLength) \
  { 9, 0x21, 0x1, 0x1, 0, 1, 0x22, _descriptorLength & 0xFF, _descriptorLength >> 8 }

#define WEAK __attribute__ ((weak))

#endif
