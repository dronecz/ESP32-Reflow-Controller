# ESP32 Reflow Controller   <a href="https://www.tindie.com/stores/dronecz/esp32-reflow-controller/?ref=offsite_badges&utm_source=sellers_dronecz83&utm_medium=badges&utm_campaign=badge_small"><img src="https://d2ss6ovg47m0r5.cloudfront.net/badges/tindie-smalls.png" alt="I sell on Tindie" width="200" height="55"></a>

You can read more about my project [here](https://hackaday.io/project/162946-esp32-reflow-oven) at Hackaday.io . :slightly_smiling_face:

This repository contain firmware and 3D files for ESP32 reflow controller. 

All version of controller include:

- ESP32 module
- 2.8" TFT LCD (ILI9341)
- MAX31856 IC for measuring temperature
- SD card slot
- buzzer
- USB to UART converter
- USB connector
- 5 buttons (Left, Right, Up, Down, Select)
- status LED 

### There are these revision of the board:

- **rev. A**

First version of the board. Fully working, except buzzer. 

- **rev. B**

Second version of the board. Reworked buzzer and changed for SMD version.

- **rev. C**

This board include 2 more buttons (Menu & Back button), fan connetor, Reset button and USB-C connector.

***

### There are 2 version of firmware for this board:

- **V1**

Basic functionality. One working profile which can be start/stoped.
**Not developed anymore.**

- **V2** (**recommended**)

You will need these libraries to compile FW from source code: 

 - Adafruit_ILI9341 (v. 1.5.1 in Library Manager) 
 - Adafruit_MAX31856 (v. 1.0.3 in Library Manager)
 - Adafruit_GFX (v. 1.7.2 in Library Manager)
 - ArduinoJson (v. 6.13.0 in Library Manager)
 - PID (v. 1.2.0 in Library Manager)
 - WiFiManager (https://github.com/tzapu/WiFiManager (development branch))
 

#### This firmware include following:

- [x] OTA update.
- [x] Vertical/Horizontal mode.
- [x] WiFiManager - you can setup your WiFi network for OTA updates. When not setup, it will start in AP mode and create network with SSID **ReflowOvenAP**. Setup server can be access at IP address: **192.168.4.1**, after connecting to this AP.  

Planned features:

- [ ] Reflow profiles (via JSON file)
- [ ] Web server for remote change of the settings 

This firmware include Menu, which can be open by pressing **Menu** button (**Left** button on rev. **A&B**). Here you can change items in **Settings**.

*** 

You can find STL files and Fusion 360 files for Front cover and for separate case (HW folder).  
									 
If you want to look at Front cover in 3D (web browser) you can use this link: <a href="https://a360.co/2S8YHzj" target="_blank">https://a360.co/2S8YHzj</a>

Front panel asssembly (rev A&B): <a href="https://a360.co/2S37lPS" target="_blank">https://a360.co/2S37lPS</a>

Firmware is based on Rocket Scream Electronics firmware for [Reflow Oven Shield](https://www.rocketscream.com/blog/2012/11/28/updated-back-in-stock-reflow-oven-shield-controller/)

Some parts of the V2 firmware are inspired by parts of <a href="https://github.com/UnexpectedMaker/ReflowMaster" target="_blank">Reflow Master</a> firmware by @UnexpectedMaker
