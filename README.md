# VINDRIKTNING Air quality sensor
IKEA - VINDRIKTNING Air quality sensor data read by Arduino Nano

A place to store my files for data logging of air quality using the  VINDRIKTNING Air quality sensor from Ikea.

The first sketch is very basic and reads a software serial port to give an average value.

The next file (running on a Wemos D1 mini Pro) adds an OLED to display the values returned by the sensor.
Software serial is created on D5 and a level converter is used.

![OLED](https://user-images.githubusercontent.com/20041111/132402870-7700e710-97c5-4fb3-8d70-6fc378d0b541.jpg)

There is also a BMP280 temp and pressure sensor.  BMP280 is not the best choice of temperature sensor! :-)
