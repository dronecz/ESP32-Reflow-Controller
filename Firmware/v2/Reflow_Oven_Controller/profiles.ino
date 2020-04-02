
void parseJsonProfile(String someName, int num, profile_t* profile) {

  StaticJsonDocument<500> newDoc;

  JsonArray array = newDoc.to<JsonArray>();

  Serial.println();
  Serial.println("Starting to parse " + someName + " file.");
  // Open file for reading
  File file = SD.open(someName);

  // Allocate a temporary JsonDocument
  // Don't forget to change the capacity to match your requirements.
  // Use arduinojson.org/v6/assistant to compute the capacity.
  StaticJsonDocument<1280> doc;

  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, file);

  // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    return;
  }

  strcpy(profile[num].title, doc["title"]);             // "Lead 183"
  strcpy(profile[num].alloy, doc["alloy"]);             // "Sn63/Pb37"
  profile[num].melting_point    = doc["melting_point"]; // 183

  profile[num].temp_range_0     = doc["temp_range"][0]; // 30
  profile[num].temp_range_1     = doc["temp_range"][1]; // 235

  profile[num].time_range_0     = doc["time_range"][0]; // 0
  profile[num].time_range_1     = doc["time_range"][1]; // 340

  strcpy(profile[num].reference, doc["reference"]);     // "https://www.chipquik.com/datasheets/TS391AX50.pdf"

  JsonObject stages = doc["stages"];

  profile[num].stages_preheat_0 = stages["preheat"][0]; // 30
  profile[num].stages_preheat_1 = stages["preheat"][1]; // 100

  profile[num].stages_soak_0    = stages["soak"][0];    // 120
  profile[num].stages_soak_1    = stages["soak"][1];    // 150

  profile[num].stages_reflow_0  = stages["reflow"][0];  // 150
  profile[num].stages_reflow_1  = stages["reflow"][1];  // 183

  profile[num].stages_cool_0    = stages["cool"][0];    // 240
  profile[num].stages_cool_1    = stages["cool"][1];    // 183

  file.close();

  Serial.println("Profile data: "
                 + String(profile[num].title) + ","
                 + String(profile[num].alloy) + ","
                 + String(profile[num].melting_point) + ","
                 + String(profile[num].temp_range_0) + ","
                 + String(profile[num].temp_range_1) + ","
                 + String(profile[num].time_range_0) + ","
                 + String(profile[num].time_range_1) + ","
                 + String(profile[num].reference) + ","
                 + String(profile[num].stages_preheat_0) + ","
                 + String(profile[num].stages_preheat_1) + ","
                 + String(profile[num].stages_soak_0) + ","
                 + String(profile[num].stages_soak_1) + ","
                 + String(profile[num].stages_reflow_0) + ","
                 + String(profile[num].stages_reflow_1) + ","
                 + String(profile[num].stages_cool_0) + ","
                 + String(profile[num].stages_cool_1));

  array.add(profile[num].title);
  array.add(profile[num].alloy);
  array.add(profile[num].melting_point);
  array.add(profile[num].temp_range_0);
  array.add(profile[num].temp_range_1);
  array.add(profile[num].time_range_0);
  array.add(profile[num].time_range_1);
  array.add(profile[num].reference);
  array.add(profile[num].stages_preheat_0);
  array.add(profile[num].stages_preheat_1);
  array.add(profile[num].stages_soak_0);
  array.add(profile[num].stages_soak_1);
  array.add(profile[num].stages_reflow_0);
  array.add(profile[num].stages_reflow_1);
  array.add(profile[num].stages_cool_0);
  array.add(profile[num].stages_cool_1);

  // serialize the array and send the result to Serial
  serializeJson(newDoc, Serial);
  Serial.println();
  size_t len = measureJson(newDoc); //get length of the array
  Serial.println("Length of the array is: " + String(len));
  //  copyArray(array, profile, len);
  //memset(newDoc, 0, sizeof(newDoc));
  Serial.println();
}

void saveSelectedProfile(int profile) {
  preferences.begin("store");
  preferences.putInt("profileUsed", profile);
  preferences.end();
  Serial.println("Saved profile # " + String(profile));
}

//void compareProfiles(profile_t _profile, profile_t profile_, int number) {
//  int check ;
//
//  check = memcmp(_profile, profile_, sizeof(_profile));
//
//  if (check == 0)
//  {
//    Serial.print("Profile match" + String(number));
//  }
//  else
//  {
//    Serial.print("Profile do not match" + String(number));
//  }
//}

void loadProfiles(int num) {
  sprintf(spaceName, "profile%d", num);
  // Extract "profiles" from memory
  preferences.begin(spaceName);
  // Extract the size of saved array
  size_t schLen = preferences.getBytes(spaceName, NULL, NULL);
  // Get array to buffer and check the size
  char buffer[schLen];
  preferences.getBytes(spaceName, buffer, schLen);
  // Check, that Preferences are not empty
  if (schLen > 0) {
    if (schLen % sizeof(profile_t)) {
      log_e("Data is not correct size!");
      return;
    }
    // Save the extracted data into variable
    profile_t *profiles = (profile_t *) buffer;
    profileNum = schLen / sizeof(profile_t);
    // Load profiles from memory to array for program usage
    for (int i = 0; i < profileNum; i++) {
      paste_profile[i] = profiles[i];
    }
    // Print of Title names loaded from Preferences
    Serial.println("Titles from Preferences: ");
    for (int i = 0; i < profileNum; i++) {
      Serial.print((String)i + ". ");
      Serial.println(paste_profile[i].title);
    }
    Serial.println();
  }
  else {
    Serial.println("No data found in Preferences memory.");
  }
  preferences.end();
}

void saveProfiles(int num, profile_t* profile) {
  sprintf(spaceName, "profile%d", num);
  // Put all profiles into Preferences
  preferences.begin(spaceName);
  // Get the possible length of saved array
  size_t schLen = sizeof(profile_t);
  // Put all bytes into "profiles"
  preferences.putBytes(spaceName, profile, schLen);
  // Test read the data back and test their correct number
  char buffer[schLen];
  preferences.getBytes(spaceName, buffer, schLen);
  if (schLen % sizeof(profile_t)) {
    log_e("Data is not correct size!");
    return;
  }
  // Check of Saved profiles
  Serial.print("Saved profile title: ");
  //  for (int i = 0; i < profileNum; i++) {
  Serial.println(profile->title);
  //    Serial.print(", ");
  //  }
  Serial.println();
  preferences.end();
}

void compareProfiles(profile_t _profile, profile_t profile_, int number) {
  if (_profile.title[number] == profile_.title[number])
  {
    Serial.println("Profile " + String(number) + " match");
  }
  else
  {
    Serial.println("Profile " + String(number) + " do not match");
    //saveProfiles(profileNum, profile_(number));
  }
}
