
extern JsonArray array;
//extern byte menuSelectLine;
#define ARROW 0x7e


void processMenu() {
  if (state == 0) { // home screen
    //loopScreen();
    return;
  } else if (state == 1) { // main menu
    //mainMenuScreen();
    return;
  } else if (state == 2) { // select profile

  } else if (state == 3) { // change profile

  } else if (state == 4) { // add profile

  } else if (state == 5) { // settings

  } else if (state == 6) { // info

  } else {

  }
  //return;
}

//extern int inputInt;

//extern bool menu;
//#define font &FreeSans9pt7b
char *menuItems[] = {"Select profile", "Change profile", "Add profile", "Settings", "Info"};
#define menuItemsSize sizeof(menuItems)
int activeMenu = 0;
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

void rightText(String text, uint16_t color, int yCord, int xCord = 0) {
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
  display.setCursor(((display.width() - w) - 10), yCord/*(yCord + (h /2))*/); //
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

  if ( state >= 1 || state <= 9)
  {

    UpdateSettingsPointer();
  }
  //  else if ( state == 11 )
  //  {
  //    // button 0
  //    display.fillRect( display.width() - 100,  buttonPosY[0] - 2, 100, buttonHeight + 4, ILI9341_BLACK );
  //    display.fillRect( display.width() - 5,  buttonPosY[0], buttonWidth, buttonHeight, ILI9341_GREEN );
  //    switch ( settings_pointer )
  //    {
  //
  //      case 1:
  //      case 2:
  //      case 3:
  //      case 4:
  //      case 5:
  //        //println_Right( display, "CHANGE", display.width() - 27, buttonPosY[0] + 8 );
  //        break;
  //
  //      default:
  //        //println_Right( display, "SELECT", display.width() - 27, buttonPosY[0] + 8 );
  //        break;
  //    }
  //
  //    // button 1
  //    display.fillRect( display.width() - 5,  buttonPosY[1], buttonWidth, buttonHeight, ILI9341_RED );
  //    //println_Right( display, "BACK", display.width() - 27, buttonPosY[1] + 8 );
  //
  //    // button 2
  //    display.fillRect( display.width() - 5,  buttonPosY[2], buttonWidth, buttonHeight, ILI9341_BLUE );
  //    //println_Right( display, "/\\", display.width() - 27, buttonPosY[2] + 8 );
  //
  //    // button 3
  //    display.fillRect( display.width() - 5,  buttonPosY[3], buttonWidth, buttonHeight, ILI9341_YELLOW );
  //    //println_Right( display, "\\/", display.width() - 27, buttonPosY[3] + 8 );
  //
  //    UpdateSettingsPointer();
  //  }
  //  else if ( state == 12 )
  //  {
  //    // button 0
  //    display.fillRect( display.width() - 5,  buttonPosY[0], buttonWidth, buttonHeight, ILI9341_GREEN );
  //    //println_Right( display, "SELECT", display.width() - 27, buttonPosY[0] + 8 );
  //
  //    // button 1
  //    display.fillRect( display.width() - 5,  buttonPosY[1], buttonWidth, buttonHeight, ILI9341_RED );
  //    //println_Right( display, "BACK", display.width() - 27, buttonPosY[1] + 8 );
  //
  //    // button 2
  //    display.fillRect( display.width() - 5,  buttonPosY[2], buttonWidth, buttonHeight, ILI9341_BLUE );
  //    //println_Right( display, "/\\", display.width() - 27, buttonPosY[2] + 8 );
  //
  //    // button 3
  //    display.fillRect( display.width() - 5,  buttonPosY[3], buttonWidth, buttonHeight, ILI9341_YELLOW );
  //    //println_Right( display, "\\/", display.width() - 27, buttonPosY[3] + 8 );
  //
  //    UpdateSettingsPointer();
  //  }
  //  else if ( state == 13 ) // restore settings to default
  //  {
  //    // button 0
  //    display.fillRect( display.width() - 5,  buttonPosY[0], buttonWidth, buttonHeight, ILI9341_GREEN );
  //    //println_Right( display, "YES", display.width() - 27, buttonPosY[0] + 8 );
  //
  //    // button 1
  //    display.fillRect( display.width() - 5,  buttonPosY[1], buttonWidth, buttonHeight, ILI9341_RED );
  //    //println_Right( display, "NO", display.width() - 27, buttonPosY[1] + 8 );
  //  }
  //  else if ( state == 1 || state == 2 || state == 16 ) // warmup, reflow, calibration
  //  {
  //    // button 0
  //    display.fillRect( display.width() - 5,  buttonPosY[0], buttonWidth, buttonHeight, ILI9341_GREEN );
  //    //println_Right( display, "ABORT", display.width() - 27, buttonPosY[0] + 8 );
  //  }
  //  else if ( state == 3 ) // Finished
  //  {
  //    display.fillRect( display.width() - 100,  buttonPosY[0] - 2, 100, buttonHeight + 4, ILI9341_BLACK );
  //
  //    // button 0
  //    display.fillRect( display.width() - 5,  buttonPosY[0], buttonWidth, buttonHeight, ILI9341_GREEN );
  //    //println_Right( display, "MENU", display.width() - 27, buttonPosY[0] + 8 );
  //  }
  //  else if ( state == 15 )
  //  {
  //    // button 0
  //    display.fillRect( display.width() - 5,  buttonPosY[0], buttonWidth, buttonHeight, ILI9341_GREEN );
  //    //println_Right( display, "START", display.width() - 27, buttonPosY[0] + 8 );
  //
  //    // button 1
  //    display.fillRect( display.width() - 5,  buttonPosY[1], buttonWidth, buttonHeight, ILI9341_RED );
  //    //println_Right( display, "BACK", display.width() - 27, buttonPosY[1] + 8 );
  //  }
}

void UpdateSettingsPointer() {
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
    display.fillRect( 0, display.height() - 50, display.width(), 40, ILI9341_BLACK );
    switch ( settings_pointer )
    {
      case 0:
        centeredText("Set buzzer on/off.", ILI9341_GREEN, 300);
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
    display.fillRect( 0, display.height() - 50, display.width(), 40, ILI9341_BLACK );
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
          centeredText("WiFi Setup", ILI9341_GREEN, 300);
        }
        break;
      case 6:
        if (buttons != 0) {
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
    display.fillRect( 0, display.height() - 50, display.width(), 40, ILI9341_BLACK );
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
  loopScreen();
}

void loopScreen() {
  state = 0;
#ifdef DEBUG
  Serial.println("State is :" + String(state));
#endif
  display.fillScreen(ILI9341_BLACK);

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
    } else if (inputInt < 50) {
      centeredText(temp, ILI9341_GREEN, tempTextPos);
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
    } else if (inputInt < 50) {
      centeredText(temp, ILI9341_GREEN, tempTextPos);
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

void showSelectProfile() {
  previousState = state;
  state = 2;
  int y = 55; //from left side of the LCD
  int h = 20;
  numOfPointers = profileNum;
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

void showChangeProfile() {
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

void showAddProfile() {
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

void wifiSetupShow(int y) {
  display.fillRect( 30, y - 18, 200, 20, ILI9341_BLACK );
  display.setTextColor(ILI9341_WHITE);
  display.setTextSize(1);
  display.setCursor(30, y);
  display.print("Setup WiFi");
}

void showSettings(byte pointer = 0) {
  previousState = state;
  state = 5;
  numOfPointers = 0;
  settings_pointer = 0; // clear pointer
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
  centeredText("Settings menu", ILI9341_WHITE, 10);
  if (horizontal != 0) {
    display.fillRect(0, 28, 320, 3, ILI9341_WHITE );
  } else {
    display.fillRect(0, 28, 240, 3, ILI9341_WHITE );
  }
  display.setCursor(30, y);

  setBuzzer(y); //y == 55;
  y += h;
  numOfPointers++;

  setDisplay(y);
  y += h;
  numOfPointers++;

  setOTA(y);
  y += h;
  numOfPointers++;

  setButtons(y);
  y += h;
  numOfPointers++;

  setStorage(y);
  y += h;
  numOfPointers++;

  if (buttons != 0) {
    setFan(y);
    y += h;
    numOfPointers++;
  }

  wifiSetupShow(y);
  y += h;
  numOfPointers++;

  leftText("Test outputs", ILI9341_WHITE, y); rightText("->", ILI9341_WHITE, y);
  //y += h;
  //numOfPointers++;

  ShowMenuOptions(true);
}

void showInfo() {
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

void updateOK() {
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

void testOutputs() {
  previousState = state;
  state = 9;
  numOfPointers = 0;
  settings_pointer = 0; // clear pointer
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
