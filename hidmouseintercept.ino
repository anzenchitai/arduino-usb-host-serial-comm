#include <Mouse.h> 
#include <Wire.h> 
#include <SPI.h> 
#include <usbhub.h> 
#include <hidboot.h> 

byte bf[3];

USB Usb; 
USBHub Hub(&Usb); 
HIDBoot<USB_HID_PROTOCOL_MOUSE> HidMouse(&Usb); 

int lmb = 0; 
int rmb = 0; 
int mmb = 0;

int dx;
int dy;
  
class MouseRptParser : public MouseReportParser 
{ 
  protected: 
    void OnMouseMove  (MOUSEINFO *mi); 
    void OnLeftButtonUp (MOUSEINFO *mi); 
    void OnLeftButtonDown (MOUSEINFO *mi); 
    void OnRightButtonUp  (MOUSEINFO *mi); 
    void OnRightButtonDown  (MOUSEINFO *mi); 
    void OnMiddleButtonUp (MOUSEINFO *mi); 
    void OnMiddleButtonDown (MOUSEINFO *mi); 
}; 

void MouseRptParser::OnMouseMove(MOUSEINFO *mi) 
{ 
  dx = mi->dX; 
  dy = mi->dY; 
}; 
 
void MouseRptParser::OnLeftButtonUp (MOUSEINFO *mi) 
{ 
  lmb = 0; 
}; 
 
void MouseRptParser::OnLeftButtonDown (MOUSEINFO *mi) 
{ 
  lmb = 1; 
}; 
 
void MouseRptParser::OnRightButtonUp  (MOUSEINFO *mi) 
{ 
  rmb = 0; 
}; 

void MouseRptParser::OnRightButtonDown  (MOUSEINFO *mi) 
{ 
  rmb = 1; 
}; 
 
void MouseRptParser::OnMiddleButtonUp (MOUSEINFO *mi) 
{ 
  mmb = 0; 
}; 

void MouseRptParser::OnMiddleButtonDown (MOUSEINFO *mi) 
{ 
  mmb = 1; 
}; 
 
MouseRptParser Prs; 

void setup()
{ 
  delay(5000); 
  Mouse.begin(); 
  Serial.begin(115200); 
  Serial.setTimeout(1);   
 
  Usb.Init(); 
 
  HidMouse.SetReportParser(0, &Prs); 
} 
 
void loop() 
{ 
  dx = 0;
  dy = 0;
  
  Usb.Task(); 
 
  //Clicking 
  if (lmb == 0)
  { 
    Mouse.release(MOUSE_LEFT); 
  } 
  
  else if (lmb == 1)
  { 
    Mouse.press(MOUSE_LEFT); 
  } 
 
  if (rmb == 0)
  { 
    Mouse.release(MOUSE_RIGHT); 
  } 
 
  else if (rmb == 1)
  { 
    Mouse.press(MOUSE_RIGHT); 
  } 
 
  if (mmb == 0)
  { 
    Mouse.release(MOUSE_MIDDLE); 
  } 
 
  else if (mmb == 1)
  { 
    Mouse.press(MOUSE_MIDDLE); 
  } 
 
  //Moving the mouse with pcinput     
  if (Serial.available())
  { 
  byte x[3] = {0, 0, 0};
  Serial.readBytes(x, 3);
    
  Serial.write(bf[0]);
  Serial.write(bf[1]);
  Serial.write(bf[2]);

  Serial.readBytes(bf, 3);

  dx = (int)x[0] + (int)bf[0]; 
  dy = (int)x[1] + (int)bf[1];
  Mouse.move(dx, dy);

  if(x[2] != 0 || bf[2] != 0)
    Mouse.press();
  else
    Mouse.release();

  memset(bf, 0, 3);
  } 
  
  //Moving the mouse without pcinput 
  else
  { 
    Mouse.move(dx, dy); 
  } 
} 
