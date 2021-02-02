#include <SPI.h>
#include <OneWire.h>
#include <ESP8266WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <DallasTemperature.h>

#define BUTTON_A  0
#define BUTTON_B 16
#define BUTTON_C  2

#define ONE_WIRE_BUS 14

const char* ssid     = "BT-KKA6H6";
const char* password = "qL3AVa6fGFbCPc";

const char* host = "wifitest.adafruit.com";

Adafruit_SH110X display = Adafruit_SH110X(64, 128, &Wire);

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  sensors.setResolution(9);
  sensors.begin();

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());


  Serial.println("128x64 OLED Wifi test");
  display.begin(0x3C, true); // Address 0x3C default

  Serial.println("OLED begun");

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(1000);

  // Clear the buffer.
  display.clearDisplay();
  display.display();

  display.setRotation(1);
  Serial.println("Button test");

  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);

  // text display tests
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.print("Connecting to SSID\n'BT-KKA6H6':");
  display.print("connected!");
  display.println(WiFi.localIP());
  display.display(); // actually display all of the above
}

void loop() {
  sensors.requestTemperatures();

  if (!digitalRead(BUTTON_A)) {

    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Temp 1 : ");
    display.print(sensors.getTempCByIndex(0));

  }
  if (!digitalRead(BUTTON_B)) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Temp 2");
  }


  if (!digitalRead(BUTTON_C)) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Temp 3");
  }
  delay(50);
  yield();    // don't know what this does yet
  display.display();
}
