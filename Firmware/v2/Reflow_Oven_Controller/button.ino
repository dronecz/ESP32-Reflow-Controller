
String profileAddress = "http://czechmaker.com/roc/profiles/";
String profileNamesDownload[] = {"Sn42Bi576Ag04.json", "sn63pb37.json", "sn965ag30cu05.json"};
String webserverAddress = "http://czechmaker.com/roc/src/";
String webserverFileNames[] = {"bootstrap.bundle.min.js", "bootstrap.min.css", "bootstrap.min.js", "bootstrap-grid.min.css", "bootstrap-reboot.min.css", "jquery.min.js", "jquery.slim.min.js", "simple-sidebar.css"};

byte digitalButton (int pin) {

  for (int i = 0; i < numDigButtons; i++) {
    // Read the state of the button

    buttonVal[i] = digitalRead(digitalButtonPins[i]);

    //delay(10);

    // Test for button pressed and store the down time
    if (buttonVal[i] == HIGH && buttonLast[i] == LOW && (millis() - btnDnTime[i]) > debounce)
    {
      btnUpTime[i] = millis();
    }

    // Test for button release and store the up time
    if (buttonVal[i] == LOW && buttonLast[i] == HIGH && (millis() - btnUpTime[i]) > debounce)
    {
      if (ignoreUp[i] == false ) event1(digitalButtonPins[i]);
      else ignoreUp[i] = false;
      btnDnTime[i] = millis();
    }
    /*-----------------------------------------------------------------------------------------------------*/
    // Test for button held down for longer than the hold time
    if (buttonVal[i] == LOW && menuMode[i] == false && (millis() - btnDnTime[i]) > long(holdTime))
    {
      //Serial.println("Menu Mode");
      ignoreUp[i] = true;
      btnDnTime[i] = millis();
      menuMode[i] = true;
    }
    if (buttonVal[i] == HIGH && buttonLast[i] == LOW && (millis() - btnDnTime[i]) > debounce)
    {
      if (ignoreUp[i] == false && menuMode[i] == true) event2(digitalButtonPins[i]);
      else ignoreUp[i] = false;
      btnUpTime[i] = millis();
    }
    if (buttonVal[i] == LOW && menuMode[i] == true && (millis() - btnDnTime[i]) > long(holdTime))
    {
      //Serial.println("Normal Mode");
      ignoreUp[i] = true;
      btnDnTime[i] = millis();
      menuMode[i] = false;
    }
    buttonLast[i] = buttonVal[i];
  }
}

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long analogLastDebounceTime = 0;  // the last time the output pin was toggled
//long debounceDelay = 8;    // the debounce time; increase if the output flickers


void readAnalogButtons() {
  AXIS_X.readAxis();
  AXIS_Y.readAxis();
  //if (menuState != MENU_STATE_EDIT_NUMBER) {
  if (AXIS_X.wasAxisPressed() == 1) {
    if (horizontal != 0) {
      if (verboseOutput != 0) {
        Serial.println("Right");
      } if (buttons != 1) { // back button if there is not dedicted Back button on board
        if (state == 1 || state == 7 || state == 8) {
          loopScreen();
          settings_pointer = 0;
        } else {
          if (state > 0) {
            settings_pointer = previousSettingsPointer;
            mainMenuScreen();
          }
        }
      }
    } else {
      if (settings_pointer < numOfPointers) {
        settings_pointer++;
        UpdateSettingsPointer();
        if (verboseOutput != 0) {
          Serial.println("Down; Settings pointer:  " + String(settings_pointer));
        }
      }
    }
  } else if (AXIS_X.wasAxisPressed() == 2) {
    if (horizontal != 0) {
      if (verboseOutput != 0) {
        Serial.println("Left");
      }
      if ( buttons != 1 ) {
        if (state == 0 ) { // menu button if there is not dedicted Menu button on board
          mainMenuScreen();
        }
      }
    } else {
      if (settings_pointer > 0) {
        settings_pointer--;
        UpdateSettingsPointer();
        if (verboseOutput != 0) {
          Serial.println("Up; Settings pointer: " + String(settings_pointer));
        }
      }
    }
  } else if (AXIS_Y.wasAxisPressed() == 1) {
    if (horizontal != 0) {
      if (settings_pointer < numOfPointers) {
        settings_pointer++;
        UpdateSettingsPointer();
        if (verboseOutput != 0) {
          Serial.println("Down; Settings pointer:  " + String(settings_pointer));
        }
      }
    } else {
      if (verboseOutput != 0) {
        Serial.println("Left");
      }
      if ( buttons != 1 ) {
        if (state == 0 ) { // menu button if there is not dedicted Menu button on board
          mainMenuScreen();
        }
      }
    }
  } else if (AXIS_Y.wasAxisPressed() == 2) {
    if (horizontal != 0) {
      settings_pointer--;
      UpdateSettingsPointer();
      if (verboseOutput != 0) {
        Serial.println("Up; Settings pointer: " + String(settings_pointer));
      }
    } else {
      if (verboseOutput != 0) {
        Serial.println("Right");
      } if (buttons != 1) { // back button if there is not dedicted Back button on board
        if (state == 1 || state == 7 || state == 8) {
          loopScreen();
          settings_pointer = 0;
        } else {
          if (state > 0) {
            settings_pointer = previousSettingsPointer;
            mainMenuScreen();
          }
        }
      }
    }
  }
}

// Events to trigger by click and press+hold

void event1(int pin) {
  if (pin > 20  && pin < 40) {
    if (pin == 27) { // Select button
      //previousState = state;
      if (verboseOutput != 0) {
        Serial.println("---------------------");
        Serial.println("Previous state is: " + String(previousState));
        Serial.println("State is: " + String(state));
        Serial.println("Settings pointer: " + String(settings_pointer));
        Serial.println("Previous settings pointer: " + String(previousSettingsPointer));
      }
      if (state == 0) {
        if (profileIsOn != 0)  {
          stopReflowScreen();
          activeStatus = "Idle";
        } else {
          startReflowScreen();
        }
      }
      else if (state == 1) { // main menu
        if (ovenMode != 1) {
          if (settings_pointer == 0) {
            if (disableMenu != 0) {
              showInfoScreen();
            } else {
              showSelectBakeSettingsScreen();
            }
          } else if (settings_pointer == 1) {
            showSettingsScreen();
          } else if  (settings_pointer == 2) {
            showInfoScreen();
          }else if (settings_pointer == 3 ) {
            updateFirmware();
          }
        } else {
          if (settings_pointer == 0) {
            if (disableMenu != 0) {
              showInfoScreen();
            } else {
              showSelectProfileScreen();
            }
          } else if (settings_pointer == 1) {
            showChangeProfileScreen();
          } else if  (settings_pointer == 2) {
            showAddProfileScreen();
          } else if  (settings_pointer == 3) {
            showSettingsScreen();
          } else if (settings_pointer == 4) {
            showInfoScreen();
          } else if (settings_pointer == 5 ) {
            updateFirmware();
          }
          //previousSettingsPointer = settings_pointer;
        }
      } else if (state == 2) { // select profile
        saveSelectedProfile(settings_pointer);
        showSelectProfileScreen();
      } else if (state == 5) { // settings
        //settings_pointer = 0; // clear pointer
        if (settings_pointer == 0) {
          ovenMode = !ovenMode;
          bool temp = ovenMode;
          if (verboseOutput != 0) {
            Serial.println("Oven mode value is: " + String(ovenMode));
          }
          setMode(55);
          changeValues("ovenMode", temp, 1);
        } else if (settings_pointer == 1) {
          buzzer = !buzzer;
          bool temp = buzzer;
          if (verboseOutput != 0) {
            Serial.println("Buzzer value is: " + String(buzzer));
          }
          setBuzzer(75);
          changeValues("buzzer", temp, 1);
        } else if (settings_pointer == 2) {
          horizontal = !horizontal;
          bool temp = horizontal;
          if (verboseOutput != 0) {
            Serial.println("Display value is: " + String(horizontal));
          }
          setDisplay(95);
          changeValues("horizontal", temp, 1);
          previousSettingsPointer, settings_pointer = 0;
          startScreen();
        } else if  (settings_pointer == 3) {
          useOTA = !useOTA;
          bool temp = useOTA;
          if (verboseOutput != 0) {
            Serial.println("Download FW by OTA: " + String(useOTA));
          }
          setOTA(115);
          changeValues("useOTA", temp, 1);
        }
        else if (settings_pointer == 4) {
          buttons = !buttons;
          bool temp = buttons;
          if (verboseOutput != 0) {
            Serial.println("Buttons value is: " + String(buttons));
          }
          setButtons(135);
          changeValues("buttons", temp, 1);
          showSettingsScreen();
        } else if (settings_pointer == 5) {
          useSPIFFS = !useSPIFFS;
          bool temp = useSPIFFS;
          if (verboseOutput != 0) {
            Serial.println("Use SPIFFS: " + String(useSPIFFS));
          }
          setStorage(155);
          changeValues("useSPIFFS", temp, 1);
        } else if  (settings_pointer == 6) {
          if (buttons != 0) {
            fan = !fan;
            bool temp = fan;
            if (verboseOutput != 0) {
              Serial.println("Fan value is: " + String(fan));
            }
            setFan(175);
            changeValues("fan", temp, 1);
          } else {
            if (connected != 1) {
              if (verboseOutput != 0) {
                Serial.println("Calling WiFi setup function");
              }
              wifiSetup();
            } else {
              testOutputsScreen();
            }
          }
        } else if  (settings_pointer == 7) {
          if (buttons != 0) {
            if (connected != 1) {
              if (verboseOutput != 0) {
                Serial.println("Calling WiFi setup function");
              }
              wifiSetup();
            }
          } else {
            testOutputsScreen();
          }
        } else if  (settings_pointer == 8) {
          testOutputsScreen();
        }
        //previousSettingsPointer = settings_pointer; //store previous position in menu
      } else if (state == 7) {
        //reflowStatus = REFLOW_STATUS_ON;
        profileIsOn = 1;
        Serial.println("Profile is ON");
        disableMenu = 1;
        loopScreen();
      } else if (state == 8) {
        profileIsOn = 0;
        disableMenu = 0;
        Serial.println("Profile is OFF");
        events.send(String(profileIsOn).c_str(), "showchart");
        Serial.println("Sending end of the profile to the webserver!");
        // Button press is for cancelling
        // Turn off reflow process
        reflowStatus = REFLOW_STATUS_OFF;
        // Reinitialize state machine
        reflowState = REFLOW_STATE_IDLE;
        loopScreen();
      } else if (state == 9) {
        //settings_pointer = 0; // clear pointer
        if (settings_pointer == 0) {
          if (testState != LOW) {
            testState = LOW;
          } else {
            testState = HIGH;
          }
          testBuzzer(55);
        } else if (settings_pointer == 1) {
          if (testState != LOW) {
            testState = LOW;
          } else {
            testState = HIGH;
          }
          testFan(75);
        } else if  (settings_pointer == 2) {
          if (testState != LOW) {
            testState = LOW;
          } else {
            testState = HIGH;
          }
          testSSR(95);
        } else if (settings_pointer == 3) {
          if (testState != LOW) {
            testState = LOW;
          } else {
            testState = HIGH;
          }
          testLED(115);
        }
      } else if (state == 10) {
        //settings_pointer = 0; // clear pointer
        if (settings_pointer == 0) {
          setupButtonsScreen();
        } else {
          loopScreen();
          setupDone = 1;
          changeValues("setupDone", setupDone, 0);
        }
      } else if (state == 101) {
        //settings_pointer = 0; // clear pointer
        if (settings_pointer == 0) {
          buttons = 1;
          changeValues("buttons", buttons, 1);
          setupWiFiScreen();
        } else if (settings_pointer == 1) {
          buttons = 0;
          changeValues("buttons", buttons, 1);
          setupWiFiScreen();
        } else {
          loopScreen();
          setupDone = 1;
          changeValues("setupDone", setupDone, 0);
        }
      } else if (state == 102) {
        //settings_pointer = 0; // clear pointer
        if (settings_pointer == 0) {
          setupWiFiScreen2();
        } else if (settings_pointer == 1) {
          //set next screen!
        } else {
          loopScreen();
          setupDone = 1;
          changeValues("setupDone", setupDone, 0);
        }
      } else if (state == 103) {
        if (settings_pointer == 0) {
          //add next step after wifi skip!
        } else {
          loopScreen();
          setupDone = 1;
          changeValues("setupDone", setupDone, 0);
        }
      } else if (state == 105) {
        //settings_pointer = 0; // clear pointer
        if (settings_pointer == 0) {
          downloadDataScreen();
          numOfRecords = (int)sizeof(profileNamesDownload) / sizeof(profileNamesDownload[0]);
          tempInt = 0;
          for (int i = 0; i < numOfRecords; i++ ) {
            tempInt += getFiles(profileAddress, profileNamesDownload[i], "/profiles");
            Serial.println("Number of profiles download: " + String(tempInt));
          }
          listDir(SPIFFS, "/profiles", 0);
        } else if (settings_pointer == 1) {
          useWebserverScreen();
        } else {
          loopScreen();
          setupDone = 1;
          changeValues("setupDone", setupDone, 0);
        }
      } else if (state == 107) {

        //settings_pointer = 0; // clear pointer
        if (settings_pointer == 0) {
          downloadDataScreen();
          Serial.println("*****************");
          Serial.println("Number of files for download: " + String(numOfRecords));
          Serial.println("Number of files for download: " + String(tempInt));
          Serial.println("*****************");
          numOfRecords = (int)sizeof(webserverFileNames) / sizeof(webserverFileNames[0]);
          Serial.println("Number of files for download: " + String(numOfRecords));
          tempInt = 0;
          Serial.println("*****************");
          Serial.println("Number of files for download: " + String(numOfRecords));
          Serial.println("Number of files for download: " + String(tempInt));
          Serial.println("*****************");

          for (int i = 0; i < numOfRecords; i++ ) {
            tempInt += getFiles(webserverAddress, webserverFileNames[i], "/src");
            Serial.println("Number of files for download: " + String(tempInt));
          }
          listDir(SPIFFS, "/src", 0);
          //          setupDone = 1;
          useWebserver = 1;
          changeValues("setupDone", setupDone, 0);
          changeValues("useWebserver", useWebserver, 0);
        }
      }
      if (verboseOutput != 0) {
        Serial.println("Select");
        Serial.println("---------------------");
      }
    } else if (pin == 32) { //Menu button
      if (state == 0) {
        mainMenuScreen();
      }
      if (verboseOutput != 0) {
        Serial.println("Menu");
        Serial.println("State is :" + String(state));
      }
    } else if (pin == 33) { // Back button
      //state = 0;
      if (state == 1 || state == 7 || state == 8) {
        loopScreen();
        settings_pointer = previousSettingsPointer;
      } else if (state == 9) {
        showSettingsScreen(tempPointer);
      } else {
        if (state > 0) {
          settings_pointer = previousSettingsPointer;
          mainMenuScreen();
        }
      }
      if (verboseOutput != 0) {
        Serial.println("---------------------");
        Serial.println("Back");
        Serial.println("State is :" + String(state));
        Serial.println("Settings pointer: " + String(settings_pointer));
        Serial.println("Previous settings pointer: " + String(previousSettingsPointer));
        Serial.println("---------------------");
      }
    } else if (verboseOutput != 0) {
      Serial.println("button 1 (" + String(pin) + ")");
    }
  }
  delay(50);
}

void event2(int pin)
{
  if (pin > 20 && pin < 40) {
    Serial.println("button 2 (" + String(pin) + ")");
  }
  delay(50);
  //  if (pin == 33) {
  //    loopScreen();
  //  }
}
