
void parseJsonProfile(String someName, int num) {

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

  strcpy(paste_profile[num].title, doc["title"]);             // "Lead 183"
  strcpy(paste_profile[num].alloy, doc["alloy"]);             // "Sn63/Pb37"
  paste_profile[num].melting_point    = doc["melting_point"]; // 183

  paste_profile[num].temp_range_0     = doc["temp_range"][0]; // 30
  paste_profile[num].temp_range_1     = doc["temp_range"][1]; // 235

  paste_profile[num].time_range_0     = doc["time_range"][0]; // 0
  paste_profile[num].time_range_1     = doc["time_range"][1]; // 340

  strcpy(paste_profile[num].reference, doc["reference"]);     // "https://www.chipquik.com/datasheets/TS391AX50.pdf"

  JsonObject stages = doc["stages"];

  paste_profile[num].stages_preheat_0 = stages["preheat"][0]; // 30
  paste_profile[num].stages_preheat_1 = stages["preheat"][1]; // 100

  paste_profile[num].stages_soak_0    = stages["soak"][0];    // 120
  paste_profile[num].stages_soak_1    = stages["soak"][1];    // 150

  paste_profile[num].stages_reflow_0  = stages["reflow"][0];  // 150
  paste_profile[num].stages_reflow_1  = stages["reflow"][1];  // 183

  paste_profile[num].stages_cool_0    = stages["cool"][0];    // 240
  paste_profile[num].stages_cool_1    = stages["cool"][1];    // 183

  file.close();

  Serial.println("Profile data: "
    + String(paste_profile[num].title) + ","
    + String(paste_profile[num].alloy) + ","
    + String(paste_profile[num].melting_point) + ","
    + String(paste_profile[num].temp_range_0) + ","
    + String(paste_profile[num].temp_range_1) + ","
    + String(paste_profile[num].time_range_0) + ","
    + String(paste_profile[num].time_range_1) + ","
    + String(paste_profile[num].reference) + ","
    + String(paste_profile[num].stages_preheat_0) + ","
    + String(paste_profile[num].stages_preheat_1) + ","
    + String(paste_profile[num].stages_soak_0) + ","
    + String(paste_profile[num].stages_soak_1) + ","
    + String(paste_profile[num].stages_reflow_0) + ","
    + String(paste_profile[num].stages_reflow_1) + ","
    + String(paste_profile[num].stages_cool_0) + ","
    + String(paste_profile[num].stages_cool_1));

  array.add(paste_profile[num].title);
  array.add(paste_profile[num].alloy);
  array.add(paste_profile[num].melting_point);
  array.add(paste_profile[num].temp_range_0);
  array.add(paste_profile[num].temp_range_1);
  array.add(paste_profile[num].time_range_0);
  array.add(paste_profile[num].time_range_1);
  array.add(paste_profile[num].reference);
  array.add(paste_profile[num].stages_preheat_0);
  array.add(paste_profile[num].stages_preheat_1);
  array.add(paste_profile[num].stages_soak_0);
  array.add(paste_profile[num].stages_soak_1);
  array.add(paste_profile[num].stages_reflow_0);
  array.add(paste_profile[num].stages_reflow_1);
  array.add(paste_profile[num].stages_cool_0);
  array.add(paste_profile[num].stages_cool_1);

  // serialize the array and send the result to Serial
  serializeJson(newDoc, Serial);
  Serial.println();
  size_t len = measureJson(newDoc); //get length of the array
  Serial.println("Length of the array is: " + String(len));
//  copyArray(array, profile, len);
  //memset(newDoc, 0, sizeof(newDoc));
    Serial.println();
}
