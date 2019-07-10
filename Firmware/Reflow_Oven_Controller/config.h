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


// FW info

const String fwVersion = "0.1.14_beta";

// Setup

//OTA settings

int contentLength = 0;
bool isValidContentType = false;
String host = "www.moravcu.cz"; // Host => bucket-name.s3.region.amazonaws.com
int port = 80; // Non https. For HTTPS 443. As of today, HTTPS doesn't work.
String bin = "/FM.bin"; // bin file name with a slash in front.
String readString;
String readVersion;
