// ***** INCLUDES *****
#include <Adafruit_ILI9341.h>
#include <Adafruit_MAX31856.h>
#include "Adafruit_GFX.h"
#include <Fonts/FreeSans9pt7b.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "config.h"
#include "LCD.h"
#include "Button.h"
#include "reflow_logic.h"
#include "sd_card.h"

//#include <PID_v1.h>

//#define font &FreeSans9pt7b

WiFiMulti wifiMulti;
int wifiStatus;

// Use software SPI: CS, DI, DO, CLK
//Adafruit_MAX31856 max = Adafruit_MAX31856(max_cs, max_di, max_do, max_clk);
// use hardware SPI, just pass in the CS pin
Adafruit_MAX31856 max31856 = Adafruit_MAX31856(max_cs);

#define DEBOUNCE_MS 50
Button AXIS_Y = Button(BUTTON_AXIS_Y, true, DEBOUNCE_MS);
Button AXIS_X = Button(BUTTON_AXIS_X, true, DEBOUNCE_MS);
Button BtnSelect = Button(BUTTON_SELECT, true, DEBOUNCE_MS);
String activeStatus = "";
bool menu = 0;

void setup() {

  Serial.begin(115200);

  Serial.println("**** ESP32 Reflow Oven Controller ****");

  Serial.println("FW version is: " + fwVersion);
  
  display.begin();
  startScreen();

  wifiMulti.addAP("SSID", "PASSWORD");
  wifiMulti.addAP("SSID", "PASSWORD");
  wifiMulti.addAP("SSID", "PASSWORD");

  // SSR pin initialization to ensure reflow oven is off

  pinMode(ssrPin, OUTPUT);
  digitalWrite(ssrPin, LOW);

  // Buzzer pin initialization to ensure annoying buzzer is off
  digitalWrite(buzzerPin, LOW);
  pinMode(buzzerPin, OUTPUT);

  // LED pins initialization and turn on upon start-up (active low)
  pinMode(ledPin, OUTPUT);

  // Start-up splash
  digitalWrite(buzzerPin, LOW);
  delay(100);
  // This is for testing on different board
#ifdef ODROID
  ledcSetup(2, 10000, 8);
  ledcAttachPin(LCD_PIN, 2);
  ledcWrite(2, 200);
#endif

  //digitalWrite(buzzerPin, HIGH);

  // Turn off LED (active low)
  digitalWrite(ledPin, ledState);

  // Button initialization
  pinMode(BUTTON_SELECT, INPUT_PULLUP);
  pinMode(BUTTON_AXIS_Y, INPUT_PULLDOWN);
  pinMode(BUTTON_AXIS_X, INPUT_PULLDOWN);


  Serial.println("Connecting Wifi...");
  if (wifiMulti.run() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }

  wifiStatus = WiFi.status();

  max31856.begin();
  max31856.setThermocoupleType(MAX31856_TCTYPE_K);

  // Set window size
  windowSize = 2000;
  // Initialize time keeping variable
  nextCheck = millis();
  // Initialize thermocouple reading variable
  nextRead = millis();

  if (!SD.begin(22)) {
    Serial.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    return;
  }

  Serial.print("SD Card Type: ");
  if (cardType == CARD_MMC) {
    Serial.println("MMC");
  } else if (cardType == CARD_SD) {
    Serial.println("SDSC");
  } else if (cardType == CARD_SDHC) {
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
  Serial.printf("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
  Serial.printf("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));
}

void loop()
{
  reflow_main();
  //loopScreen();

  /* For testing select button (not yet implemented)& LED functionality. */
  ///*
    if (BtnSelect.read() == 1) {
      //digitalWrite(buzzerPin, HIGH);
      digitalWrite(ledPin, HIGH);
      if (menu == 0){
        menuScreen();
      }else{
        loopScreen();
      }
    } else {
      //digitalWrite(buzzerPin, LOW);
      digitalWrite(ledPin, LOW);
    }
  //*/
}
