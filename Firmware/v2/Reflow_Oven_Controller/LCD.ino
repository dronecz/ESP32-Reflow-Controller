extern JsonArray array;

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

void rightText(String text, uint16_t color, int yCord, int xCord = 5) {
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
  //display.fillRect(((display.width() - w) / 2), (yCord - (h / 2)), (w + offSet) , (h + offSet), ILI9341_BLACK);//
  display.setCursor(((display.width() - w) - xCord), yCord/*(yCord + (h /2))*/); //
  display.println(text);
}

void leftText(String text, uint16_t color, int yCord, int xCord = 0) {
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
  //display.fillRect(((display.width() - w) / 2), (yCord - (h / 2)), (w + offSet) , (h + offSet), ILI9341_BLACK);//
  display.setCursor(xCord + 30, yCord/*(yCord + (h /2))*/); //
  display.print(text);
}

void ShowMenuOptions( bool clearAll )
{
  int buttonPosY[] = { 45, 100, 145, 200 };
  int buttonHeight = 16;
  int buttonWidth = 4;

  display.setTextColor( ILI9341_WHITE, ILI9341_BLACK );
  display.setTextSize(2);

  if ( state >= 1 || state <= 10)
  {
    UpdateSettingsPointer();
  }
}

void UpdateSettingsPointer() { // this function shows help text at the bottom of the screen and pointer to your selection
  if ( state == 1 ) { // main menu
    //    if (settings_pointer >= 0 && settings_pointer <= 4) {
    display.setTextColor( ILI9341_WHITE, ILI9341_BLACK );
    display.setTextSize(1);
    display.fillRect( 0, 40, 20, display.height() - 20, ILI9341_BLACK );
    display.setCursor( 10, ( 54 + ( 20 * settings_pointer ) ) );
    display.println(">");


    display.setTextSize(0);
    display.setTextColor( ILI9341_GREEN, ILI9341_BLACK );
    display.fillRect( 0, display.height() - 40, display.width(), 40, ILI9341_BLACK );
    switch ( settings_pointer ) {

      case 0:
        if (disableMenu != 0) {
          //println_Center( display, "Select which profile to reflow", display.width() / 2, display.height() - 20 );
          centeredText("Show info menu", ILI9341_GREEN, 300);
          break;
        } else {
          centeredText("Select which profile to reflow", ILI9341_GREEN, 300);
          break;
        }

      case 1:
        centeredText("Change selected profile", ILI9341_GREEN, 300);
        break;

      case 2:
        centeredText("Add reflow profile", ILI9341_GREEN, 300);
        break;

      case 3:
        centeredText("Show settings menu", ILI9341_GREEN, 300);
        break;

      case 4:
        centeredText("Show info menu", ILI9341_GREEN, 300);
        break;
      case 5:
        if (updataAvailable = 1) {
          centeredText("Press Select to start update", ILI9341_GREEN, 300);
        }
        break;
    }
    display.setTextSize(2);
    previousSettingsPointer = settings_pointer;
  }
  else if (state == 2) { // select profile
    display.setTextColor( ILI9341_WHITE, ILI9341_BLACK );
    display.setTextSize(1);
    display.fillRect( 0, 40, 20, display.height() - 20, ILI9341_BLACK );
    display.setCursor( 10, ( 54 + ( 40 * settings_pointer ) ) );
    display.println(">");

    display.setTextSize(0);
    display.setTextColor( ILI9341_GREEN, ILI9341_BLACK );
    display.fillRect( 0, display.height() - 50, display.width(), 50, ILI9341_BLACK );
    switch ( settings_pointer )
    {
      case 0:
        centeredText("Select profile which", ILI9341_GREEN, 280);
        centeredText("you want to use.", ILI9341_GREEN, 300);
        break;
    }
  }
  else if ( state == 5 ) { //settings menu
    display.setTextColor( ILI9341_WHITE, ILI9341_BLACK );
    display.setTextSize(1);
    display.fillRect( 0, 40, 20, display.height() - 20, ILI9341_BLACK );
    display.setCursor( 10, ( 54 + ( 20 * settings_pointer ) ) );
    display.println(">");

    display.setTextSize(0);
    display.setTextColor( ILI9341_GREEN, ILI9341_BLACK );
    display.fillRect( 0, display.height() - 50, display.width(), 50, ILI9341_BLACK );
    switch ( settings_pointer )
    {
      case 0:
        centeredText("Set buzzer on/off.", ILI9341_GREEN, 300);
        break;

      case 1:
        centeredText("Orientation of the screen.", ILI9341_GREEN, 300);
        break;

      case 2:
        centeredText("Set Yes if you want to", ILI9341_GREEN, 280);
        centeredText("use FW updates from web.", ILI9341_GREEN, 300);
        break;

      case 3:
        centeredText("Set Yes if you have them.", ILI9341_GREEN, 300);
        break;
      case 4:
        centeredText("Set Yes to use SPIFFS", ILI9341_GREEN, 280);
        centeredText("for profiles.", ILI9341_GREEN, 300);
        break;
      case 5:
        if (buttons != 0) {
          centeredText("Set Yes to use fan.", ILI9341_GREEN, 300);
        } else {
          if (connected != 1) {
            centeredText("WiFi Setup", ILI9341_GREEN, 300);
          } else {
            centeredText("Enter Test menu.", ILI9341_GREEN, 300);
          }
        }
        break;
      case 6:
        if (buttons != 0) {
          if (connected != 1) {
            centeredText("WiFi Setup", ILI9341_GREEN, 300);
          }
          else {
            centeredText("Enter Test menu.", ILI9341_GREEN, 300);
          }
          centeredText("WiFi Setup", ILI9341_GREEN, 300);
        } else {
          centeredText("Enter Test menu.", ILI9341_GREEN, 300);
        }
        break;
      case 7:
        if (buttons != 0) {
          centeredText("Enter Test menu.", ILI9341_GREEN, 300);
        }
        break;
    }
  }
  else if ( state == 9 ) { //settings/test menu
    display.setTextColor( ILI9341_WHITE, ILI9341_BLACK );
    display.setTextSize(1);
    display.fillRect( 0, 40, 20, display.height() - 20, ILI9341_BLACK );
    display.setCursor( 10, ( 54 + ( 20 * settings_pointer ) ) );
    display.println(">");

    display.setTextSize(0);
    display.setTextColor( ILI9341_GREEN, ILI9341_BLACK );
    display.fillRect( 0, display.height() - 50, display.width(), 50, ILI9341_BLACK );
    switch ( settings_pointer )
    {
      case 0:
        centeredText("Test buzzer.", ILI9341_GREEN, 300);
        break;

      case 1:
        centeredText("Test fan.", ILI9341_GREEN, 300);
        break;

      case 2:
        centeredText("Test SSR.", ILI9341_GREEN, 300);
        break;

      case 3:
        centeredText("Test LED.", ILI9341_GREEN, 300);
        break;
    }
  }
  else if ( state == 10 || state == 101 || state == 102 || state == 103 || state == 104 || state == 105 || state == 106 || state == 107) {
    display.setTextColor( ILI9341_WHITE, ILI9341_BLACK );
    display.setTextSize(1);
    display.fillRect( 0, 40, 20, display.height() - 20, ILI9341_BLACK );
    display.setCursor( 10, ( 250 + ( 20 * settings_pointer ) ) );
    display.println(">");
  }
}

void infoScreen() {
  display.fillScreen(ILI9341_BLACK);
  display.setFont(&FreeSans9pt7b);
  display.setTextColor(ILI9341_WHITE);
  display.setTextSize(1);
  display.setCursor(5, 15);
  display.print("IP: ");
  display.println(WiFi.localIP());
  display.setCursor(5, 315);
  display.print("FW: ");
  display.println(fwVersion);
}

void startScreen() {
  display.fillScreen(ILI9341_BLACK);
  int y;
  if (horizontal != 0) {
    display.setRotation(3);
    y = 40;
    display.setFont(&FreeSans9pt7b);
    display.setTextSize(2);
    centeredText("ESP32", ILI9341_WHITE, y);
    centeredText("Reflow", ILI9341_WHITE, y + 32);
    centeredText("Controller", ILI9341_WHITE, y + 64);
    display.setTextSize(1);
    centeredText("by", ILI9341_WHITE, y + 134);
    centeredText("Czech maker", ILI9341_WHITE, y + 154);
    centeredText("www.czechmaker.com", ILI9341_WHITE, y + 174);
  } else {
    display.setRotation(2);
    y = 100;
    display.setFont(&FreeSans9pt7b);
    display.setTextSize(2);
    centeredText("ESP32", ILI9341_WHITE, y);
    centeredText("Reflow", ILI9341_WHITE, y + 32);
    centeredText("Controller", ILI9341_WHITE, y + 64);
    display.setTextSize(1);
    centeredText("by", ILI9341_WHITE, y + 164);
    centeredText("Czech maker", ILI9341_WHITE, y + 184);
    centeredText("www.czechmaker.com", ILI9341_WHITE, y + 204);
  }
  delay(2000);
  if (setupDone != 0) {
    loopScreen();
  } else {
    startSetupScreen();
  }
}

void loopScreen() {
  if (state == 109) {
    previousState = state;
    state = 0;
  } else {
    state = 0;
  }
#ifdef DEBUG
  Serial.println("State is :" + String(state));
#endif
  display.fillScreen(ILI9341_BLACK);

  display.setFont(&FreeSerif9pt7b);
  display.setTextSize(1);
  if (connected != 0 && useOTA != 0) {
    rightText("WiFi", ILI9341_GREEN, 15);
    rightText("OTA", ILI9341_GREEN, 15, 45);
  } else if (connected != 0 && useOTA != 1) {
    rightText("WiFi", ILI9341_GREEN, 15);
    rightText("OTA", ILI9341_WHITE, 15, 45);
  }  else {
    rightText("WiFi", ILI9341_WHITE, 15);
  }
  display.setFont(&FreeSans9pt7b);
  display.setTextSize(1);
  if (updataAvailable != 0) {
    centeredText("!UPDATE AVAILABLE!", ILI9341_GREEN, 10);
  }
  if (horizontal != 0) {
    int tempTextPos = 180;
    int infoText = 30;
    centeredText("Status:", ILI9341_WHITE, infoText);
    display.setTextSize(2);
    centeredText(activeStatus, ILI9341_WHITE, infoText + 32);
    String temp = ("Temp : " + String(inputInt));

    if (isFault != 0) {
      display.setTextSize(1);
      centeredText("Thermocouple error", ILI9341_RED, tempTextPos);
    } else if (inputInt == 1372) {
      display.setTextSize(1);
      centeredText("Thermocouple not", ILI9341_RED, tempTextPos);
      centeredText("connected", ILI9341_RED, tempTextPos + 20);
      noThermocouple = 1;
    } else if (inputInt < 50) {
      centeredText(temp, ILI9341_GREEN, tempTextPos);
      noThermocouple = 0;
    } else if ((inputInt > 50) && (inputInt < 100)) {
      centeredText(temp, ILI9341_ORANGE, tempTextPos);
    } else if (inputInt > 100) {
      centeredText(temp, ILI9341_RED, tempTextPos);
    }
    display.setTextSize(1);
    centeredText("Profile in use:" + String(paste_profile[profileUsed].title), ILI9341_WHITE, tempTextPos + 50);
#ifdef DEBUG
    Serial.println(temp);
#endif
  } else {
    int tempTextPos = 240;
    int infoText = 50;
    centeredText("Status:", ILI9341_WHITE, infoText);
    display.setTextSize(2);
    centeredText(activeStatus, ILI9341_WHITE, infoText + 32);
    String temp = ("Temp : " + String(inputInt));

    if (isFault != 0) {
      display.setTextSize(1);
      centeredText("Thermocouple error", ILI9341_RED, tempTextPos);
    } else if (inputInt == 1372) {
      display.setTextSize(1);
      centeredText("Thermocouple not", ILI9341_RED, tempTextPos);
      centeredText("connected", ILI9341_RED, tempTextPos + 20);
      noThermocouple = 1;
    } else if (inputInt < 50) {
      centeredText(temp, ILI9341_GREEN, tempTextPos);
      noThermocouple = 0;
    } else if ((inputInt > 50) && (inputInt < 100)) {
      centeredText(temp, ILI9341_ORANGE, tempTextPos);
    } else if (inputInt > 100) {
      centeredText(temp, ILI9341_RED, tempTextPos);
    }
    display.setTextSize(1);
    centeredText("Profile in use:" + String(paste_profile[profileUsed].title), ILI9341_WHITE, tempTextPos + 50);
#ifdef DEBUG
    Serial.println(temp);
#endif
  }
}

void startReflowScreen() {
  if (noThermocouple != 1) {
    previousState = state;
    state = 7;
#ifdef DEBUG
    Serial.println("State is :" + String(state));
#endif
    display.fillScreen(ILI9341_BLACK);
    int tempTextPos = 240;
    int infoText = 50;
    display.setFont(&FreeSans9pt7b);
    display.setTextSize(2);
    centeredText("Start reflow?", ILI9341_RED, infoText);
    display.setTextSize(1);
    centeredText("Yes = Select", ILI9341_WHITE, infoText + 32);
    centeredText("No = Back", ILI9341_WHITE, infoText + 64);
  } else {
    noThermocoupleScreen();
  }
}

void stopReflowScreen() {
  previousState = state;
  state = 8;
#ifdef DEBUG
  Serial.println("State is :" + String(state));
#endif
  display.fillScreen(ILI9341_BLACK);
  int tempTextPos = 240;
  int infoText = 50;
  display.setFont(&FreeSans9pt7b);
  display.setTextSize(2);
  centeredText("Stop reflow?", ILI9341_RED, infoText);
  display.setTextSize(1);
  centeredText("Yes = Select", ILI9341_WHITE, infoText + 32);
  centeredText("No = Back", ILI9341_WHITE, infoText + 64);
}

void noThermocoupleScreen() {
#ifdef DEBUG
  Serial.println("Can not start reflow profile as here is no thermocouple connnected!");
#endif
  display.fillScreen(ILI9341_BLACK);
  int infoText = 100;
  display.setFont(&FreeSans9pt7b);
  display.setTextSize(1);
  centeredText("Can not start reflow", ILI9341_RED, infoText);
  centeredText("profile as there is no", ILI9341_RED, infoText + 20);
  centeredText("thermocouple connnected!", ILI9341_RED, infoText + 40);
  delay(5000);
  loopScreen();
}

void mainMenuScreen() {
  previousState = state;
  state = 1;
  numOfPointers = 0;
#ifdef DEBUG
  Serial.println("State is :" + String(state));
#endif
  int y = 55;
  int h = 20;
  display.setFont(&FreeSans9pt7b);
  display.fillScreen(ILI9341_BLACK);
  display.setTextColor(ILI9341_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 4);
  centeredText("Main menu", ILI9341_WHITE, 10);
  if (horizontal != 0) {
    display.fillRect(0, 28, 320, 3, ILI9341_WHITE );
  } else {
    display.fillRect(0, 28, 240, 3, ILI9341_WHITE );
  }
  display.setCursor(10, y);
  if (disableMenu != 1) {
    leftText("Select profile", ILI9341_WHITE, y); rightText("->", ILI9341_WHITE, y);
    y += h;
    numOfPointers++;
    leftText("Change profile", ILI9341_WHITE, y); rightText("->", ILI9341_WHITE, y);
    y += h;
    numOfPointers++;
    leftText("Add profile", ILI9341_WHITE, y); rightText("->", ILI9341_WHITE, y);
    y += h;
    numOfPointers++;
    leftText("Settings", ILI9341_WHITE, y); rightText("->", ILI9341_WHITE, y);
    y += h;
    numOfPointers++;
  }
  leftText("Info", ILI9341_WHITE, y); rightText("->", ILI9341_WHITE, y);

  if (updataAvailable == 1) {
    y += h;
    numOfPointers++;
    leftText("Update firmware", ILI9341_GREEN, y);
  }

  ShowMenuOptions(true);
}

void showSelectProfileScreen() {
  previousState = state;
  state = 2;
  int y = 55; //from left side of the LCD
  int h = 20;
  numOfPointers = profileNum;
  settings_pointer = 0;
#ifdef DEBUG
  Serial.println("State is :" + String(state));
#endif
  display.fillScreen(ILI9341_BLACK);
  //display.setRotation(2);
  display.setFont(&FreeSans9pt7b);
  display.setTextColor(ILI9341_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 4);
  centeredText("Select profile menu", ILI9341_WHITE, 10);
  if (horizontal != 0) {
    display.fillRect(0, 28, 320, 3, ILI9341_WHITE );
  } else {
    display.fillRect(0, 28, 240, 3, ILI9341_WHITE );
  }
  for (int i = 0; i < profileNum; i++) {
    if (i == profileUsed) {
      leftText(paste_profile[i].title, ILI9341_YELLOW, y);
    } else {
      leftText(paste_profile[i].title, ILI9341_WHITE, y);
    }
    y += h;
    leftText(paste_profile[i].alloy, ILI9341_BLUE, y, +15);
    y += h;
  }

  ShowMenuOptions(true);
}

void showChangeProfileScreen() {
  previousState = state;
  state = 3;
#ifdef DEBUG
  Serial.println("State is :" + String(state));
#endif
  int y = 55; //from left side of the LCD
  int h = 20;
  display.setFont(&FreeSans9pt7b);
  display.fillScreen(ILI9341_BLACK);
  display.setTextColor(ILI9341_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 4);
  centeredText("Change profile menu", ILI9341_WHITE, 10);
  if (horizontal != 0) {
    display.fillRect(0, 28, 320, 3, ILI9341_WHITE );
  } else {
    display.fillRect(0, 28, 240, 3, ILI9341_WHITE );
  }
}

void showAddProfileScreen() {
  previousState = state;
  state = 4;
#ifdef DEBUG
  Serial.println("State is :" + String(state));
#endif
  int y = 55; //from left side of the LCD
  int h = 20;
  display.setFont(&FreeSans9pt7b);
  display.fillScreen(ILI9341_BLACK);
  display.setTextColor(ILI9341_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 4);
  centeredText("Add profile menu", ILI9341_WHITE, 10);
  if (horizontal != 0) {
    display.fillRect(0, 28, 320, 3, ILI9341_WHITE );
  } else {
    display.fillRect(0, 28, 240, 3, ILI9341_WHITE );
  }
}


void showSettingsScreen(byte pointer = 0) {
  previousState = state;
  state = 5;
  numOfPointers = 0;
  if (pointer != 0) {
    settings_pointer = pointer;
  } else {
    settings_pointer = 0; // clear pointer
  }
#ifdef DEBUG
  Serial.println("State is: " + String(state));
#endif
  int y = 55; //from left side of the LCD
  int h = 20;
  display.setFont(&FreeSans9pt7b);
  display.fillScreen(ILI9341_BLACK);
  display.setTextColor(ILI9341_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 4);
  centeredText("Settings menu", ILI9341_WHITE, 10);
  if (horizontal != 0) {
    display.fillRect(0, 28, 320, 3, ILI9341_WHITE );
  } else {
    display.fillRect(0, 28, 240, 3, ILI9341_WHITE );
  }
  display.setCursor(30, y);

  setBuzzer(y); //y == 55;
  y += h;
  numOfPointers++; //0

  setDisplay(y);
  y += h;
  numOfPointers++; //1

  setOTA(y);
  y += h;
  numOfPointers++; //2

  setButtons(y);
  y += h;
  numOfPointers++; //3

  setStorage(y);
  y += h;
  numOfPointers++; //4

  if (buttons != 0) {
    setFan(y);
    y += h;
    numOfPointers++; //5
    if (connected != 1) {
      wifiSetupShow(y);
      y += h;
      numOfPointers++;
    }
  } else {
    wifiSetupShow(y);
    y += h;
    numOfPointers++;
  }

  leftText("Test outputs", ILI9341_WHITE, y); rightText("->", ILI9341_WHITE, y);
  //y += h;
  //numOfPointers++;

  ShowMenuOptions(true);
}

void showInfoScreen() {
  previousState = state;
  state = 6;
#ifdef DEBUG
  Serial.println("State is :" + String(state));
#endif
  int y = 55; //from left side of the LCD
  int h = 20;
  display.setFont(&FreeSans9pt7b);
  display.fillScreen(ILI9341_BLACK);
  display.setTextColor(ILI9341_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 4);
  centeredText("Info menu", ILI9341_WHITE, 10);
  if (horizontal != 0) {
    display.fillRect(0, 28, 320, 3, ILI9341_WHITE );
  } else {
    display.fillRect(0, 28, 240, 3, ILI9341_WHITE );
  }
  leftText("- FW version: " + fwVersion, ILI9341_WHITE, y, -15);
  if (connected != 0) {
    String ipAddress = WiFi.localIP().toString();
    leftText("- WiFi: " + String(WiFi.SSID()), ILI9341_WHITE, y + h, -15);
    leftText("- IP: " + ipAddress, ILI9341_WHITE, y + h * 2, -15);
  }
}


void startUpdateScreen() {
  display.fillScreen(ILI9341_BLACK);
  int y;
  if (horizontal != 0) {
    display.setRotation(3);
    y = 40;
    display.setFont(&FreeSans9pt7b);
    display.setTextSize(1);
    centeredText("Update started.It may", ILI9341_GREEN, y);
    centeredText("take 2 - 5 mins to complete.", ILI9341_GREEN, y + 20);
  } else {
    display.setRotation(2);
    y = 100;
    display.setFont(&FreeSans9pt7b);
    display.setTextSize(1);
    centeredText("Update started.It may", ILI9341_GREEN, y);
    centeredText("take 2 - 5 mins to complete.", ILI9341_GREEN, y + 20);
  }
}

void updateOKScreen() {
  display.fillScreen(ILI9341_BLACK);
  int y;
  if (horizontal != 0) {
    display.setRotation(3);
    y = 40;
    display.setFont(&FreeSans9pt7b);
    display.setTextSize(1);
    centeredText("Update successfully", ILI9341_GREEN, y);
    centeredText("completed. Rebooting.", ILI9341_GREEN, y + 32);
  } else {
    display.setRotation(2);
    y = 100;
    display.setFont(&FreeSans9pt7b);
    display.setTextSize(1);
    centeredText("Update successfully", ILI9341_GREEN, y);
    centeredText("completed. Rebooting.", ILI9341_GREEN, y + 32);
  }
  delay(2000);
}

void testOutputsScreen() {
  Serial.println();
  previousState = state;
  state = 9;
  numOfPointers = 0;
  tempPointer = settings_pointer;
  settings_pointer = 0; // clear pointer
#ifdef DEBUG
  Serial.println("State is :" + String(state));
  Serial.println("Settings pointer: " + String(settings_pointer));
  Serial.println("Previous settings pointer: " + String(previousSettingsPointer));
#endif
  int y = 55; //from left side of the LCD
  int h = 20;
  display.setFont(&FreeSans9pt7b);
  display.fillScreen(ILI9341_BLACK);
  display.setTextColor(ILI9341_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 4);
  centeredText("Test outputs menu", ILI9341_WHITE, 10);
  if (horizontal != 0) {
    display.fillRect(0, 28, 320, 3, ILI9341_WHITE );
  } else {
    display.fillRect(0, 28, 240, 3, ILI9341_WHITE );
  }
  display.setCursor(30, y);

  testBuzzer(y); //y == 55;
  y += h;
  numOfPointers++;

  testFan(y);
  y += h;
  numOfPointers++;

  testSSR(y);
  y += h;
  numOfPointers++;

  testLED(y);
  //  y += h;
  //  numOfPointers++;
  ShowMenuOptions(true);
}

void startSetupScreen() {
  previousState = state;
  state = 10;
  numOfPointers = 0;
  //  settings_pointer = 0; // clear pointer
#ifdef DEBUG
  Serial.println("State is :" + String(state));
#endif
  int y = 55; //from left side of the LCD
  int h = 20;
  display.setRotation(2);
  display.setFont(&FreeSans9pt7b);
  display.fillScreen(ILI9341_BLACK);
  display.setTextColor(ILI9341_WHITE);
  display.setTextSize(2);
  display.setCursor(0, 4);
  centeredText("Welcome in", ILI9341_WHITE, y);
  centeredText("the device", ILI9341_WHITE, y += 40);
  centeredText("setup", ILI9341_WHITE, y += 40);

  display.setTextSize(1);
  y = 250;
  leftText(" continue setup", ILI9341_GREEN, y);
  numOfPointers++;
  leftText(" skip setup", ILI9341_RED, y += h);
  ShowMenuOptions(true);
}

void setupButtonsScreen() {
  previousState = state;
  state = 101;
  numOfPointers = 0;
  //  settings_pointer = 0; // clear pointer
#ifdef DEBUG
  Serial.println("State is :" + String(state));
#endif
  int y = 55; //from left side of the LCD
  int h = 20;
  display.setRotation(2);
  display.setFont(&FreeSerif9pt7b);
  display.fillScreen(ILI9341_BLACK);
  display.setTextColor(ILI9341_WHITE);
  display.setTextSize(2);
  display.setCursor(0, 4);
  centeredText("Do you have", ILI9341_WHITE, y);
  centeredText("Menu & Back", ILI9341_WHITE, y += 40);
  centeredText("buttons?", ILI9341_WHITE, y += 40);

  display.setTextSize(1);
  y = 250;
  leftText(" Yes", ILI9341_GREEN, y);
  numOfPointers++;
  leftText(" No", ILI9341_GREEN, y += h);
  numOfPointers++;
  leftText(" skip setup", ILI9341_RED, y += h);
  ShowMenuOptions(true);
}

void setupWiFiScreen() {
  previousState = state;
  state = 102;
  numOfPointers = 0;
  //  settings_pointer = 0; // clear pointer
#ifdef DEBUG
  Serial.println("State is :" + String(state));
#endif
  int y = 55; //from left side of the LCD
  int h = 20;
  display.setRotation(2);
  display.setFont(&FreeSerif9pt7b);
  display.fillScreen(ILI9341_BLACK);
  display.setTextColor(ILI9341_WHITE);
  display.setTextSize(2);
  display.setCursor(0, 4);
  centeredText("Do you want", ILI9341_WHITE, y);
  centeredText("to setup ", ILI9341_WHITE, y += 40);
  centeredText("WiFi?", ILI9341_WHITE, y += 40);

  display.setTextSize(1);
  y = 250;
  leftText(" Yes", ILI9341_GREEN, y);
  numOfPointers++;
  leftText(" No", ILI9341_GREEN, y += h);
  numOfPointers++;
  leftText(" skip setup", ILI9341_RED, y += h);
  ShowMenuOptions(true);
}

void setupWiFiScreen2() {
  wifiSetup();
  previousState = state;
  state = 103;
  numOfPointers = 0;
  //  settings_pointer = 0; // clear pointer
#ifdef DEBUG
  Serial.println("State is :" + String(state));
#endif
  int y = 55; //from left side of the LCD
  int h = 20;
  display.setRotation(2);
  display.setFont(&FreeSerif9pt7b);
  display.fillScreen(ILI9341_BLACK);
  display.setTextColor(ILI9341_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 4);
  centeredText("Please connect to", ILI9341_WHITE, y);
  centeredText("ReflowOvenAP", ILI9341_BLUE, y += h);
  centeredText("open browser and ", ILI9341_WHITE, y += h);
  centeredText("type in this", ILI9341_WHITE, y += h);
  centeredText("address:", ILI9341_WHITE, y += h);
  centeredText(" ", ILI9341_WHITE, y += h);
  centeredText("192.168.4.1", ILI9341_RED, y += h);

  display.setTextSize(1);
  y = 250;
  leftText(" skip wifi setup", ILI9341_GREEN, y);
  numOfPointers++;
  //  leftText(" No", ILI9341_GREEN, y += h);
  //  numOfPointers++;
  leftText(" skip setup", ILI9341_RED, y += h);
  ShowMenuOptions(true);
}

void setupWiFiScreenDone() {
  String ipAddress = WiFi.localIP().toString();
  previousState = state;
  state = 104;
  numOfPointers = 0;
  //  settings_pointer = 0; // clear pointer
#ifdef DEBUG
  Serial.println("State is :" + String(state));
#endif
  int y = 85; //from left side of the LCD
  int h = 20;
  display.setRotation(2);
  display.setFont(&FreeSerif9pt7b);
  display.fillScreen(ILI9341_BLACK);
  display.setTextColor(ILI9341_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 4);
  centeredText("WiFi setup", ILI9341_GREEN, y);
  centeredText("successful! ", ILI9341_GREEN, y += h);
  centeredText("IP adress is:", ILI9341_GREEN, y += h);
  centeredText(ipAddress, ILI9341_BLUE, y += h);
}

void setupWiFiScreenFail() {
  startTime = millis();
  wm.stopConfigPortal();
  previousState = state;
  state = 1040;
  numOfPointers = 0;
  //  settings_pointer = 0; // clear pointer
#ifdef DEBUG
  Serial.println("State is :" + String(state));
#endif
  int y = 85; //from left side of the LCD
  int h = 20;
  display.setRotation(2);
  display.setFont(&FreeSerif9pt7b);
  display.fillScreen(ILI9341_BLACK);
  display.setTextColor(ILI9341_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 4);
  centeredText("WiFi setup", ILI9341_RED, y);
  centeredText("failed! ", ILI9341_RED, y += h);
  centeredText("Restarting", ILI9341_RED, y += h);
  centeredText("WiFiManager...", ILI9341_RED, y += h);
}

void downloadProfilesScreen() {
  previousState = state;
  state = 105;
  numOfPointers = 0;
  //  settings_pointer = 0; // clear pointer
#ifdef DEBUG
  Serial.println("State is :" + String(state));
#endif
  int y = 55; //from left side of the LCD
  int h = 40;
  display.setRotation(2);
  display.setFont(&FreeSerif9pt7b);
  display.fillScreen(ILI9341_BLACK);
  display.setTextColor(ILI9341_WHITE);
  display.setTextSize(2);
  display.setCursor(0, 4);
  centeredText("Do you want", ILI9341_WHITE, y);
  centeredText("to download ", ILI9341_WHITE, y += h);
  centeredText("reflow", ILI9341_WHITE, y += h);
  centeredText("profiles?", ILI9341_WHITE, y += h);

  display.setTextSize(1);
  y = 250;
  h = 20;
  leftText(" yes", ILI9341_GREEN, y);
  numOfPointers++;
  leftText(" skip download", ILI9341_BLUE, y += h);
  numOfPointers++;
  leftText(" skip setup", ILI9341_RED, y += h);
  ShowMenuOptions(true);
}

void profilesDownloadFinished() {
  startTime = millis();
  previousState = state;
  state = 106;
  numOfPointers = 0;
  //  settings_pointer = 0; // clear pointer
#ifdef DEBUG
  Serial.println("State is :" + String(state));
#endif
  int y = 85; //from left side of the LCD
  int h = 20;
  display.setRotation(2);
  display.setFont(&FreeSerif9pt7b);
  display.fillScreen(ILI9341_BLACK);
  display.setTextColor(ILI9341_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 4);
  centeredText("All profiles", ILI9341_GREEN, y);
  centeredText("were", ILI9341_GREEN, y += h);
  centeredText("successfullly!", ILI9341_GREEN, y += h);
  centeredText("downloaded!", ILI9341_GREEN, y += h);
}

void useWebserverScreen() {
  previousState = state;
  tempInt, numOfRecords = 0;
  state = 107;
  numOfPointers = 0;
  //  settings_pointer = 0; // clear pointer
#ifdef DEBUG
  Serial.println("State is :" + String(state));
#endif
  int y = 55; //from left side of the LCD
  int h = 40;
  display.setRotation(2);
  display.setFont(&FreeSerif9pt7b);
  display.fillScreen(ILI9341_BLACK);
  display.setTextColor(ILI9341_WHITE);
  display.setTextSize(2);
  display.setCursor(0, 4);
  centeredText("Do you want", ILI9341_WHITE, y);
  centeredText("to use ", ILI9341_WHITE, y += h);
  centeredText("webserver", ILI9341_WHITE, y += h);

  display.setTextSize(1);
  y = 250;
  h = 20;
  leftText(" yes", ILI9341_GREEN, y);
  numOfPointers++;
  leftText(" no", ILI9341_BLUE, y += h);
  numOfPointers++;
  leftText(" skip setup", ILI9341_RED, y += h);
  ShowMenuOptions(true);
}

void updateFilesDownloading(String temp) {
  //  settings_pointer = 0; // clear pointer
#ifdef DEBUG
  Serial.println("State is :" + String(state));
#endif
  int y = 85; //from left side of the LCD
  int h = 25;;
  if (tempInt == 0) {
    display.setRotation(2);
    display.setFont(&FreeSerif9pt7b);
    display.fillScreen(ILI9341_BLACK);
    display.setTextColor(ILI9341_WHITE);
    display.setTextSize(1);
    display.setCursor(0, 4);
    centeredText("Downloading", ILI9341_GREEN, y);
    centeredText("files:", ILI9341_GREEN, y += h);
    centeredText(" ", ILI9341_GREEN, y += h);
    centeredText("Current file: " + temp, ILI9341_GREEN, y += h);
    centeredText("Files: " + String(tempInt) + " / " + String(numOfRecords), ILI9341_GREEN, y += h);
  } else {
    y = 135;
    centeredText("Current file: " + temp + "%", ILI9341_GREEN, y += h);
    centeredText("Files: " + String(tempInt) + " / " + String(numOfRecords), ILI9341_GREEN, y += h);
  }
}

void webserverDownloadFinished() {
  startTime = millis();
  previousState = state;
  state = 108;
  numOfPointers = 0;
  //  settings_pointer = 0; // clear pointer
#ifdef DEBUG
  Serial.println("State is :" + String(state));
#endif
  int y = 85; //from left side of the LCD
  int h = 20;
  display.setRotation(2);
  display.setFont(&FreeSerif9pt7b);
  display.fillScreen(ILI9341_BLACK);
  display.setTextColor(ILI9341_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 4);
  centeredText("All files", ILI9341_GREEN, y);
  centeredText("for webserver", ILI9341_GREEN, y += h);
  centeredText("were", ILI9341_GREEN, y += h);
  centeredText("successfullly!", ILI9341_GREEN, y += h);
  centeredText("downloaded!", ILI9341_GREEN, y += h);
}

void finishSetupScreen() {
  startTime = millis();
  previousState = state;
  state = 109;
  numOfPointers = 0;
  //  settings_pointer = 0; // clear pointer
#ifdef DEBUG
  Serial.println("State is :" + String(state));
#endif
  int y = 105; //from left side of the LCD
  int h = 40;
  display.setRotation(2);
  display.setFont(&FreeSerif9pt7b);
  display.fillScreen(ILI9341_BLACK);
  display.setTextColor(ILI9341_WHITE);
  display.setTextSize(2);
  display.setCursor(0, 4);
  centeredText("Your setup", ILI9341_WHITE, y);
  centeredText("is finished. ", ILI9341_WHITE, y += h);
}


void setBuzzer (int y) {
  display.fillRect( 30, y - 18, 200, 20, ILI9341_BLACK );
  display.setTextColor(ILI9341_WHITE);
  display.setTextSize(1);
  display.setCursor(30, y);
  display.print("Use buzzer: ");
  if (buzzer != 0) {
    display.println("Yes");
  } else {
    display.println("No");
  }
}

void setButtons (int y) {
  if (state != 101) {
    display.fillRect( 30, y - 18, 200, 20, ILI9341_BLACK );
    display.setTextColor(ILI9341_WHITE);
    display.setTextSize(1);
    display.setCursor(30, y);
    display.print("Menu/Back buttons: ");
    if (buttons != 0) {
      display.println("Yes");
    } else {
      display.println("No");
    }
  }
}

void setFan (int y) {
  display.fillRect( 30, y - 18, 200, 20, ILI9341_BLACK );
  display.setTextColor(ILI9341_WHITE);
  display.setTextSize(1);
  display.setCursor(30, y);
  display.print("Use fan: ");
  if (fan != 0) {
    display.println("Yes");
  } else {
    display.println("No");
  }
}

void setDisplay (int y) {
  display.fillRect( 30, y - 18, 200, 20, ILI9341_BLACK );
  display.setTextColor(ILI9341_WHITE);
  display.setTextSize(1);
  display.setCursor(30, y);
  display.print("Orientation: ");
  if (horizontal != 0) {
    display.println("Horizontal");
  } else {
    display.println("Vertical");
  }
}

void setOTA (int y) {
  display.fillRect( 30, y - 18, 200, 20, ILI9341_BLACK );
  display.setTextColor(ILI9341_WHITE);
  display.setTextSize(1);
  display.setCursor(30, y);
  display.print("Update FW by OTA: ");
  if (useOTA != 0) {
    display.println("Yes");
  } else {
    display.println("No");
  }
}

void setStorage (int y) {
  display.fillRect( 30, y - 18, 200, 20, ILI9341_BLACK );
  display.setTextColor(ILI9341_WHITE);
  display.setTextSize(1);
  display.setCursor(30, y);
  display.print("Use SPIFFS: ");
  if (useSPIFFS != 0) {
    display.println("Yes");
  } else {
    display.println("No");
  }
}

void wifiSetupShow(int y) {
  display.fillRect( 30, y - 18, 200, 20, ILI9341_BLACK );
  display.setTextColor(ILI9341_WHITE);
  display.setTextSize(1);
  display.setCursor(30, y);
  display.print("Setup WiFi");
}

void testBuzzer(int y) {
  //testState = LOW;
  display.fillRect( 30, y - 18, 200, 20, ILI9341_BLACK );
  display.setTextColor(ILI9341_WHITE);
  display.setTextSize(1);
  display.setCursor(30, y);
  display.print("Test buzzer: ");
  if (testState != LOW) {
    display.println("On");
    digitalWrite(buzzerPin, HIGH);
  } else {
    display.println("Off");
    digitalWrite(buzzerPin, LOW);
  }
}

void testFan (int y) {
  display.fillRect( 30, y - 18, 200, 20, ILI9341_BLACK );
  display.setTextColor(ILI9341_WHITE);
  display.setTextSize(1);
  display.setCursor(30, y);
  display.print("Test fan: ");
  if (testState != LOW) {
    display.println("On");
    digitalWrite(fanPin, HIGH);
  } else {
    display.println("Off");
    digitalWrite(fanPin, LOW);
  }
}

void testSSR(int y) {
  display.fillRect( 30, y - 18, 200, 20, ILI9341_BLACK );
  display.setTextColor(ILI9341_WHITE);
  display.setTextSize(1);
  display.setCursor(30, y);
  display.print("Test SSR: ");
  if (testState != LOW) {
    display.println("On");
    digitalWrite(ssrPin, HIGH);
  } else {
    display.println("Off");
    digitalWrite(ssrPin, LOW);
  }
}

void testLED(int y) {
  display.fillRect( 30, y - 18, 200, 20, ILI9341_BLACK );
  display.setTextColor(ILI9341_WHITE);
  display.setTextSize(1);
  display.setCursor(30, y);
  display.print("Test LED: ");
  if (testState != LOW) {
    display.println("On");
    digitalWrite(ledPin, HIGH);
  } else {
    display.println("Off");
    digitalWrite(ledPin, LOW);
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
