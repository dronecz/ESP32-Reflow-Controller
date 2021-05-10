// ***** INCLUDES *****
#include <Adafruit_ILI9341.h>
#include <Adafruit_MAX31856.h>
#include "Adafruit_GFX.h"
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSerif9pt7b.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <Preferences.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <WebSocketsServer.h>
#include <DNSServer.h>
#include <ESPmDNS.h>
#include <Update.h>
#include "FS.h"
#include <SD.h>
//#include <wifiTool.h> //https://github.com/oferzv/wifiTool
#include <WiFiManager.h>
#include "SPI.h"
#include "config.h"
#include "Button.h"
#include <SPIFFS.h>

HTTPClient http;

// Use software SPI: CS, DI, DO, CLK
//Adafruit_MAX31856 max = Adafruit_MAX31856(max_cs, max_di, max_do, max_clk);
// use hardware SPI, just pass in the CS pin
Adafruit_MAX31856 max31856 = Adafruit_MAX31856(max_cs);

// Use hardware SPI
Adafruit_ILI9341 display = Adafruit_ILI9341(display_cs, display_dc, display_rst);
//Adafruit_ILI9341 display = Adafruit_ILI9341(display_cs, display_dc, display_mosi, display_sclk, display_rst);

#define FORMAT_SPIFFS_IF_FAILED true

Preferences preferences;
AsyncWebServer server(80);
AsyncEventSource events("/events");
DNSServer dns;
WebSocketsServer webSocket = WebSocketsServer(1337);
//WifiTool wifiTool;
WiFiManager wm;
char msg_buf[10];

#define DEBOUNCE_MS 100
Button AXIS_Y = Button(BUTTON_AXIS_Y, true, DEBOUNCE_MS);
Button AXIS_X = Button(BUTTON_AXIS_X, true, DEBOUNCE_MS);

int digitalButtonPins[] = {BUTTON_SELECT, BUTTON_MENU, BUTTON_BACK};

#define numDigButtons sizeof(digitalButtonPins)

int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;
unsigned long lastDebounceTime_ = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 200;    // the debounce time; increase if the output flicker

String activeStatus = "Idle";
bool menu = 0;
bool isFault = 0;
bool connected = 0;
bool horizontal = 0;
bool fan = 0;
bool buttons = 0;
bool buzzer = 0;
bool useOTA = 0;
bool debug = 0;
bool verboseOutput = 1;
bool disableMenu = 0;
bool profileIsOn = 0;
bool noThermocouple = 0;
bool updataAvailable = 0;
bool testState = 0;
bool useSPIFFS = 1;
bool setupDone = 0;

// Button variables
int buttonVal[numDigButtons] = {0};                            // value read from button
int buttonLast[numDigButtons] = {0};                           // buffered value of the button's previous state
long btnDnTime[numDigButtons];                               // time the button was pressed down
long btnUpTime[numDigButtons];                               // time the button was released
boolean ignoreUp[numDigButtons] = {false};                     // whether to ignore the button release because the click+hold was triggered
boolean menuMode[numDigButtons] = {false};                     // whether menu mode has been activated or not
int debounce = 50;
int holdTime = 1000;
int oldTemp = 0;

byte numOfPointers = 0;
byte state = 0; // 0 = boot, 1 = main menu, 2 = select profile, 3 = change profile, 4 = add profile, 5 = settings, 6 = info, 7 = start reflow, 8 = stop reflow, 9 = test outputs , 10 = setup
byte previousState = 0;

byte settings_pointer = 0;
byte previousSettingsPointer = 0;
byte tempPointer = 0;
bool   SD_present = false;
//char* json = "";
int profileNum = 0;
#define numOfProfiles 10
String jsonName[numOfProfiles];
char json;
int profileUsed = 0;
char spaceName[] = "profile00";
String profileNames = "";
String usedProfileName = "";
const char* PARAM_INPUT_1 = "output";
const char* PARAM_INPUT_2 = "state";
String inputMessage1;
int inputMessage2;
String settingsValues;
String setSettingsValue;

// Structure for paste profiles
typedef struct {
  char      title[20];         // "Lead 183"
  char      alloy[20];         // "Sn63/Pb37"
  uint16_t  melting_point;     // 183

  uint16_t  temp_range_0;      // 30
  uint16_t  temp_range_1;      // 235

  uint16_t  time_range_0;      // 0
  uint16_t  time_range_1;      // 340

  char      reference[100];    // "https://www.chipquik.com/datasheets/TS391AX50.pdf"

  uint16_t  stages_preheat_0;  // 30
  uint16_t  stages_preheat_1;  // 100

  uint16_t  stages_soak_0;     // 120
  uint16_t  stages_soak_1;     // 150

  uint16_t  stages_reflow_0;   // 150
  uint16_t  stages_reflow_1;   // 183

  uint16_t  stages_cool_0;     // 240
  uint16_t  stages_cool_1;     // 183

  uint16_t  profile_count;     // max. 30
  uint16_t  profile[32][2];    // {{0,30}, {20,90}, ...}, maximum -> profile_countc
} profile_t;

profile_t paste_profile[numOfProfiles]; //declaration of struct type array

#include "reflow_logic.h"

void changeValues(String variable, bool value, bool sendUpdate = 1) {
  preferences.begin("store", false);
  if (variable == "useOTA") {
    Serial.println("Current value is: " + String(useOTA));
    preferences.putBool("useOTA", value);
    useOTA = preferences.getBool("useOTA", 0);
    Serial.println("useOTA value changed to: " + String(useOTA));
    setOTA(95);
  } else if (variable == "buzzer") {
    Serial.println("Current value is: " + String(buzzer));
    preferences.putBool("buzzer", value);
    buzzer = preferences.getBool("buzzer", 0);
    Serial.println("buzzer value changed to: " + String(buzzer));
    setBuzzer(55);
  } else if (variable == "useSPIFFS") {
    Serial.println("Current value is: " + String(useSPIFFS));
    preferences.putBool("useSPIFFS", value);
    useSPIFFS = preferences.getBool("useSPIFFS", 0);
    Serial.println("useSPIFFS value changed to: " + String(useSPIFFS));
    setStorage(135);
  } else if (variable == "buttons") {
    Serial.println("Current value is: " + String(buttons));
    preferences.putBool("buttons", value);
    buttons = preferences.getBool("buttons", 0);
    Serial.println("buttons value changed to: " + String(buttons));
    setButtons(115);
  } else if (variable == "horizontal") {
    Serial.println("Current value is: " + String(horizontal));
    preferences.putBool("horizontal", value);
    horizontal = preferences.getBool("horizontal", 0);
    Serial.println("horizontal value changed to: " + String(horizontal));
    setDisplay(75);
    startScreen();
  } else if (variable == "setupDone") {
    Serial.println("Current value is: " + String(setupDone));
    preferences.putBool("setupDone", value);
    horizontal = preferences.getBool("setupDone", 0);
    Serial.println("setupDone value changed to: " + String(setupDone));
  } else {
    Serial.println("Current value is: " + String(fan));
    preferences.putBool("fan", value);
    fan = preferences.getBool("fan", 0);
    Serial.println("fan value changed to: " + String(fan));
    setFan(155);
  }
  preferences.end();
  if (sendUpdate != 0) {
    String tempS = "";
    tempS += variable + ",";
    tempS += value;
    events.send(tempS.c_str(), "setSettings");
  }
}


void setup() {
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP

  Serial.begin(115200);

  Serial.println(projectName);

  Serial.println("FW version is: " + String(fwVersion) + "_&_" + String(__DATE__) + "_&_" + String(__TIME__));

  preferences.begin("store", false);
  buttons = preferences.getBool("buttons", 0);
  fan = preferences.getBool("fan", 0);
  horizontal = preferences.getBool("horizontal", 0);
  buzzer = preferences.getBool("buzzer", 0);
  useOTA = preferences.getBool("useOTA", 0);
  profileUsed = preferences.getInt("profileUsed", 0);
  useSPIFFS = preferences.getBool("useSPIFFS", 0);
  setupDone = preferences.getBool("setupDone", 0);
  preferences.end();

  Serial.println();
  Serial.println("Buttons: " + String(buttons));
  Serial.println("Fan is: " + String(fan));
  Serial.println("Horizontal: " + String(horizontal));
  Serial.println("Buzzer: " + String(buzzer));
  Serial.println("OTA: " + String(useOTA));
  Serial.println("Used profile: " + String(profileUsed));
  Serial.println();

  settingsValues += String(useOTA) + ",";
  settingsValues += String(buzzer) + ",";
  settingsValues += String(useSPIFFS) + ",";
  settingsValues += String(fan) + ",";
  settingsValues += String(buttons) + ",";
  settingsValues += String(horizontal);

  Serial.println("Settings Value are: " + settingsValues);

  // load profiles from ESP32 memory
  for (int i = 0; i < numOfProfiles; i++) {
    loadProfiles(i);
  }
  
  display.begin();
  startScreen();
  
  if ( !SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)) {
    Serial.println("Error mounting SPIFFS");
    return;
  }

  // SSR pin initialization to ensure reflow oven is off

  pinMode(ssrPin, OUTPUT);
  digitalWrite(ssrPin, LOW);

  // Buzzer pin initialization to ensure annoying buzzer is off
  digitalWrite(buzzerPin, LOW);
  pinMode(buzzerPin, OUTPUT);

  // LED pins initialization and turn on upon start-up (active low)
  pinMode(ledPin, OUTPUT);

  // Start-up splash
  //digitalWrite(fanPin, LOW);
  pinMode(fanPin, OUTPUT);

  delay(100);

  // Turn off LED (active low)
  digitalWrite(ledPin, ledState);

  // Button initialization
  pinMode(BUTTON_AXIS_Y, INPUT_PULLDOWN);
  pinMode(BUTTON_AXIS_X, INPUT_PULLDOWN);

  for (byte i = 0; i < numDigButtons - 1 ; i++) {
    // Set button input pin
    if (digitalButtonPins[i] > 20  && digitalButtonPins[i] < 40) {
      pinMode(digitalButtonPins[i], INPUT_PULLUP);
      digitalWrite(digitalButtonPins[i], LOW  );
      Serial.println(digitalButtonPins[i]);
    }
  }

  if (WiFi.status() == WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
    Serial.println("\nConnected to " + WiFi.SSID() + "; IP address: " + WiFi.localIP().toString()); // Report which SSID and IP is in use
    connected = 1;

    if (useOTA != 0) {
      OTA();
    }
  }

  // The logical name http://reflowserver.local will also access the device if you have 'Bonjour' running or your system supports multicast dns
  if (!MDNS.begin("reflowserver")) {          // Set your preferred server name, if you use "myserver" the address would be http://myserver.local/
    Serial.println(F("Error setting up MDNS responder!"));
    ESP.restart();
  }

  /** webserver start**/

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", "text/html");
  });

  server.on("/src/jquery.min.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/src/jquery.min.js", "text/javascript");
  });

  server.on("/src/bootstrap.bundle.min.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/src/bootstrap.bundle.min.js", "text/javascript");
  });


  server.on("/src/bootstrap.min.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/src/bootstrap.min.css", "text/css");
  });

  server.on("/src/simple-sidebar.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/src/simple-sidebar.css", "text/css");
  });

  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", webTemp().c_str());
  });

  server.on("/showchart", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", profileInt().c_str());
  });

  server.on("/profileNames", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", profileNames.c_str());
  });

  server.on("/getProfile", HTTP_GET, [](AsyncWebServerRequest * request) {
    String inputId;
    // GET input1 value on <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
    if (request->hasParam("id")) {
      inputId = request->getParam("id")->value();
    }
    else {
      inputId = "No message sent";
    }
    int id = inputId.toInt();
    if (id != -1) {
      request->send_P(200, "text/plain", getProfile(id).c_str());
    } else {
      Serial.println("Requested profile ID is -1 (\"Select profile\"), nothing to send.");
    }
  });

  server.on("/usedProfile", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", usedProfileName.c_str());
  });

  server.on("/getSettings", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", settingsValues.c_str());
  });

  server.on("/setSettings", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", setSettingsValue.c_str());
  });

  // Send a GET request to <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
  server.on("/update", HTTP_GET, [] (AsyncWebServerRequest * request) {
    // GET input1 value on <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
    String tempString;
    if (request->hasParam(PARAM_INPUT_1) && request->hasParam(PARAM_INPUT_2)) {
      inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
      tempString = request->getParam(PARAM_INPUT_2)->value();
      inputMessage2 = tempString.toInt();
      changeValues(inputMessage1, inputMessage2, 0);
    }
    else {
      inputMessage1 = "No message sent";
    }
    Serial.print(inputMessage1);
    Serial.print(" - Set to: ");
    Serial.println(String(inputMessage2));
    request->send(200, "text/plain", "OK");
  });

  // Handle Web Server Events
  events.onConnect([](AsyncEventSourceClient * client) {
    if (client->lastId()) {
      Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
    }
    // send event with message "hello!", id current millis
    // and set reconnect delay to 1 second
    client->send("hello!", NULL, millis(), 10000);
    //    client->send(profileNames, NULL, NULL, NULL);
  });

  server.addHandler(&events);
  // Start server
  server.begin();
  /** webserver end**/

  Serial.println("HTTP server started");

  max31856.begin();
  max31856.setThermocoupleType(MAX31856_TCTYPE_K);

  // Set window size
  windowSize = 2000;
  // Initialize time keeping variable
  nextCheck = millis();
  // Initialize thermocouple reading variable
  nextRead = millis();

  if (useSPIFFS != 0) {
    profileNum = 0;
    listDir(SPIFFS, "/profiles", 0);
  } else {
    Serial.print(F("Initializing SD card..."));
    //    if (!SD.begin(SD_CS_pin)) { // see if the card is present and can be initialised. Wemos SD-Card CS uses D8
    //      Serial.println(F("Card failed or not present, no SD Card data logging possible..."));
    //      SD_present = false;
    //    } else {
    //      Serial.println(F("Card initialised... file access enabled..."));
    //      SD_present = true;
    //      // Reset number of profiles for fresh load from SD card
    //      profileNum = 0;
    //      listDir(SD, "/profiles", 0);
    //    }
  }
  // Load data from selected storage
  if ((SD_present == true) || (useSPIFFS != 0)) {
    profile_t paste_profile_load[numOfProfiles];
    // Scan all profiles from source

    for (int i = 0; i < profileNum; i++) {
      if (useSPIFFS != 0) {
        parseJsonProfile(SPIFFS, jsonName[i], i, paste_profile_load);
      } else {
        parseJsonProfile(SD, jsonName[i], i, paste_profile_load);
      }
    }
    //Compare profiles, if they are already in memory
    for (int i = 0; i < profileNum; i++) {
      compareProfiles(paste_profile_load[i], paste_profile[i], i);
    }
  }

  Serial.println();
  Serial.print("Number of profiles: ");
  Serial.println(profileNum);

  Serial.println("Titles and alloys: ");
  for (int i = 0; i < profileNum; i++) {
    Serial.print((String)i + ". ");
    Serial.print(paste_profile[i].title);
    Serial.print(", ");
    Serial.println(paste_profile[i].alloy);
  }

  for (int i = 0; i < profileNum; i++) {
    profileNames += (paste_profile[i].title);
    profileNames += (", ");
  }
  Serial.println("Names of all profiles: " + profileNames);
  events.send(profileNames.c_str(), "profileNames");
  usedProfileName = paste_profile[profileUsed].title;
  Serial.println("Names of used profile: " + usedProfileName);
  events.send(usedProfileName.c_str(), "usedProfile");
  Serial.println();
  Serial.println("Connected: " + String(connected));
}


void processButtons() {
  for (int i = 0; i < numDigButtons; i++) {
    digitalButton(digitalButtonPins[i]);
  }
  readAnalogButtons();
}

void loop() {
  wm.process();
  if (state != 9) { // if we are in test menu, disable LED & SSR control in loop
    reflow_main();
  }
  processButtons();
  //server.handleClient(); // Listen for client connections
  // Look for and handle WebSocket data
  webSocket.loop();
}

void listDir(fs::FS &fs, const char * dirname, uint8_t levels) {
  Serial.printf("Listing directory: %s\r\n", dirname);

  File root = fs.open(dirname);
  if (!root) {
    Serial.println("Failed to open directory");
    return;
  }
  if (!root.isDirectory()) {
    Serial.println("Not a directory");
    return;
  }

  File file = root.openNextFile();
  String tempFileName;
  while (file) {
    if (file.isDirectory()) {
      Serial.print("  DIR : ");
      Serial.println(file.name());
      if (levels) {
        listDir(fs, file.name(), levels - 1);
      }
    } else {
      tempFileName = file.name();
      if (tempFileName.endsWith("json")) {
        Serial.println("Find this JSON file: "  + tempFileName);
        jsonName[profileNum] = tempFileName;
        profileNum++;
      }
    }
    file = root.openNextFile();
  }
}

void readFile(fs::FS & fs, String path, const char * type) {
  Serial.printf("Reading file: %s\n", path);

  File file = fs.open(path);
  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }
  Serial.print("Read from file: ");
  while (file.available()) {
    Serial.write(file.read());
  }
  file.close();
}

void wifiSetup() {
  wm.setConfigPortalBlocking(false);
  if (wm.autoConnect("ReflowOvenAP")) {
    Serial.println("connected...yeey :)");
  }
  else {
    Serial.println("Configportal running");
  }
}

String getProfile(int Id) {
  Serial.println("Get request for profile with ID of:" + String(Id));
  //String returnString = "Get request for profile with ID of:" + String(Id);
  String returnString;

  returnString += String(paste_profile[Id].title) + ",";
  returnString += String(paste_profile[Id].alloy) + ",";
  returnString += String(paste_profile[Id].melting_point) + ",";
  returnString += String(paste_profile[Id].temp_range_0) + ",";
  returnString += String(paste_profile[Id].temp_range_1) + ",";
  returnString += String(paste_profile[Id].time_range_0) + ",";
  returnString += String(paste_profile[Id].time_range_1) + ",";
  returnString += String(paste_profile[Id].reference) + ",";
  returnString += String(paste_profile[Id].stages_preheat_0) + ",";
  returnString += String(paste_profile[Id].stages_preheat_1) + ",";
  returnString += String(paste_profile[Id].stages_soak_0) + ",";
  returnString += String(paste_profile[Id].stages_soak_1) + ",";
  returnString += String(paste_profile[Id].stages_reflow_0) + ",";
  returnString += String(paste_profile[Id].stages_reflow_1) + ",";
  returnString += String(paste_profile[Id].stages_cool_0) + ",";
  returnString += String(paste_profile[Id].stages_cool_1);
  Serial.println("Profile as String is: " + returnString);
  return returnString;
}
