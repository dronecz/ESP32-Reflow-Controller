void webserverFunc() {

  // The logical name http://reflowserver.local will also access the device if you have 'Bonjour' running or your system supports multicast dns
  if (!MDNS.begin("reflowserver")) {          // Set your preferred server name, if you use "myserver" the address would be http://myserver.local/
    Serial.println(F("Error setting up MDNS responder!"));
    ESP.restart();
  }
  /** webserver start**/

  // Route for root / web page
  asyncserver.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", "text/html");
  });

  asyncserver.on("/src/jquery.min.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/src/jquery.min.js", "text/javascript");
  });

  asyncserver.on("/src/bootstrap.bundle.min.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/src/bootstrap.bundle.min.js", "text/javascript");
  });


  asyncserver.on("/src/bootstrap.min.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/src/bootstrap.min.css", "text/css");
  });

  asyncserver.on("/src/simple-sidebar.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/src/simple-sidebar.css", "text/css");
  });

  asyncserver.on("/temperature", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", webTemp().c_str());
  });

  asyncserver.on("/showchart", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", profileInt().c_str());
  });

  asyncserver.on("/profileNames", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", profileNames.c_str());
  });

  asyncserver.on("/getProfile", HTTP_GET, [](AsyncWebServerRequest * request) {
    String inputId;
    // GET input1 value on <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
    if (request->hasParam("id")) {
      inputId = request->getParam("id")->value();
    }
    else {
      inputId = "No message sent";
    }
    int id = inputId.toInt();
    if (id != -1) {
      request->send_P(200, "text/plain", getProfile(id).c_str());
    } else {
      Serial.println("Requested profile ID is -1 (\"Select profile\"), nothing to send.");
    }
  });

  asyncserver.on("/usedProfile", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", usedProfileName.c_str());
  });

  asyncserver.on("/getSettings", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", settingsValues.c_str());
  });

  asyncserver.on("/setSettings", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", setSettingsValue.c_str());
  });

  asyncserver.on("/serialMess", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", serialMessages.c_str());
  });

  // Send a GET request to <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
  asyncserver.on("/update", HTTP_GET, [] (AsyncWebServerRequest * request) {
    // GET input1 value on <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
    String tempString;
    if (request->hasParam(PARAM_INPUT_1) && request->hasParam(PARAM_INPUT_2)) {
      inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
      tempString = request->getParam(PARAM_INPUT_2)->value();
      inputMessage2 = tempString.toInt();
      changeValues(inputMessage1, inputMessage2, 0);
    }
    else {
      inputMessage1 = "No message sent";
    }
    Serial.print(inputMessage1);
    Serial.print(" - Set to: ");
    Serial.println(String(inputMessage2));
    request->send(200, "text/plain", "OK");
  });

  // Handle Web Server Events
  events.onConnect([](AsyncEventSourceClient * client) {
    if (client->lastId()) {
      Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
    }
    // send event with message "hello!", id current millis
    // and set reconnect delay to 1 second
    client->send("hello!", NULL, millis(), 10000);
    //    client->send(profileNames, NULL, NULL, NULL);
  });

  asyncserver.addHandler(&events);
  // Start server
  asyncserver.begin();
  /** webserver end**/

  Serial.println("HTTP server started");
}