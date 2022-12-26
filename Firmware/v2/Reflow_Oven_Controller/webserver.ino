//extern WebServer server;
//extern bool SD_present;
//String webpage = "";
//
//void append_page_header() {
//  webpage  = F("<!DOCTYPE html><html>");
//  webpage += F("<head>");
//  webpage += F("<title>");
//  webpage += F(projectName);
//  webpage += F("</title>"); // NOTE: 1em = 16px
//  webpage += F("<meta name='viewport' content='user-scalable=yes,initial-scale=1.0,width=device-width'>");
//  webpage += F("<style>");
//  webpage += F("body{max-width:65%;margin:0 auto;font-family:arial;font-size:105%;text-align:center;color:blue;background-color:#F7F2Fd;}");
//  webpage += F("ul{list-style-type:none;margin:0.1em;padding:0;border-radius:0.375em;overflow:hidden;background-color:#dcade6;font-size:1em;}");
//  webpage += F("li{float:left;border-radius:0.375em;border-right:0.06em solid #bbb;}last-child {border-right:none;font-size:85%}");
//  webpage += F("li a{display: block;border-radius:0.375em;padding:0.44em 0.44em;text-decoration:none;font-size:85%}");
//  webpage += F("li a:hover{background-color:#EAE3EA;border-radius:0.375em;font-size:85%}");
//  webpage += F("section {font-size:0.88em;}");
//  webpage += F("h1{color:white;border-radius:0.5em;font-size:1em;padding:0.2em 0.2em;background:#558ED5;}");
//  webpage += F("h2{color:orange;font-size:1.0em;}");
//  webpage += F("h3{color:red;font-size:0.8em;}");
//  webpage += F("table{font-family:arial,sans-serif;font-size:0.9em;border-collapse:collapse;width:85%;}");
//  webpage += F("th,td {border:0.06em solid #dddddd;text-align:left;padding:0.3em;border-bottom:0.06em solid #dddddd;}");
//  webpage += F("tr:nth-child(odd) {background-color:#eeeeee;}");
//  webpage += F(".rcorners_n {border-radius:0.5em;background:#558ED5;padding:0.3em 0.3em;width:20%;color:white;font-size:75%;}");
//  webpage += F(".rcorners_m {border-radius:0.5em;background:#558ED5;padding:0.3em 0.3em;width:50%;color:white;font-size:75%;}");
//  webpage += F(".rcorners_w {border-radius:0.5em;background:#558ED5;padding:0.3em 0.3em;width:70%;color:white;font-size:75%;}");
//  webpage += F(".column{float:left;width:50%;height:45%;}");
//  webpage += F(".row:after{content:'';display:table;clear:both;}");
//  webpage += F("*{box-sizing:border-box;}");
//  webpage += F("footer{background-color:#eedfff; text-align:center;padding:0.3em 0.3em;border-radius:0.375em;font-size:60%;}");
//  webpage += F("button{border-radius:0.5em;background:#558ED5;padding:0.3em 0.3em;width:20%;color:white;font-size:130%;}");
//  webpage += F(".buttons {border-radius:0.5em;background:#558ED5;padding:0.3em 0.3em;width:15%;color:white;font-size:80%;}");
//  webpage += F(".buttonsm{border-radius:0.5em;background:#558ED5;padding:0.3em 0.3em;width:9%; color:white;font-size:70%;}");
//  webpage += F(".buttonm {border-radius:0.5em;background:#558ED5;padding:0.3em 0.3em;width:15%;color:white;font-size:70%;}");
//  webpage += F(".buttonw {border-radius:0.5em;background:#558ED5;padding:0.3em 0.3em;width:40%;color:white;font-size:70%;}");
//  webpage += F("a{font-size:75%;}");
//  webpage += F("p{font-size:75%;}");
//  webpage += F("</style></head><body><h1>");
//  webpage += String(projectName) + " Webserver" +  "</h1>";
//}
////~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//void append_page_footer() { // Saves repeating many lines of code for HTML page footers
//  webpage += F("<ul>");
//  webpage += F("<li><a href='/'>Home</a></li>"); // Lower Menu bar command entries
////  webpage += F("<li><a href='/download'>Download</a></li>");
//  webpage += F("<li><a href='/upload'>Upload</a></li>");
//  webpage += F("</ul>");
//  webpage += F("</body></html>");
//}
//
//
//// All supporting functions from here...
////~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//void HomePage() {
//  SendHTML_Header();
//  webpage += F("<a href='/download'><button>Download</button></a>");
//  webpage += F("<a href='/upload'><button>Upload</button></a>");
//  //  webpage += F("<h3>Temp is: ");
//  //  webpage += String(inputInt);
//  //  webpage += F("</h3>");
//  append_page_footer();
//  SendHTML_Content();
//  SendHTML_Stop(); // Stop is needed because no content length was sent
//}
////~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//void File_Download() { // This gets called twice, the first pass selects the input, the second pass then processes the command line arguments
//  if (server.args() > 0 ) { // Arguments were received
//    if (useSPIFFS != 1) {
//      if (server.hasArg("download")) file_download(SD, server.arg(0));
//    } else {
//      if (server.hasArg("download")) file_download(SPIFFS, server.arg(0));
//    }
//  }
//  else SelectInput("Enter filename to download", "download", "download");
//}
////~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//void file_download(fs::FS &fs, String filename) {
//  File download = fs.open("/" + filename);
//  if (download) {
//    server.sendHeader("Content-Type", "text/text");
//    server.sendHeader("Content-Disposition", "attachment; filename=" + filename);
//    server.sendHeader("Connection", "close");
//    server.streamFile(download, "application/octet-stream");
//    download.close();
//  } else ReportFileNotPresent("download");
//}
////~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//void File_Upload() {
//  append_page_header();
//  webpage += F("<h3>Select File to Upload</h3>");
//  webpage += F("<FORM action='/fupload' method='post' enctype='multipart/form-data'>");
//  webpage += F("<input class='buttons' style='width:40%' type='file' name='fupload' id = 'fupload' value=''><br>");
//  webpage += F("<br><button class='buttons' style='width:10%' type='submit'>Upload File</button><br>");
//  webpage += F("<a href='/'>[Back]</a><br><br>");
//  append_page_footer();
//  server.send(200, "text/html", webpage);
//}
////~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//File UploadFile;
//void handleFileUpload() { // upload a new file to the Filing system
//  HTTPUpload& uploadfile = server.upload(); // See https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer/srcv
//  // For further information on 'status' structure, there are other reasons such as a failed transfer that could be used
//  if (uploadfile.status == UPLOAD_FILE_START)
//  {
//    String filename = uploadfile.filename;
//    if (!filename.startsWith("/")) filename = "/" + filename;
//    Serial.print("Upload File Name: "); Serial.println(filename);
//    if (useSPIFFS != 1) {
//      SD.remove(filename);                         // Remove a previous version, otherwise data is appended the file again
//      UploadFile = SD.open(filename, "w");  // Open the file for writing in SPIFFS (create it, if doesn't exist)
//    } else {
//      SPIFFS.remove(filename);                         // Remove a previous version, otherwise data is appended the file again
//      UploadFile = SPIFFS.open(filename, "w");  // Open the file for writing in SPIFFS (create it, if doesn't exist)
//    }
//    filename = String();
//  }
//  else if (uploadfile.status == UPLOAD_FILE_WRITE)
//  {
//    if (UploadFile) UploadFile.write(uploadfile.buf, uploadfile.currentSize); // Write the received bytes to the file
//  }
//  else if (uploadfile.status == UPLOAD_FILE_END)
//  {
//    if (UploadFile)         // If the file was successfully created
//    {
//      UploadFile.close();   // Close the file again
//      Serial.print("Upload Size: "); Serial.println(uploadfile.totalSize);
//      webpage = "";
//      append_page_header();
//      webpage += F("<h3>File was successfully uploaded</h3>");
//      webpage += F("<h2>Uploaded File Name: "); webpage += uploadfile.filename + "</h2>";
//      webpage += F("<h2>File Size: "); webpage += file_size(uploadfile.totalSize) + "</h2><br>";
//      append_page_footer();
//      server.send(200, "text/html", webpage);
//      scanForProfiles();
//    }
//    else
//    {
//      ReportCouldNotCreateFile("upload");
//    }
//  }
//}
////~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//void SendHTML_Header() {
//  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
//  server.sendHeader("Pragma", "no-cache");
//  server.sendHeader("Expires", "-1");
//  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
//  server.send(200, "text/html", ""); // Empty content inhibits Content-length header so we have to close the socket ourselves.
//  append_page_header();
//  server.sendContent(webpage);
//  webpage = "";
//}
////~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//void SendHTML_Content() {
//  server.sendContent(webpage);
//  webpage = "";
//}
////~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//void SendHTML_Stop() {
//  server.sendContent("");
//  server.client().stop(); // Stop is needed because no content length was sent
//}
////~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//void SelectInput(String heading1, String command, String arg_calling_name) {
//  SendHTML_Header();
//  webpage += F("<h3>"); webpage += heading1 + "</h3>";
//  webpage += F("<FORM action='/"); webpage += command + "' method='post'>"; // Must match the calling argument e.g. '/chart' calls '/chart' after selection but with arguments!
//  webpage += F("<input type='text' name='"); webpage += arg_calling_name; webpage += F("' value=''><br>");
//  webpage += F("<type='submit' name='"); webpage += arg_calling_name; webpage += F("' value=''><br>");
//  webpage += F("<a href='/'>[Back]</a>");
//  append_page_footer();
//  SendHTML_Content();
//  SendHTML_Stop();
//}
////~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//void ReportSDNotPresent() {
//  SendHTML_Header();
//  webpage += F("<h3>No SD Card present</h3>");
//  webpage += F("<a href='/'>[Back]</a><br><br>");
//  append_page_footer();
//  SendHTML_Content();
//  SendHTML_Stop();
//}
////~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//void ReportFileNotPresent(String target) {
//  SendHTML_Header();
//  webpage += F("<h3>File does not exist</h3>");
//  webpage += F("<a href='/"); webpage += target + "'>[Back]</a><br><br>";
//  append_page_footer();
//  SendHTML_Content();
//  SendHTML_Stop();
//}
////~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//void ReportCouldNotCreateFile(String target) {
//  SendHTML_Header();
//  webpage += F("<h3>Could Not Create Uploaded File (NOT inserted SD card or NOT \"Use SPIFFS:Yes\" in Settings?)</h3>");
//  webpage += F("<a href='/"); webpage += target + "'>[Back]</a><br><br>";
//  append_page_footer();
//  SendHTML_Content();
//  SendHTML_Stop();
//}
////~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//String file_size(int bytes) {
//  String fsize = "";
//  if (bytes < 1024)                 fsize = String(bytes) + " B";
//  else if (bytes < (1024 * 1024))      fsize = String(bytes / 1024.0, 3) + " KB";
//  else if (bytes < (1024 * 1024 * 1024)) fsize = String(bytes / 1024.0 / 1024.0, 3) + " MB";
//  else                              fsize = String(bytes / 1024.0 / 1024.0 / 1024.0, 3) + " GB";
//  return fsize;
//}
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>Captive Portal Demo</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <h3>Captive Portal Demo</h3>
  <br><br>
  <form action="/get">
    <br>
    SSID: <input type="text" name="ssid">
    <br>
    Password: <input type="text" name="password">
    <input type="submit" value="Submit">
  </form>
</body></html>)rawliteral";

class CaptiveRequestHandler : public AsyncWebHandler {
  public:
    CaptiveRequestHandler() {}
    virtual ~CaptiveRequestHandler() {}

    bool canHandle(AsyncWebServerRequest *request) {
      //request->addInterestingHeader("ANY");
      return true;
    }

    void handleRequest(AsyncWebServerRequest *request) {
      request->send_P(200, "text/html", index_html);
    }
};

void setupServer() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html);
    Serial.println("Client Connected");
  });

  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest * request) {
    String inputMessage;
    String inputParam;

    if (request->hasParam("ssid")) {
      inputMessage = request->getParam("ssid")->value();
      inputParam = "ssid";
      ssid = inputMessage;
      Serial.println(inputMessage);
      valid_ssid_received = true;
    }

    if (request->hasParam("password")) {
      inputMessage = request->getParam("password")->value();
      inputParam = "password";
      password = inputMessage;
      Serial.println(inputMessage);
      valid_password_received = true;
    }
    request->send(200, "text/html", "The values entered by you have been successfully sent to the device. It will now attempt WiFi connection");
  });
}


void WiFiSoftAPSetup()
{
  WiFi.mode(WIFI_AP);
  WiFi.softAP("esp-captive");
  Serial.print("AP IP address: "); Serial.println(WiFi.softAPIP());
}


void WiFiStationSetup(String rec_ssid, String rec_password)
{
  wifi_timeout = false;
  WiFi.mode(WIFI_STA);
  char ssid_arr[20];
  char password_arr[20];
  rec_ssid.toCharArray(ssid_arr, rec_ssid.length() + 1);
  rec_password.toCharArray(password_arr, rec_password.length() + 1);
  Serial.print("Received SSID: "); Serial.println(ssid_arr); Serial.print("And password: "); Serial.println(password_arr);
  WiFi.begin(ssid_arr, password_arr);

  uint32_t t1 = millis();
  while (WiFi.status() != WL_CONNECTED) {
    delay(2000);
    Serial.print(".");
    if (millis() - t1 > 50000) //50 seconds elapsed connecting to WiFi
    {
      Serial.println();
      Serial.println("Timeout connecting to WiFi. The SSID and Password seem incorrect.");
      valid_ssid_received = false;
      valid_password_received = false;
      is_setup_done = false;
      preferences.putBool("is_setup_done", is_setup_done);

      StartCaptivePortal();
      wifi_timeout = true;
      break;
    }
  }
  if (!wifi_timeout)
  {
    is_setup_done = true;
    Serial.println("");  Serial.print("WiFi connected to: "); Serial.println(rec_ssid);
    Serial.print("IP address: ");  Serial.println(WiFi.localIP());
    preferences.putBool("is_setup_done", is_setup_done);
    preferences.putString("rec_ssid", rec_ssid);
    preferences.putString("rec_password", rec_password);
  }
}

void StartCaptivePortal() {
  Serial.println("Setting up AP Mode");
  WiFiSoftAPSetup();
  Serial.println("Setting up Async WebServer");
  setupServer();
  Serial.println("Starting DNS Server");
  dnsServer.start(53, "*", WiFi.softAPIP());
  server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);//only when requested from AP
  server.begin();
  dnsServer.processNextRequest();
}
