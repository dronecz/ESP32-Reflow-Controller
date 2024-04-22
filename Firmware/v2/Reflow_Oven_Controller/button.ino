byte readBtn() {
  int anaRead[2];
  bool digRead[3];
  byte dataRead = 0;
  anaRead[0] = analogRead(btnPin[0]);
  anaRead[1] = analogRead(btnPin[1]);
  digRead[0] = digitalRead(btnPin[2]);
  digRead[1] = digitalRead(btnPin[3]);
  digRead[2] = digitalRead(btnPin[4]);
  if (anaRead[0] > 3000)      { // Right button
    dataRead = 1;
  }
  else if (anaRead[0] > 1000) { // Left button
    dataRead = 2;
  }
  if (anaRead[1] > 3000)      { // Up button
    dataRead = 3;
  }
  else if (anaRead[1] > 1000) { // Down button
    dataRead = 4;
  }
  if (digRead[0] == 0)        { // Select button
    dataRead = 5;
  }
  if (digRead[1] == 0)        { // Back button
    dataRead = 6;
  }
  if (digRead[2] == 0)        { // Menu button
    dataRead = 7;
  }

  return dataRead;
}

// This code is based on Debounce sketch provided by Arduino IDE
void readButtons() {

  // Read the state of the button
  byte reading = readBtn();

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading !=  lastButtonNum) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      buttonEvent(reading);
    }
  }

  // save the reading. Next time through the loop, it'll be the lastButtonNum:
  lastButtonNum = reading;
}

//
//// Events to trigger by click and press+hold
//

void buttonEvent(byte number) {
  Serial.println("Number received:" + String(number));
  if (number == 1) {
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
        Serial.println("Left (vertical)");
      }
      if ( buttons != 1 ) {
        if (state == 0 ) { // menu button if there is not dedicted Menu button on board
          mainMenuScreen();
        }
      }
    }
  } else if (number == 2) {
    if (horizontal != 0) {
      settings_pointer--;
      UpdateSettingsPointer();
      if (verboseOutput != 0) {
        Serial.println("Up; Settings pointer: " + String(settings_pointer));
      }
    } else {
      if (verboseOutput != 0) {
        Serial.println("Right (vertical)");
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
  } else if (number == 4) {
    if (horizontal != 0) {
      if (verboseOutput != 0) {
        //Serial.println("Right");
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
          Serial.println("Down (vertical)"); //; Settings pointer:  " + String(settings_pointer));
        }
      }
    }
  } else if (number == 3) {
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
          Serial.println("Up (vertical)"); // Settings pointer: " + String(settings_pointer));
        }
      }
    }
  }  else if (number == 5) { // Select button
    //previousState = state;
    if (verboseOutput != 0) {
      Serial.println("---------------------");
      Serial.println("Select button was pressed");
      Serial.println("Previous state is: " + String(previousState));
      Serial.println("State is: " + String(state));
      Serial.println("Settings pointer: " + String(settings_pointer));
      Serial.println("Previous settings pointer: " + String(previousSettingsPointer));
      Serial.println("---------------------");
    }
    if (state == 0) {
      if (profileIsOn != 0) {
        stopReflowScreen();
        activeStatus = "Idle";
      } else {
        startReflowScreen();
      }
    }
    else if (state == 1) { // main menu
      if (settings_pointer == 0) {
        if (disableMenu != 0) {
          showInfo();
        } else {
          showSelectProfile();
        }
      } else if (settings_pointer == 1) {
        showChangeProfile();
      } else if  (settings_pointer == 2) {
        showAddProfile();
      } else if  (settings_pointer == 3) {
        showSettings();
      } else if (settings_pointer == 4) {
        showInfo();
      } else if (settings_pointer == 5 ) {
        updateFirmware();
      }
    } else if (state == 2) { // select profile
      saveSelectedProfile(settings_pointer);
      showSelectProfile();
    } else if (state == 5) { // settings
      if (buttons != 0) {
        if (settings_pointer == 0) {
          buttons = !buttons;
          if (verboseOutput != 0) {
            Serial.println("Buttons value is: " + String(buttons));
          }
          setButtons(55);
          updatePreferences();
          showSettings();
        } else if (settings_pointer == 1) {
          fan = !fan;
          if (verboseOutput != 0) {
            Serial.println("Fan value is: " + String(fan));
          }
          setFan(75);
          updatePreferences();
        } else if (settings_pointer == 2) {
          horizontal = !horizontal;
          if (verboseOutput != 0) {
            Serial.println("Display value is: " + String(horizontal));
          }
          setDisplayOrientation(95);
          updatePreferences();
          previousSettingsPointer, settings_pointer = 0;
          startScreen();
        } else if (settings_pointer == 3) {
          buzzer = !buzzer;
          if (verboseOutput != 0) {
            Serial.println("Buzzer value is: " + String(buzzer));
          }
          setBuzzer(115);
          updatePreferences();
        } else if (settings_pointer == 4) {
          useSPIFFS = !useSPIFFS;
          if (verboseOutput != 0) {
            Serial.println("Use SPIFFS: " + String(useSPIFFS));
          }
          setStorage(135);
          updatePreferences();
        } else if (settings_pointer == 5) {
          testOutputs();
        } else {
          wifiSettingsScreen();
        }
      } else {
        if (settings_pointer == 0) {
          buttons = !buttons;
          if (verboseOutput != 0) {
            Serial.println("Buttons value is: " + String(buttons));
          }
          setButtons(55);
          updatePreferences();
          showSettings();
        } else if (settings_pointer == 1) {
          horizontal = !horizontal;
          if (verboseOutput != 0) {
            Serial.println("Display value is: " + String(horizontal));
          }
          setDisplayOrientation(75);
          updatePreferences();
          previousSettingsPointer, settings_pointer = 0;
          startScreen();
        } else if (settings_pointer == 2) {
          buzzer = !buzzer;
          if (verboseOutput != 0) {
            Serial.println("Buzzer value is: " + String(buzzer));
          }
          setBuzzer(95);
          updatePreferences();
        } else if (settings_pointer == 3) {
          useSPIFFS = !useSPIFFS;
          if (verboseOutput != 0) {
            Serial.println("Use SPIFFS: " + String(useSPIFFS));
          }
          setStorage(115);
          updatePreferences();
        } else if (settings_pointer == 4) {
          testOutputs();
        } else {
          wifiSettingsScreen();
        }
      }
    } else if (state == 51) {
      if (settings_pointer == 0) {
        wifiSetupCancel();
      }
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
      //        } else if  (settings_pointer == 4) {
      //          fan = !fan;
      //          if (verboseOutput != 0) {
      //            Serial.println("Fan value is: " + String(fan));
      //          }
      //          setFan(135);
      //          updatePreferences();
      //        }
      //previousSettingsPointer = settings_pointer; //store previous position in menu
    } else if (state == 10) {
      if (settings_pointer == 0) {
        useOTA = !useOTA;
        if (verboseOutput != 0) {
          Serial.println("Download FW by OTA: " + String(useOTA));
        }
        setOTA(55);
        updatePreferences();
      } else if (settings_pointer == 1) {
        if (wifiConfigured != 0) {
          if (verboseOutput != 0) {
            Serial.println("Starting up WiFi..");
          }
          //wifiRunning = !wifiRunning;
          if (wifiConnected != 1) {
            connectWiFi();
          } else {
            disconnectWiFi();
          }
          setWiFi(55);
          if (wifiConnected != 1) {
            wifiConnectionScreen(0);
          } else {
            wifiConnectionScreen(4);
          }
        } else {
          if (verboseOutput != 0) {
            Serial.println("Calling WiFi setup function");
          }
          wifiSetupShow(75);
          wifiSetup();
        }
      } else {
        //          if (verboseOutput != 0) {
        //            Serial.println("Calling WiFi setup function");
        //          }
        //          wifiSetupShow(75);
        //          wifiSetup();
      }
    }
    if (verboseOutput != 0) {
      Serial.println("Select");
      Serial.println("---------------------");
    }
  } else if (number == 7) { //Menu button
    if (state == 0) {
      mainMenuScreen();
    }
    if (verboseOutput != 0) {
      Serial.println("Menu");
      Serial.println("State is :" + String(state));
    }
  } else if (number == 6) { // Back button
    //state = 0;
    if (state == 1 || state == 7 || state == 8) {
      loopScreen();
      settings_pointer = 0;
    } else if (state == 9 )  { //test menu
      settings_pointer = previousSettingsPointer;
      showSettings();
    } else if (state == 10 )  { // wifi menu
      settings_pointer = previousSettingsPointer;
      showSettings();
    } else if (state == 51 )  { // wifi setup screen
      settings_pointer = previousSettingsPointer;
      wifiSettingsScreen();
      wifiSetupCancel();
    } else if (state == 52 )  { // wifi setup confirm screen
      settings_pointer = previousSettingsPointer;
      wifiSettingsScreen();
    } else if (state == 101 )  { // wifi connection screen
      settings_pointer = previousSettingsPointer;
      wifiSettingsScreen();
    } else {
      if (state > 0) {
        settings_pointer = previousSettingsPointer;
        mainMenuScreen();
      }
    }
    if (verboseOutput != 0) {
      Serial.println("---------------------");
      Serial.println("Back button was pressed");
      Serial.println("State is :" + String(state));
      Serial.println("Settings pointer: " + String(settings_pointer));
      Serial.println("Previous settings pointer: " + String(previousSettingsPointer));
      Serial.println("---------------------");
    }
  } else if (verboseOutput != 0) {
    if (number != 0) {
      Serial.println("Button number " + String(number) + " was pressed");
    }
  }
  //}
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
