// Use hardware SPI
Adafruit_ILI9341 display = Adafruit_ILI9341(display_cs, display_dc, display_rst);
//Adafruit_ILI9341 display = Adafruit_ILI9341(display_cs, display_dc, display_mosi, display_sclk, display_rst);
//extern void centeredText();
//extern typedef enum REFLOW_STATE;
extern int inputInt;
extern String activeStatus;
extern bool menu;
//#define font &FreeSans9pt7b

bool screanCleread = 0;
char* string2char(String command) {
  if (command.length() != 0) {
    char *p = const_cast<char*>(command.c_str());
    return p;
  }
}

void centeredText(String text, uint16_t color, int yCord, int xCord = 0) {
  int16_t x1, y1;
  uint16_t w, h;
  int offSet = 10;
  display.getTextBounds(string2char(text), 0, 0, &x1, &y1, &w, &h);
#ifdef DEBUG
  Serial.print("Text bounds for: \"" + text + "\"");
  Serial.print(" x1:");  Serial.print(x1);
  Serial.print(" y1:");  Serial.print(y1);
  Serial.print(" w:");  Serial.print(w);
  Serial.print(" h:");  Serial.println(h);
#endif
  display.setTextColor(color);
  display.fillRect(((display.width() - w) / 2), (yCord - (h / 2)), (w + offSet) , (h + offSet), ILI9341_BLACK);
  display.setCursor(((display.width() - w) / 2), (yCord + (h / 2)));
  display.println(text);
}

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
  display.setCursor(5, 15);
  display.print("IP: ");
  display.println(WiFi.localIP());
  //  display.setCursor(80, 275);
  //  display.print("Temp: ");
  //  display.println(input);
  display.setCursor(5, 315);
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
  int y = 100;
  infoScreen();
  display.setFont(&FreeSans9pt7b);
  //display.setTextColor(ILI9341_WHITE);
  display.setTextSize(2);
  centeredText("ESP32", ILI9341_WHITE, y);
  centeredText("Reflow", ILI9341_WHITE, y + 32);
  centeredText("Controller", ILI9341_WHITE, y + 64);
}

void accessScreen() {
  infoScreen();
  display.setFont(&FreeSans9pt7b);
  display.setTextColor(ILI9341_WHITE);
  display.setRotation(3);
  display.setTextSize(2);
  display.setCursor(70, 130);
}

void menuScreen() {
  display.fillScreen(ILI9341_BLACK);
  display.setTextColor(ILI9341_WHITE);
  display.setTextSize(2);

  display.drawRect(45, 10, 150, 20, ILI9341_WHITE);        //  draw outer box

  display.fillRect(10, 10, 30, 20, ILI9341_RED);           //  draw - button box
  display.drawRect(10, 10, 30, 20, ILI9341_WHITE);         //  draw button outer box
  display.setCursor(17, 26);                       //  text position
  display.print("-");
  display.fillRect(205, 10, 30, 20, ILI9341_GREEN);        //  draw + button box
  display.drawRect(205, 10, 30, 20, ILI9341_WHITE);        //  draw button outer box
  display.setCursor(210, 26);                      //  text position
  display.print("+");
  display.setTextSize(1);
  display.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
  centeredText("Test", ILI9341_WHITE, 17);
  //  display.setTextSize(1);
  //  display.setCursor(80, 120);                      //  text position
  //  display.print("OPTIONAL - NOT IN USE");
}

void loopScreen() {
  //startScreen();
  if (screanCleread !=1) {
    infoScreen(); //one time clear screen 
    screanCleread = 1;
  }
  if (menu != 0) {
    menuScreen();
  } else {
    int tempTextPos = 240;
    int infoText = 50;
    display.setFont(&FreeSans9pt7b);
    display.setTextSize(1);
    //display.setTextColor(ILI9341_WHITE);
    centeredText("Status:", ILI9341_WHITE, infoText);
    display.setTextSize(2);
    centeredText(activeStatus, ILI9341_WHITE, infoText + 32);
    //centeredText(reflowState, infoText);
    //display.setTextSize(2);

    String temp = ("Temp : " + String(inputInt));
#ifdef DEBUG
    Serial.println(temp);
#endif
    if (inputInt < 50) {
      //display.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
      centeredText(temp, ILI9341_GREEN, tempTextPos);
    } else if ((inputInt > 50) && (inputInt < 100)) {
      //display.setTextColor();
      centeredText(temp, ILI9341_ORANGE, tempTextPos);
    } else if (inputInt > 100) {
      //display.setTextColor(ILI9341_RED);
      centeredText(temp, ILI9341_RED, tempTextPos);
    }
  }
}


/* Saved for later use.. */
/*
  void updateProcessDisplay() {
  const uint8_t h =  86;
  const uint8_t w = 160;
  const uint8_t yOffset =  30; // space not available for graph

  uint16_t dx, dy;
  uint8_t y = 2;
  double tmp;

  // header & initial view
  tft.setTextColor(ST7735_WHITE, ST7735_BLUE);

  if (!initialProcessDisplay) {
    initialProcessDisplay = true;

    tft.fillScreen(ST7735_WHITE);
    tft.fillRect(0, 0, tft.width(), menuItemHeight, ST7735_BLUE);
    tft.setCursor(2, y);
  #ifndef PIDTUNE
    tft.print("Profile ");
    tft.print(activeProfileId);
  #else
    tft.print("Tuning ");
  #endif

    tmp = h / (activeProfile.peakTemp * 1.10) * 100.0;
    pxPerC = (uint16_t)tmp;

  #if 0 // pxPerS should be calculated from the selected profile, wint fit in flash right now
    double estimatedTotalTime = 60 * 12;
    // estimate total run time for current profile
    estimatedTotalTime = activeProfile.soakDuration + activeProfile.peakDuration;
    estimatedTotalTime += (activeProfile.soakTemp - 20.0) / (activeProfile.rampUpRate / 10);
    estimatedTotalTime += (activeProfile.peakTemp - activeProfile.soakTemp) / (activeProfile.rampUpRate / 10);
    estimatedTotalTime += (activeProfile.peakTemp - 20.0) / (activeProfile.rampDownRate  / 10);
    //estimatedTotalTime *= 2; // add some spare
    Serial.print("total est. time: ");
    Serial.println((uint16_t)estimatedTotalTime);
  #endif
    tmp = 60 * 8;
    tmp = w / tmp * 10.0;
    pxPerS = (uint16_t)tmp;

    // 50°C grid
    int16_t t = (uint16_t)(activeProfile.peakTemp * 1.10);
    for (uint16_t tg = 0; tg < t; tg += 50) {
      uint16_t l = h - (tg * pxPerC / 100) + yOffset;
      tft.drawFastHLine(0, l, 160, tft.Color565(0xe0, 0xe0, 0xe0));
    }
  #ifdef GRAPH_VERBOSE
    Serial.print("Calc pxPerC/S: ");
    Serial.print(pxPerC);
    Serial.print("/");
    Serial.println(pxPerS);
  #endif
  }

  // elapsed time
  uint16_t elapsed = (zeroCrossTicks - startCycleZeroCrossTicks) / 100;
  tft.setCursor(125, y);
  alignRightPrefix(elapsed);
  tft.print(elapsed);
  tft.print("s");

  y += menuItemHeight + 2;

  tft.setCursor(2, y);
  tft.setTextColor(ST7735_BLACK, ST7735_WHITE);

  // temperature
  tft.setTextSize(2);
  alignRightPrefix((int)A.temperature);
  displayThermocoupleData(&A);
  tft.setTextSize(1);

  #ifndef PIDTUNE
  // current state
  y -= 2;
  tft.setCursor(95, y);
  tft.setTextColor(ST7735_BLACK, ST7735_GREEN);

  switch (currentState) {
    #define casePrintState(state) case state: tft.print(#state); break;
    casePrintState(RampToSoak);
    casePrintState(Soak);
    casePrintState(RampUp);
    casePrintState(Peak);
    casePrintState(RampDown);
    casePrintState(CoolDown);
    casePrintState(Complete);
    default: tft.print((uint8_t)currentState); break;
  }
  tft.print("        "); // lazy: fill up space

  tft.setTextColor(ST7735_BLACK, ST7735_WHITE);
  #endif

  // set point
  y += 10;
  tft.setCursor(95, y);
  tft.print("Sp:");
  alignRightPrefix((int)Setpoint);
  printDouble(Setpoint);
  tft.print("\367C  ");

  // draw temperature curves
  //

  if (xOffset >= elapsed) {
    xOffset = 0;
  }

  do { // x with wrap around
    dx = ((elapsed - xOffset) * pxPerS) / 10;
    if (dx > w) {
      xOffset = elapsed;
    }
  } while(dx > w);

  // temperature setpoint
  dy = h - ((uint16_t)Setpoint * pxPerC / 100) + yOffset;
  tft.drawPixel(dx, dy, ST7735_BLUE);

  // actual temperature
  dy = h - ((uint16_t)A.temperature * pxPerC / 100) + yOffset;
  tft.drawPixel(dx, dy, ST7735_RED);

  // bottom line
  y = 119;

  // set values
  tft.setCursor(2, y);
  tft.print("\xef");
  alignRightPrefix((int)heaterValue);
  tft.print((int)heaterValue);
  tft.print('%');

  tft.print(" \x2a");
  alignRightPrefix((int)fanValue);
  tft.print((int)fanValue);
  tft.print('%');

  tft.print(" \x12 "); // alternative: \x7f
  printDouble(rampRate);
  tft.print("\367C/s    ");
  }
*/
