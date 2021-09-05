// Basic Arduino sketch to read data from an IKEA - VINDRIKTNING Air quality sensor.
// Software serial set up on pins 10 & 11 

#include <SoftwareSerial.h>
unsigned int serialRxBuf[21];
static const uint8_t PIN_UART_RX = 10; // D0 on Wemos D1 Mini
static const uint8_t PIN_UART_TX = 11; //
int a = 0;
int data;
int numReadings[7];
int b;
int total;

//uint16_t pm25;
SoftwareSerial sensorSerial(PIN_UART_RX, PIN_UART_TX);



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Opened Hardware serial  ");
  sensorSerial.begin(9600);
  Serial.println("Opened Software serial  ");

}

void loop() {
  // put your main code here, to run repeatedly:
  if (sensorSerial.available())
  {

    int data = sensorSerial.read();

    a = (a + 1);
    if (a == 20) {
      uint16_t pm25 = (serialRxBuf[5] << 8) | serialRxBuf[6];

      Serial.print("PM 2.5 value = ");
      numReadings[b] = (pm25);
      Serial.println(pm25);
      b = (b + 1);
      (a = 0);
      if (b == 7) {
        (total = ((numReadings[0] + numReadings[1] + numReadings[2] + (numReadings[3] + numReadings[4] + numReadings[5] + numReadings[6])) / 7));
        Serial.print("Average PM 2.5 value = ");
        Serial.println(total);
        b = 0;
      }

    }
  }

}
