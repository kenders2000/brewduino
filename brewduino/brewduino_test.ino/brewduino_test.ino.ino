#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

/********************************************************************/
// Temperature stuff
// https://lastminuteengineers.com/ds18b20-arduino-tutorial/
// https://cdn.sparkfun.com/assets/4/a/8/8/8/DS18B20.pdf
#include <OneWire.h> 
#include <DallasTemperature.h>
// Data wire is plugged into pin 2 on the Arduino 
#define ONE_WIRE_BUS 14
// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 
OneWire oneWire(ONE_WIRE_BUS); 
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
float current_temp;  // The current temperature
float target_temp = 22.0;  // The target temperature
float temp_step = 0.5;     // Every time A or B is pressed target changes by this ammount.
char line [100]; // a line of text to write to the screen
int cx;          // int (
Adafruit_SH110X display = Adafruit_SH110X(64, 128, &Wire);

// OLED FeatherWing buttons map to different pins depending on board:
#define BUTTON_A  0
#define BUTTON_B 16
#define BUTTON_C  2

void setup() {
  Serial.begin(115200);
  // set resultion to 9 bits, this determins the latancy and temp resolution (around 100ms)
  sensors.setResolution(9);
  sensors.begin(); 

  Serial.println("128x64 OLED FeatherWing test");
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
  display.setTextSize(1.5);
  display.setTextColor(SH110X_WHITE);
//  display.setCursor(0,0);
//  display.print("Connecting to SSID\n'adafruit':");
//  display.print("connected!");
//  display.println("IP: 10.0.1.23");
//  display.println("Sending val #0");
//  display.display(); // actually display all of the above
}

void loop() {

  // grab the temperature 
  // https://lastminuteengineers.com/ds18b20-arduino-tutorial/
  sensors.requestTemperatures(); // Send the command to get temperature readings 
  current_temp = sensors.getTempCByIndex(0);
  Serial.print(current_temp); 
  Serial.print("\n");
  
  // Clear the buffer.
  display.clearDisplay();
  display.setCursor(0,0);

  // format the first line, write to display
  snprintf ( line, 100, "Actual Temp : %3.2f", current_temp);
  display.println(line);
  // format the first line, write to display
  snprintf ( line, 100, "Target Temp : %3.2f", target_temp);
  display.println(line);

  if(!digitalRead(BUTTON_A)) target_temp = target_temp + temp_step ;
  if(!digitalRead(BUTTON_B)) target_temp = target_temp - temp_step ;

//  if(!digitalRead(BUTTON_B)) display.print("B");
//  if(!digitalRead(BUTTON_C)) display.print("C");
  delay(10);
  yield();
  display.display();
}
