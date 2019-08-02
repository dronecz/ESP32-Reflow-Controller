// Use hardware SPI
Adafruit_ILI9341 display = Adafruit_ILI9341(display_cs, display_dc, display_rst);
//Adafruit_ILI9341 display = Adafruit_ILI9341(display_cs, display_dc, display_mosi, display_sclk, display_rst);

extern int inputInt;
//#define font &FreeSans9pt7b

void infoScreen() {
  display.fillScreen(ILI9341_BLACK);
  display.setRotation(2);
  display.setFont(&FreeSans9pt7b);
  //display.setFont(&FreeSans9pt7b);
  display.setTextColor(ILI9341_WHITE);
  display.setTextSize(1);
  //  display.setCursor(0, 15);
  //  display.print("WIFI: ");
  //  display.print(WiFi.SSID());
  display.setCursor(0, 15);
  display.print("IP: ");
  display.println(WiFi.localIP());
  //  display.setCursor(80, 275);
  //  display.print("Temp: ");
  //  display.println(input);
  display.setCursor(0, 300);
  display.print("FW: ");
  display.println(fwVersion);
  //  if (online == 1) {
  //    display.setFont(&FreeSerif9pt7b);
  //    display.setTextColor(ILI9341_GREEN);
  //    display.setCursor(260, 15);
  //    display.setTextSize(1);
  //    display.print("Online");
  //  } else {
  //    display.setFont(&FreeSerif9pt7b);
  //    display.setTextColor(ILI9341_RED);
  //    display.setCursor(260, 15);
  //    display.setTextSize(1);
  //    display.print("Offline");
  //  }
}
void startScreen() {
  infoScreen();
  display.setFont(&FreeSans9pt7b);
  display.setTextColor(ILI9341_WHITE);
  display.setTextSize(2);
  display.setCursor(50, 70);
  display.println("ESP32");
  display.setCursor(50, 120);
  display.println("Reflow");
  display.setCursor(25, 200);
  display.println("Controller");
}

void accessScreen() {
  infoScreen();
  display.setFont(&FreeSans9pt7b);
  display.setTextColor(ILI9341_WHITE);
  display.setRotation(3);
  display.setTextSize(2);
  display.setCursor(70, 130);
}

void loopScreen() {
  //startScreen();
  display.fillRect(0,220,240,40,ILI9341_WHITE);
  display.setFont(&FreeSans9pt7b);
  display.setTextColor(ILI9341_GREEN);
  display.setTextSize(2);
  display.setCursor(20, 250);
  display.print("Temp : ");
  display.println(inputInt);
}
/*
void centeredText(){
  
}

char* string2char(String command){
    if(command.length()!=0){
        char *p = const_cast<char*>(command.c_str());
        return p;
    }
}

void test(){
  display.getTextBounds(string2char("Temp"), 0, 100, &x1, &y1, &ww, &hh );
}
*/
