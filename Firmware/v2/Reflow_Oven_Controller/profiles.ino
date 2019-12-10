//const size_t capacity = 13 * JSON_ARRAY_SIZE(2) + JSON_ARRAY_SIZE(7) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(8) + 310;
DynamicJsonDocument doc(2048);

//char* json1 = "{\"title\":\"Lead 138\",\"alloy\":\"Sn42/Bi57.6/Ag0.4\",\"melting_point\":138,\"temp_range\":[30,165],\"time_range\":[0,390],\"reference\":\"http://www.chipquik.com/datasheets/TS391LT50.pdf\",\"stages\":{\"preheat\":[90,90],\"soak\":[180,130],\"reflow\":[210,138],\"cool\":[270,138]},\"profile\":[[0,30],[90,90],[180,130],[210,138],[240,165],[270,138],[390,50]]}";

StaticJsonDocument<1024> newDoc;

JsonArray array = newDoc.to<JsonArray>();

void parseJsonProfile() {
  Serial.println();
  Serial.println("Starting to parse " + jsonName + " file.");
  // Open file for reading
  File file = SD.open(jsonName);

  // Allocate a temporary JsonDocument
  // Don't forget to change the capacity to match your requirements.
  // Use arduinojson.org/v6/assistant to compute the capacity.
  StaticJsonDocument<1024> doc;

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

  array.add(title);
  array.add(alloy);
  array.add(melting_point);
  array.add(temp_range_0);
  array.add(temp_range_1);
  array.add(time_range_0);
  array.add(time_range_1);
  array.add(reference);
  array.add(time_range_0);
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
}

//
//// Prints the content of a file to the Serial
//void printFile(const char *filename) {
//  // Open file for reading
//  File file = SD.open(filename);
//  if (!file) {
//    Serial.println(F("Failed to read file"));
//    return;
//  }
//
//  // Extract each characters by one by one
//  while (file.available()) {
//    Serial.print((char)file.read());
//  }
//  Serial.println();
//
//  // Close the file (File's destructor doesn't close the file)
//  file.close();
//}
