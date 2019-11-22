

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
      if (ignoreUp[i] == false && menuMode[i] == false) event1(digitalButtonPins[i]);
      else ignoreUp[i] = false;
      btnUpTime[i] = millis();
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
    if (settings_pointer < numOfPointers) {
      settings_pointer++;
      UpdateSettingsPointer();
      if (verboseOutput != 0) {
        Serial.println("Down; Settings pointer:  " + String(settings_pointer));
      }
    }
  } else if (AXIS_X.wasAxisPressed() == 2) {
    if (settings_pointer > 0) {
      settings_pointer--;
      UpdateSettingsPointer();
      if (verboseOutput != 0) {
        Serial.println("Up; Settings pointer: " + String(settings_pointer));
      }
    }
  } else if (AXIS_Y.wasAxisPressed() == 1) {
    if (verboseOutput != 0) {
      Serial.println("Left");
    }
  } else if (AXIS_Y.wasAxisPressed() == 2) {
    if (verboseOutput != 0) {
      Serial.println("Right");
    }
  }
  //}
}


// Events to trigger by click and press+hold

void event1(int pin) {
  if (pin > 20  && pin < 40) {
    if (pin == 27) { // Select button
      //previousState = state;
      if (verboseOutput != 0) {
        Serial.println("Previous state is: " + String(previousState));
        Serial.println("State is: " + String(state));
        Serial.println("Settings pointer: " + String(settings_pointer));
        Serial.println("Previous settings pointer: " + String(previousSettingsPointer));
      }
      if (state == 1) {
        if (settings_pointer == 0) {
          showSelectProfile();
        } else if (settings_pointer == 1) {
          showChangeProfile();
        } else if  (settings_pointer == 2) {
          showAddProfile();
        } else if  (settings_pointer == 3) {
          showSettings();
        } else {
          showInfo();
        }
        //previousSettingsPointer = settings_pointer;
      } else if (state == 2) {
        if (settings_pointer == 0) {

        } else if (settings_pointer == 1) {

        } else if  (settings_pointer == 2) {

        } else if  (settings_pointer == 3) {

        } else {

        }
      } else if (state == 5) {

        //settings_pointer = 0; // clear pointer
        if (settings_pointer == 0) {
          buttons = !buttons;

          if (verboseOutput != 0) {
            Serial.println("Buttons value is: " + String(buttons));
          }
          setButtons(55);
          updatePreferences();
        } else if (settings_pointer == 1) {
          fan = !fan;

          if (verboseOutput != 0) {
            Serial.println("Fan value is: " + String(fan));
          }
          setFan(75);
          updatePreferences();
        } else if  (settings_pointer == 2) {
          horizontal = !horizontal;
          if (verboseOutput != 0) {
            Serial.println("Display value is: " + String(horizontal));
          }
          setDisplay(95);
          updatePreferences();
          previousSettingsPointer,settings_pointer = 0;
          startScreen();
          //        } else if  (settings_pointer == 3) {
          //
          //        } else {
          //
        }
        //previousSettingsPointer = settings_pointer; //store previous position in menu
      }
      if (verboseOutput != 0) {
        Serial.println("Select");
      }
    } else if (pin == 32) { //Menu button
      //state = 1;

      if (state == 0) {
        mainMenuScreen();
      }
      if (verboseOutput != 0) {
        Serial.println("Menu");
        Serial.println("State is :" + String(state));
      }
    } else if (pin == 33) { // Back button
      //state = 0;
      if (state == 1) {
        loopScreen();
        settings_pointer = 0;
      } else {
        settings_pointer = previousSettingsPointer;
        mainMenuScreen();
      }
      if (verboseOutput != 0) {
        Serial.println("Back");
        Serial.println("State is :" + String(state));
        Serial.println("Settings pointer: " + String(settings_pointer));
        Serial.println("Previous settings pointer: " + String(previousSettingsPointer));
      }
    } else if (verboseOutput != 0) {
      Serial.println("button 1 (" + String(pin) + ")");
    }
  }
  delay(50);
  //  if (pin == 32) {
  //    menuScreen();
  //  } else if (pin == 33) {
  //    loopScreen();
  //  }
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
