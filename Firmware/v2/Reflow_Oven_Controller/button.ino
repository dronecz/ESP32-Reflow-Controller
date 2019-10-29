byte button (int pin) {

  int aRead[4];
  for (int i = 0; i < numButtons; i++) {
    // Read the state of the button
    /*
      if (buttonPin[3,4]) {
      aRead[i] = analogRead(buttonPin[i]);
      if (aRead[i] > 1 && aRead[i] < 5000) {
        //Serial.println((buttonPin[i]) + (aRead[i]));
      }
      //  buttonVal[i] = analogRead(buttonPin[i]);
      if ((aRead[0, 2]) == 0) {
      buttonVal[i] = LOW;
      } else {
      buttonVal[i] = HIGH;
      }
      } else {
      buttonVal[0, 2] = digitalRead(buttonPin[i]);
      //Serial.println(String(buttonVal[i]) + "(" + String(buttonPin[i]) + ")");
      }
    */
    //Serial.println(String(buttonVal[i]) + "(" + String(buttonPin[i]) + ")");
    aRead[i] = analogRead(buttonPin[i]);
    if (buttonPin[i] == 27) { // select
      if (aRead[i] > 350 && aRead[i] < 400) {
        buttonVal[i] = HIGH;
      } else {
        buttonVal[i] = LOW;
      }
    } else if (buttonPin[i] == 32) { //menu
      if (aRead[i] > 500 && aRead[i] < 600) {
        buttonVal[i] = HIGH;
      } else {
        buttonVal[i] = LOW;
      }
    } else if (buttonPin[i] == 33) { //back
      if (aRead[i] > 200 && aRead[i] < 300) {
        buttonVal[i] = HIGH;
      } else {
        buttonVal[i] = LOW;
      }
    } else if (buttonPin[i] == 34) { //up
      if (aRead[i] > 4000) {
        buttonVal[i] = HIGH;
      } else {
        buttonVal[i] = LOW;
      }
    } else if (buttonPin[i] == 34) { //down
      if (aRead[i] > 1850 && aRead[i] < 1950) {
        buttonVal[i] = HIGH;
      } else {
        buttonVal[i] = LOW;
      }
    } else if (buttonPin[i] == 35) { //left
      if (aRead[i] > 1850 && aRead[i] < 1950) {
        buttonVal[i] = HIGH;
      } else {
        buttonVal[i] = LOW;
      }
    } else if (buttonPin[i] == 35) { //right
      if (aRead[i] > 4000) {
        buttonVal[i] = HIGH;
      } else {
        buttonVal[i] = LOW;
      }
    }
  
  delay(10);

  // Test for button pressed and store the down time
  if (buttonVal[i] == LOW && buttonLast[i] == HIGH && (millis() - btnUpTime[i]) > debounce)
  {
    btnDnTime[i] = millis();
  }

  // Test for button release and store the up time
  if (buttonVal[i] == HIGH && buttonLast[i] == LOW && (millis() - btnDnTime[i]) > debounce)
  {
    if (ignoreUp[i] == false && menuMode[i] == false) event1(buttonPin[i]);
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
    if (ignoreUp[i] == false && menuMode[i] == true) event2(buttonPin[i]);
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

// Events to trigger by click and press+hold

void event1(int pin)
{
  if (pin > 20  && pin < 40) {
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
