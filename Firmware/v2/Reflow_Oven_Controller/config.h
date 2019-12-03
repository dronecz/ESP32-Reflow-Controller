#define DEBUG

#define VERBOSE 1 

// LCD pin definition

#define display_cs   5  // goes to TFT CS
#define display_dc   21  // goes to TFT DC
#define display_mosi 23  // goes to TFT MOSI
#define display_sclk 18  // goes to TFT SCK/CLK
#define display_rst  -1   // goes to TFT RESET
#define _miso 19    // Not connected
//       3.3V     // Goes to TFT LED
//       5v       // Goes to TFT Vcc
//       Gnd      // Goes to TFT Gnd

// MAX31856 pin definition
#define max_cs  13  
#define max_di  23
#define max_do  19
#define max_clk 18

/*SSR pin definition*/
int ssrPin = 14;
/*LED pin definition*/
int ledPin = 2;
int ledState = LOW;
/*Buzzer pin definition*/
int buzzerPin = 15;
//int switchPin = 27; // Select button
/*Swich pin definition*/
#define BUTTON_SELECT   27
#define BUTTON_AXIS_Y   35
#define BUTTON_AXIS_X   34
#define BUTTON_MENU     32
#define BUTTON_BACK     33
#define SD_CS_pin       22

// FW info

const String fwVersion = "0.2.28_beta";
#define ServerVersion "1.0"
#define projectName "ESP32 Reflow Oven Controller"

// Setup

//OTA settings

int contentLength = 0;
bool isValidContentType = false;
String host = "yourdomain.com"; // Host => bucket-name.s3.region.amazonaws.com
int port = 80; // Non https. For HTTPS 443. As of today, HTTPS doesn't work.
String bin = "/some.bin"; // bin file name with a slash in front.
String readString;
String readVersion;
