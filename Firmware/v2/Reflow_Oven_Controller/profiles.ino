
template <typename T> unsigned int convert_to_byte (const T& value, uint8_t output [sizeof(profile_t)], int multiplier) {
  const byte * p = (const byte*) &value;
  unsigned int i;
  for (i = 0; i < sizeof value; i++)
    output[multiplier*i] = (*p++);
  return i;
}  // end of convert_to_byte

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
  profileUsed = preferences.getInt("profileUsed", 0);
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
  int profileSize;
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
    else {
      Serial.print("Buffer: ");
      Serial.println(buffer);
    }
    // Save the extracted data into variable
    profile_t *profiles = (profile_t *) buffer;
    profileSize = schLen / sizeof(profile_t);
    // Load profiles from memory to array for program usage
    if (profileSize == 1) {
      paste_profile[num] = profiles[0];
      // Print of Title names loaded from Preferences
      Serial.println("Title from loaded profile: ");
      Serial.print((String)num + ". ");
      Serial.println(paste_profile[num].title);
      Serial.println();
      profileNum++;
    }
    else {
      Serial.println("Error during load of data in loadProfiles.");
    }
  }
  else {
    Serial.print("No data found in Preferences memory n");
    Serial.println(num);
  }
  preferences.end();
}

void saveProfiles(int num, profile_t profile) {
  sprintf(spaceName, "profile%0d", num);
  // Put all profiles into Preferences
  preferences.begin(spaceName);

  uint8_t content[sizeof(profile_t)];
  convert_to_byte(profile, content, 0);


  // Get the possible length of saved array
  size_t schLen = sizeof(profile_t);
  // Put all bytes into "profiles"
  preferences.putBytes(spaceName, content, schLen);
  // Test read the data back and test their correct number
  char buffer[schLen];
  preferences.getBytes(spaceName, buffer, schLen);
  if (schLen % sizeof(profile_t)) {
    log_e("Data is not correct size!");
    return;
  }
  // Save new profile also to paste_profile used in program
  paste_profile[num] = profile;

  profile_t *profiles = (profile_t *) buffer;
  // Check of Saved profiles
  Serial.println("Title from saved profile: ");
  Serial.print((String)num + ". ");
  Serial.println(profiles[0].title);
  Serial.println();
  preferences.end();
}

void compareProfiles(profile_t profile_new, profile_t profile_saved, int number) {
  if (profile_new.title[number] == profile_saved.title[number])
  {
    Serial.println("Profile " + String(number) + " match");
  }
  else
  {
    Serial.println("Profile " + String(number) + " do not match");
    saveProfiles(number, profile_new); //////////
  }
}
