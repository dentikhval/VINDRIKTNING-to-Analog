// Basic Arduino sketch to read data from an IKEA - VINDRIKTNING Air quality sensor.
// Software serial set up on pins 2 and 3

#include <SoftwareSerial.h>
unsigned int serialRxBuf[21];
static const uint8_t PIN_UART_RX = 2;  // TX Pin on sensor board
static const uint8_t PIN_UART_TX = 3;  // Not connected as we aren't sending anything to the sensor
static const uint8_t PIN_PWM_OUT = 8;  // PWM Out for analogWrite function - connected to a PWM-to-analog converter

const int PM_SPAN_MIN = 0;     // Minimal pm2.5 reading equivalent to minimum poutput
const int PM_SPAN_MAX = 500;   // Max pm2.5 reading equivalent to max output
const int PWM_OUT_MIN = 204;   // MIN PWM Out - calibrate to get 2V OUT at zero reading
const int PWM_OUT_MAX = 1023;  // MAX PWM Out - calibrate to get 10V OUT at max reading

//#define USE_AVERAGE // Comment out this line not to use averaging

const int AVG_NUM = 3;  // Number of readings for average (only average gets written to output!)

int a = 0;
int data;
//int numReadings[7];
int average = 0;
int b = 0;
//int total;
uint16_t OUT_VALUE = 0;
bool validFrame = 0;

//uint16_t pm25;
SoftwareSerial sensorSerial(PIN_UART_RX, PIN_UART_TX);



void setup() {
  pinMode(PIN_PWM_OUT, OUTPUT);
  analogWrite(PIN_PWM_OUT, 0);  // Until boot finished we intentionally keep this pin LOW
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Opened Hardware serial  ");
  sensorSerial.begin(9600);
  Serial.println("Opened Software serial  ");
  //delay(4000);  // Wait for the sensor to boot
}

void loop() {
  // put your main code here, to run repeatedly:


  if (sensorSerial.available()) {

    int data = sensorSerial.read();
    (serialRxBuf[a] = data);

    a++; // Only move toward a if we have a valid frame start

    if (serialRxBuf[0] == 0x16 && serialRxBuf[1] == 0x11 && serialRxBuf[2] == 0x0B) {
      validFrame = 1;
    }

    if (a == 20 && validFrame == 1) { // When we have a full frame and
      validFrame = 0;
      uint16_t pm25 = (serialRxBuf[5] << 8) | serialRxBuf[6];

      if (pm25 > 2 && pm25 < 1200) {  // DIY sorta sanity check - only output if the values are sane
        Serial.print(" PM 2.5 value = ");
        Serial.println(pm25);
#ifndef USE_AVERAGE 
          OUT_VALUE = map(pm25, PM_SPAN_MIN, PM_SPAN_MAX, PWM_OUT_MIN, PWM_OUT_MAX);
          Serial.print("NON AVG PWM = ");
          Serial.println(OUT_VALUE);
          analogWrite(PIN_PWM_OUT, OUT_VALUE);
#endif

#ifdef USE_AVERAGE
        b++;
        average = average + pm25;
        if (b == AVG_NUM) {
          average = average / AVG_NUM;

          // (total = ((numReadings[0] + numReadings[1] + numReadings[2] + (numReadings[3] + numReadings[4] + numReadings[5] + numReadings[6])) / 7));
          Serial.print("Average PM 2.5 value = ");
          Serial.println(average);
          OUT_VALUE = map(average, PM_SPAN_MIN, PM_SPAN_MAX, PWM_OUT_MIN, PWM_OUT_MAX);
          Serial.print("PWM value = ");
          Serial.println(OUT_VALUE);
          analogWrite(PIN_PWM_OUT, OUT_VALUE);
          average = 0;
          b = 0;
        } // if b == 7
        // End average calculation
#endif
      } else {  // if we got gibberish input
        Serial.println("Valid frame invalid reading");

      } // if we got gibberish input
      a = 0; // Reset byte counter
      validFrame = 0; // Reset valid frame indicator

    }  // if a==20

  }//  if sensorserial    available
}
