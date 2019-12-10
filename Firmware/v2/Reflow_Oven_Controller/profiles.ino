const size_t capacity = 13 * JSON_ARRAY_SIZE(2) + JSON_ARRAY_SIZE(7) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(8) + 200;
DynamicJsonDocument doc(capacity);

//const char* json = "{\"title\":\"Lead 138\",\"alloy\":\"Sn42/Bi57.6/Ag0.4\",\"melting_point\":138,\"temp_range\":[30,165],\"time_range\":[0,390],\"reference\":\"http://www.chipquik.com/datasheets/TS391LT50.pdf\",\"stages\":{\"preheat\":[90,90],\"soak\":[180,130],\"reflow\":[210,138],\"cool\":[270,138]},\"profile\":[[0,30],[90,90],[180,130],[210,138],[240,165],[270,138],[390,50]]}";
//
//deserializeJson(doc, json);
//
//const char* title = doc["title"]; // "Lead 138"
//const char* alloy = doc["alloy"]; // "Sn42/Bi57.6/Ag0.4"
//int melting_point = doc["melting_point"]; // 138
//
//int temp_range_0 = doc["temp_range"][0]; // 30
//int temp_range_1 = doc["temp_range"][1]; // 165
//
//int time_range_0 = doc["time_range"][0]; // 0
//int time_range_1 = doc["time_range"][1]; // 390
//
//const char* reference = doc["reference"]; // "http://www.chipquik.com/datasheets/TS391LT50.pdf"
//
//JsonObject stages = doc["stages"];
//
//int stages_preheat_0 = stages["preheat"][0]; // 90
//int stages_preheat_1 = stages["preheat"][1]; // 90
//
//int stages_soak_0 = stages["soak"][0]; // 180
//int stages_soak_1 = stages["soak"][1]; // 130
//
//int stages_reflow_0 = stages["reflow"][0]; // 210
//int stages_reflow_1 = stages["reflow"][1]; // 138
//
//int stages_cool_0 = stages["cool"][0]; // 270
//int stages_cool_1 = stages["cool"][1]; // 138
//
//JsonArray profile = doc["profile"];
//
//int profile_0_0 = profile[0][0]; // 0
//int profile_0_1 = profile[0][1]; // 30
//
//int profile_1_0 = profile[1][0]; // 90
//int profile_1_1 = profile[1][1]; // 90
//
//int profile_2_0 = profile[2][0]; // 180
//int profile_2_1 = profile[2][1]; // 130
//
//int profile_3_0 = profile[3][0]; // 210
//int profile_3_1 = profile[3][1]; // 138
//
//int profile_4_0 = profile[4][0]; // 240
//int profile_4_1 = profile[4][1]; // 165
//
//int profile_5_0 = profile[5][0]; // 270
//int profile_5_1 = profile[5][1]; // 138
//
//int profile_6_0 = profile[6][0]; // 390
//int profile_6_1 = profile[6][1]; // 50
//
////  Serial.println(String(title));
////  Serial.println(String(alloy));
////  Serial.println(String(melting_point));
//}
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

void parseJSONProfile() {
  deserializeJson(doc, jsonProfileString);
  
  const char* title = doc["title"]; // "Lead 138"//
  const char* alloy = doc["alloy"]; // "Sn42/Bi57.6/Ag0.4"
  int melting_point = doc["melting_point"]; // 138


  JsonArray profile = doc["profile"];
  for(JsonVariant profiles : profile){
    Serial.println(profiles.as<int>());
//    Serial.println(profiles.value().as<char*>());
  }

  Serial.println(String(title));
  Serial.println(String(alloy));
  Serial.println(String(melting_point));
}
