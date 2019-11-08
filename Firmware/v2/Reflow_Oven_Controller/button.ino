byte digitalButton (int pin) {

  for (int i = 0; i < numDigButtons; i++) {
    // Read the state of the button

    buttonVal[i] = digitalRead(digitalButtonPins[i]);

    //delay(10);

    // Test for button pressed and store the down time
    if (buttonVal[i] == LOW && buttonLast[i] == HIGH && (millis() - btnUpTime[i]) > debounce)
    {
      btnDnTime[i] = millis();
    }

    // Test for button release and store the up time
    if (buttonVal[i] == HIGH && buttonLast[i] == LOW && (millis() - btnDnTime[i]) > debounce)
    {
      if (ignoreUp[i] == false && menuMode[i] == false) event1(digitalButtonPins[i]);
      else ignoreUp[i] = false;
      btnUpTime[i] = millis();
    }

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


void analogButton(int pin) {
  // read the state of the switch into a local variable:
  int reading = analogRead(pin);
  //Serial.println(analogRead(pin));
  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    analogLastDebounceTime = millis();
  }

  if ((millis() - analogLastDebounceTime) > debounce) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;
      if (pin == 34) {
        if (reading > 1500 && reading < 2000) {
          Serial.println("Left");
        } else {
          Serial.println("Right");
        }
      }
    }
  }

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;

}
// Events to trigger by click and press+hold

void event1(int pin)
{
  if (pin > 20  && pin < 40) {
    if (pin == 27) {
      Serial.println("Select");
    } else if (pin == 32) {
      Serial.println("Menu");
    } else if (pin == 33) {
      Serial.println("Back");
    } else
      Serial.println("button 1 (" + String(pin) + ")");
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
