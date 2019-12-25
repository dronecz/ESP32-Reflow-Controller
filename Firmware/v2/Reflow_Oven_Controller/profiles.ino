
void parseJsonProfile(String someName) {

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

  const char* title = doc["title"]; // "Lead 183"
  const char* alloy = doc["alloy"]; // "Sn63/Pb37"
  int melting_point = doc["melting_point"]; // 183

  int temp_range_0 = doc["temp_range"][0]; // 30
  int temp_range_1 = doc["temp_range"][1]; // 235

  int time_range_0 = doc["time_range"][0]; // 0
  int time_range_1 = doc["time_range"][1]; // 340

  const char* reference = doc["reference"]; // "https://www.chipquik.com/datasheets/TS391AX50.pdf"

  JsonObject stages = doc["stages"];

  int stages_preheat_0 = stages["preheat"][0]; // 30
  int stages_preheat_1 = stages["preheat"][1]; // 100

  int stages_soak_0 = stages["soak"][0]; // 120
  int stages_soak_1 = stages["soak"][1]; // 150

  int stages_reflow_0 = stages["reflow"][0]; // 150
  int stages_reflow_1 = stages["reflow"][1]; // 183

  int stages_cool_0 = stages["cool"][0]; // 240
  int stages_cool_1 = stages["cool"][1]; // 183


  file.close();

  Serial.println("Profile data: " + String(title) + "," + String(alloy) + "," + String(melting_point) + "," + String(temp_range_0) + "," + String(temp_range_1) + "," + String(time_range_0) + "," + String(time_range_1) + "," + String(reference) + "," + String(stages_preheat_0) + "," + String(stages_preheat_1) + "," + String(stages_soak_0) + "," + String(stages_soak_1) + "," + String(stages_reflow_0) + "," + String(stages_reflow_1) + "," + String(stages_cool_0) + "," + String(stages_cool_1));

  array.add(title);
  array.add(alloy);
  array.add(melting_point);
  array.add(temp_range_0);
  array.add(temp_range_1);
  array.add(time_range_0);
  array.add(time_range_1);
  array.add(reference);
  array.add(stages_preheat_0);
  array.add(stages_preheat_1);
  array.add(stages_soak_0);
  array.add(stages_soak_1);
  array.add(stages_reflow_0);
  array.add(stages_reflow_1);
  array.add(stages_cool_0);
  array.add(stages_cool_1);

  // serialize the array and send the result to Serial
  serializeJson(newDoc, Serial);
  Serial.println();
  size_t len = measureJson(newDoc); //get length of the array
  Serial.println("Length of the array is: " + String(len));
//  copyArray(array, profile, len);
  //memset(newDoc, 0, sizeof(newDoc));
    Serial.println();
}
