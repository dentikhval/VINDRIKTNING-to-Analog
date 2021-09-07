#include <SoftwareSerial.h>
#include <Adafruit_GFX.h>      //Libraries for the OLED and BMP280
#include <Adafruit_SSD1306.h>
#include <Adafruit_BMP280.h>

unsigned int serialRxBuf[21];
static const uint8_t PIN_UART_RX = D5; //
static const uint8_t PIN_UART_TX = D0; //
int a = 0;
int data;
int numReadings[7];
int b;
int total;
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)

uint16_t pm25;
SoftwareSerial sensorSerial(PIN_UART_RX, PIN_UART_TX);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); //Declaring the display name (display)
Adafruit_BMP280 bmp;


void setup() {
  // put your setup code here, to run once:
  bmp.begin(0x76);                                //Start the bmp

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //Start the OLED display
  display.clearDisplay();
  display.display();
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("Air Quality");
  display.display();
  delay(100);
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

    (serialRxBuf[a] = data);

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

        display.clearDisplay();
        display.display();
        display.setTextSize(2);
        display.setCursor(0, 30);
        display.print(total);
        display.setCursor(50, 30);
        display.print("ug/M3");

        //BMP280 Stuff
        float T = bmp.readTemperature();           //Read temperature in C
        float P = bmp.readPressure() / 100;       //Read Pressure in Pa and conversion to hPa
        float A = bmp.readAltitude(1026);      //Calculating the Altitude, the "1019.66" is the pressure in (hPa) at sea level at day in your region


        display.setCursor(0, 50);
        display.print((T - 5), 1); // Very poor attempt to display a more accurate temperature.
        display.setCursor(52, 50);
        display.setTextSize(1);
        display.print("C");

        display.setTextSize(1);
        display.setCursor(65, 47);
        display.print(P);
        display.setCursor(110, 47);
        display.print("hPa");

        display.setCursor(65, 57);
        display.print("Alt");
        display.setCursor(90, 57);
        display.print(A, 0);
        display.setCursor(105, 57);
        display.print("m");
        // end of bmp280 stuff

        display.display();

        Serial.print("Average PM 2.5 value = ");
        Serial.println(total);
        b = 0;
      }

    }

  }
}
