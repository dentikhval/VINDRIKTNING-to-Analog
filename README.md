# VINDRIKTNING Air quality sensor
Thank you sparx266 for the original code. Good place to start but the missing addition of new byte to buffer was surprising.

I have added a frame verification mechanism to confirm we are receiving useful payloads, and a small sanity check to verify the readings are reasonable.

Arduino Nano is connected to the VINDRIKTNING board on pins: 
GND to board GND, 5V to 5V
Arduino Pin D2 set as Software Serial RX and connected to VINDRIKTNING board pin RFST (second from the side of the board where the SMD cap is)

On the other side, Arduino is connected to a DC-DC converter with 24V input and 5.1V output. 

For analog output I am using a cool DAC board PW1VA01, which creates an analog output from PWM inputs.
It is connected to GND and uses 24V input power. 
Arduino pin D8 is connected to PW1VA01 PWM input.
