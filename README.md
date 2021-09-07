# Arduino USB Host / HID Mouse

Standalone USB host mouse proxy. This sketch includes a HID mouse and can take
commands from the device it is connected to. Reads the incoming bytes through 
serial port, then executes. It basically intercepts HID signals and overwrites them.


### Usage

###### Takes a byte and a buffer. You can R/W as many bytes as you need. 
```cpp
writeSerialPort->(&x, buffer) // X pos
writeSerialPort->(&y, buffer) // Y pos
writeSerialPort->(&lmb, buffer) // Left Mouse Button
```


###### Moves the mouse X and Y pixels. Clicks if received byte and buffer is not NULL.
```cpp
dx = (int)x[0] + (int)bf[0]; 
dy = (int)x[1] + (int)bf[1];
Mouse.move(dx, dy);

if(x[2] != 0 || bf[2] != 0)
    Mouse.press();
    
else
    Mouse.release();
```
