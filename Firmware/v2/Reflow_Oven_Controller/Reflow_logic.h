#include <PID_v1.h>

extern Adafruit_MAX31856 max31856;
extern Button AXIS_X;
extern Button AXIS_Y;

extern bool isFault;
extern String activeStatus;
extern void loopScreen();
extern int oldTemp;
extern byte state;
extern bool disableMenu;
extern bool profileIsOn;

extern profile_t paste_profile[numOfProfiles];
extern int profileUsed;

/*******************************************************************************
  Title: Reflow Oven Controller
  Version: 1.20
  Date: 26-11-2012
  Company: Rocket Scream Electronics
  Author: Lim Phang Moh
  Website: www.rocketscream.com

  Brief
  =====
  This is an example firmware for our Arduino compatible reflow oven controller.
  The reflow curve used in this firmware is meant for lead-free profile
  (it's even easier for leaded process!). You'll need to use the MAX31855
  library for Arduino if you are having a shield of v1.60 & above which can be
  downloaded from our GitHub repository. Please check our wiki
  (www.rocketscream.com/wiki) for more information on using this piece of code
  together with the reflow oven controller shield.

  Temperature (Degree Celcius)                 Magic Happens Here!
  245-|                                               x  x
      |                                            x        x
      |                                         x              x
      |                                      x                    x
  200-|                                   x                          x
      |                              x    |                          |   x
      |                         x         |                          |       x
      |                    x              |                          |
  150-|               x                   |                          |
      |             x |                   |                          |
      |           x   |                   |                          |
      |         x     |                   |                          |
      |       x       |                   |                          |
      |     x         |                   |                          |
      |   x           |                   |                          |
  30 -| x             |                   |                          |
      |<  60 - 90 s  >|<    90 - 120 s   >|<       90 - 120 s       >|
      | Preheat Stage |   Soaking Stage   |       Reflow Stage       | Cool
   0  |_ _ _ _ _ _ _ _|_ _ _ _ _ _ _ _ _ _|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
                                                                 Time (Seconds)

  This firmware owed very much on the works of other talented individuals as
  follows:
  ==========================================
  Brett Beauregard (www.brettbeauregard.com)
  ==========================================
  Author of Arduino PID library. On top of providing industry standard PID
  implementation, he gave a lot of help in making this reflow oven controller
  possible using his awesome library.

  ==========================================
  Limor Fried of Adafruit (www.adafruit.com)
  ==========================================
  Author of Arduino MAX6675 library. Adafruit has been the source of tonnes of
  tutorials, examples, and libraries for everyone to learn.

  Disclaimer
  ==========
  Dealing with high voltage is a very dangerous act! Please make sure you know
  what you are dealing with and have proper knowledge before hand. Your use of
  any information or materials on this reflow oven controller is entirely at
  your own risk, for which we shall not be liable.

  Licences
  ========
  This reflow oven controller hardware and firmware are released under the
  Creative Commons Share Alike v3.0 license
  http://creativecommons.org/licenses/by-sa/3.0/
  You are free to take this piece of code, use it and modify it.
  All we ask is attribution including the supporting libraries used in this
  firmware.

  Required Libraries
  ==================
  - Arduino PID Library:
    >> https://github.com/br3ttb/Arduino-PID-Library
  - MAX31855 Library (for board v1.60 & above):
    >> https://github.com/rocketscream/MAX31855
  - MAX6675 Library (for board v1.50 & below):
    >> https://github.com/adafruit/MAX6675-library

  Revision  Description
  ========  ===========
  1.20      Adds supports for v1.60 (and above) of Reflow Oven Controller
            Shield:
            - Uses MAX31855KASA+ chip and pin reassign (allowing A4 & A5 (I2C)
              to be used for user application).
            - Uses analog based switch (allowing D2 & D3 to be used for user
              application).
            Adds waiting state when temperature too hot to start reflow process.
            Corrected thermocouple disconnect error interpretation (MAX6675).
  1.10      Arduino IDE 1.0 compatible.
  1.00      Initial public release.
*******************************************************************************/
// Comment either one the following #define to select your board revision
// Newer board version starts from v1.60 using MAX31855KASA+ chip

// ***** TYPE DEFINITIONS *****
typedef enum REFLOW_STATE
{
  REFLOW_STATE_IDLE,
  REFLOW_STATE_PREHEAT,
  REFLOW_STATE_SOAK,
  REFLOW_STATE_REFLOW,
  REFLOW_STATE_COOL,
  REFLOW_STATE_COMPLETE,
  REFLOW_STATE_TOO_HOT,
  REFLOW_STATE_ERROR
} reflowState_t;

typedef enum REFLOW_STATUS
{
  REFLOW_STATUS_OFF,
  REFLOW_STATUS_ON
} reflowStatus_t;

typedef  enum SWITCH
{
  SWITCH_NONE,
  SWITCH_1,
  SWITCH_2
} switch_t;

typedef enum DEBOUNCE_STATE
{
  DEBOUNCE_STATE_IDLE,
  DEBOUNCE_STATE_CHECK,
  DEBOUNCE_STATE_RELEASE
} debounceState_t;

// ***** CONSTANTS *****
#define TEMPERATURE_ROOM 50
#define TEMPERATURE_SOAK_MIN 150
#define TEMPERATURE_SOAK_MAX 185
#define TEMPERATURE_REFLOW_MAX 220
#define TEMPERATURE_COOL_MIN 100
#define SENSOR_SAMPLING_TIME 1000
#define SOAK_TEMPERATURE_STEP 5
#define SOAK_MICRO_PERIOD 9000
#define DEBOUNCE_PERIOD_MIN 50

// ***** PID PARAMETERS *****
// ***** PRE-HEAT STAGE *****
#define PID_KP_PREHEAT 100
#define PID_KI_PREHEAT 0.025
#define PID_KD_PREHEAT 20
// ***** SOAKING STAGE *****
#define PID_KP_SOAK 300
#define PID_KI_SOAK 0.05
#define PID_KD_SOAK 250
// ***** REFLOW STAGE *****
#define PID_KP_REFLOW 300
#define PID_KI_REFLOW 0.05
#define PID_KD_REFLOW 350
#define PID_SAMPLE_TIME 1000

// ***** PID CONTROL VARIABLES *****
double setpoint;
double input;
double output;
double kp = PID_KP_PREHEAT;
double ki = PID_KI_PREHEAT;
double kd = PID_KD_PREHEAT;
int windowSize;
int inputInt;
unsigned long windowStartTime;
unsigned long nextCheck;
unsigned long nextRead;
unsigned long timerSoak;
unsigned long buzzerPeriod;
// Reflow oven controller state machine state variable
reflowState_t reflowState;
// Reflow oven controller status
reflowStatus_t reflowStatus;
// Switch debounce state machine state variable
debounceState_t debounceState;
// Switch debounce timer
long lastDebounceTime;
// Switch press status
switch_t switchStatus;
// Seconds timer
int timerSeconds;

// Specify PID control interface & it must be here, after all declaration
PID reflowOvenPID(&input, &output, &setpoint, kp, ki, kd, DIRECT);

void reflow_main() {
  // Current time
  unsigned long now;
  //loopScreen();

  // Time to read thermocouple?
  if (millis() > nextRead) {

    // Read thermocouple next sampling period
    nextRead += SENSOR_SAMPLING_TIME;
    // Read current temperature

    input = max31856.readThermocoupleTemperature();
    // Check and print any faults
    uint8_t fault = max31856.readFault();
    if (fault) {
      if (fault & MAX31856_FAULT_CJRANGE) //Serial.println("Cold Junction Range Fault");
        if (fault & MAX31856_FAULT_TCRANGE) //Serial.println("Thermocouple Range Fault");
          if (fault & MAX31856_FAULT_CJHIGH)  //Serial.println("Cold Junction High Fault");
            if (fault & MAX31856_FAULT_CJLOW)   //Serial.println("Cold Junction Low Fault");
              if (fault & MAX31856_FAULT_TCHIGH)  //Serial.println("Thermocouple High Fault");
                if (fault & MAX31856_FAULT_TCLOW)   //Serial.println("Thermocouple Low Fault");
                  if (fault & MAX31856_FAULT_OVUV)    //Serial.println("Over/Under Voltage Fault");
                    if (fault & MAX31856_FAULT_OPEN)    //Serial.println("Thermocouple Open Fault");
                      isFault = 1;
    }
    inputInt = input / 1;

    if (oldTemp != inputInt) {
      if (state == 0) {
        loopScreen();
      }
#ifdef Serial
      if ((input > 0) && (input <= 500)) {
        Serial.print("Float temp: " + String(input));
        Serial.print(" ; ");
        Serial.println("Integer temp: " + String(inputInt));
      }
#endif
    }
    // If thermocouple problem detected
    if (input == MAX31856_FAULT_CJRANGE) {
      // Illegal operation
      reflowState = REFLOW_STATE_ERROR;
      reflowStatus = REFLOW_STATUS_OFF;
    }
    oldTemp = inputInt;
  }

  if (millis() > nextCheck)
  {
    // Check input in the next seconds
    nextCheck += 1000;
    // If reflow process is on going
    if (reflowStatus == REFLOW_STATUS_ON)
    {
      // Toggle red LED as system heart beat
      digitalWrite(ledPin, !(digitalRead(ledPin)));
      // Increase seconds timer for reflow curve analysis
      timerSeconds++;
      // Send temperature and time stamp to serial
      Serial.print(timerSeconds);
      Serial.print(" ");
      Serial.print(setpoint);
      Serial.print(" ");
      Serial.print(input);
      Serial.print(" ");
      Serial.println(output);
    }
    else
    {
      // Turn off red LED
      digitalWrite(ledPin, LOW);
    }
    // If currently in error state
    if (reflowState == REFLOW_STATE_ERROR)
    {
      // No thermocouple wire connected
      Serial.println("TC Error!");
    }
  }

  // Reflow oven controller state machine
  switch (reflowState)
  {
    case REFLOW_STATE_IDLE:
      activeStatus = "Idle";
      // If oven temperature is still above room temperature
      if (input >= TEMPERATURE_ROOM)
      {
        reflowState = REFLOW_STATE_TOO_HOT;
        Serial.println("Status: Too hot to start");
      }
      else
      {
        // If switch is pressed to start reflow process
        if (profileIsOn != 0)
        {
          // Send header for CSV file
          Serial.println("Time Setpoint Input Output");
          // Intialize seconds timer for serial debug information
          timerSeconds = 0;
          // Initialize PID control window starting time
          windowStartTime = millis();
          // Ramp up to minimum soaking temperature
          setpoint = paste_profile[profileUsed].stages_preheat_1;
          // Tell the PID to range between 0 and the full window size
          reflowOvenPID.SetOutputLimits(0, windowSize);
          reflowOvenPID.SetSampleTime(PID_SAMPLE_TIME);
          // Turn the PID on
          reflowOvenPID.SetMode(AUTOMATIC);
          // Proceed to preheat stage
          reflowState = REFLOW_STATE_PREHEAT;
        }
      }
      break;

    case REFLOW_STATE_PREHEAT:
      activeStatus = "Preheat";
      reflowStatus = REFLOW_STATUS_ON;
      // If minimum soak temperature is achieve
      if (input >= paste_profile[profileUsed].stages_preheat_1)
      {
        // Chop soaking period into smaller sub-period
        timerSoak = millis() + SOAK_MICRO_PERIOD;
        // Set less agressive PID parameters for soaking ramp
        reflowOvenPID.SetTunings(PID_KP_SOAK, PID_KI_SOAK, PID_KD_SOAK);
        // Ramp up to first section of soaking temperature
        setpoint = paste_profile[profileUsed].stages_preheat_1 + SOAK_TEMPERATURE_STEP;
        // Proceed to soaking state
        reflowState = REFLOW_STATE_SOAK;
      }
      break;

    case REFLOW_STATE_SOAK:
      activeStatus = "Soak";
      // If micro soak temperature is achieved
      if (millis() > timerSoak)
      {
        timerSoak = millis() + SOAK_MICRO_PERIOD;
        // Increment micro setpoint
        setpoint += SOAK_TEMPERATURE_STEP;
        if (setpoint > paste_profile[profileUsed].stages_soak_1)
        {
          // Set agressive PID parameters for reflow ramp
          reflowOvenPID.SetTunings(PID_KP_REFLOW, PID_KI_REFLOW, PID_KD_REFLOW);
          // Ramp up to first section of soaking temperature
          setpoint = paste_profile[profileUsed].stages_reflow_1;
          // Proceed to reflowing state
          reflowState = REFLOW_STATE_REFLOW;
        }
      }
      break;

    case REFLOW_STATE_REFLOW:
      activeStatus = "Reflow";
      // We need to avoid hovering at peak temperature for too long
      // Crude method that works like a charm and safe for the components
      if (input >= (paste_profile[profileUsed].stages_reflow_1 - 5))
      {
        // Set PID parameters for cooling ramp
        reflowOvenPID.SetTunings(PID_KP_REFLOW, PID_KI_REFLOW, PID_KD_REFLOW);
        // Ramp down to minimum cooling temperature
        setpoint = TEMPERATURE_COOL_MIN;
        // Proceed to cooling state
        reflowState = REFLOW_STATE_COOL;
      }
      break;

    case REFLOW_STATE_COOL:
      activeStatus = "Cool";
      // If minimum cool temperature is achieve
      if (input <= TEMPERATURE_COOL_MIN)
      {
        // Retrieve current time for buzzer usage
        buzzerPeriod = millis() + 1000;
        // Turn on buzzer and green LED to indicate completion
        digitalWrite(buzzerPin, HIGH);
        // Turn off reflow process
        reflowStatus = REFLOW_STATUS_OFF;
        // Proceed to reflow Completion state
        reflowState = REFLOW_STATE_COMPLETE;
      }
      break;

    case REFLOW_STATE_COMPLETE:
      activeStatus = "Complete";
      if (millis() > buzzerPeriod)
      {
        // Turn off buzzer and green LED
        digitalWrite(buzzerPin, LOW);
        // Reflow process ended
        reflowState = REFLOW_STATE_IDLE;
        profileIsOn = 0;
        disableMenu = 0;
        Serial.println("Profile is OFF");
      }
      break;

    case REFLOW_STATE_TOO_HOT:
      // If oven temperature drops below room temperature
      if (input < TEMPERATURE_ROOM)
      {
        // Ready to reflow
        reflowState = REFLOW_STATE_IDLE;
      }
      break;

    case REFLOW_STATE_ERROR:
      // If thermocouple problem is still present

      if (input == MAX31856_FAULT_CJRANGE)// || (input == FAULT_SHORT_GND) ||
        //          (input == FAULT_SHORT_VCC))
      {
        // Wait until thermocouple wire is connected
        reflowState = REFLOW_STATE_ERROR;
      }
      else
      {
        // Clear to perform reflow process
        reflowState = REFLOW_STATE_IDLE;
      }
      break;
  }

  // If switch 1 is pressed
  if (switchStatus == SWITCH_1)
  {
    // If currently reflow process is on going
    if (reflowStatus == REFLOW_STATUS_ON)
    {
      // Button press is for cancelling
      // Turn off reflow process
      reflowStatus = REFLOW_STATUS_OFF;
      // Reinitialize state machine
      reflowState = REFLOW_STATE_IDLE;
    }
  }

  // Simple switch debounce state machine (for switch #1 (both analog & digital
  // switch supported))
  switch (debounceState)  
  {
    case DEBOUNCE_STATE_IDLE:
      // No valid switch press
      switchStatus = SWITCH_NONE;
      // If switch #1 is pressed
      if (input == -1) // (AXIS_X.readAxis() == 1)
      {
        // Intialize debounce counter
        lastDebounceTime = millis();
        Serial.println("Switch pressed");
        // Proceed to check validity of button press
        debounceState = DEBOUNCE_STATE_CHECK;
      }
      break;

    case DEBOUNCE_STATE_CHECK:
      if (input == -1) // (AXIS_X.readAxis() == 1)
      {
        // If minimum debounce period is completed
        if ((millis() - lastDebounceTime) > DEBOUNCE_PERIOD_MIN)
        {
          // Proceed to wait for button release
          debounceState = DEBOUNCE_STATE_RELEASE;
        }
      }
      // False trigger
      else
      {
        // Reinitialize button debounce state machine
        debounceState = DEBOUNCE_STATE_IDLE;
      }
      break;

    case DEBOUNCE_STATE_RELEASE:
      if (input == -1) // (AXIS_X.readAxis() > 0)
      {
        // Valid switch 1 press
        switchStatus = SWITCH_1;
        // Reinitialize button debounce state machine
        debounceState = DEBOUNCE_STATE_IDLE;
      }
      break;
  }

  // PID computation and SSR control
  if (reflowStatus == REFLOW_STATUS_ON)
  {
    now = millis();

    reflowOvenPID.Compute();

    if ((now - windowStartTime) > windowSize)
    {
      // Time to shift the Relay Window
      windowStartTime += windowSize;
    }
    if (output > (now - windowStartTime)) digitalWrite(ssrPin, HIGH);
    else digitalWrite(ssrPin, LOW);
  }
  // Reflow oven process is off, ensure oven is off
  else
  {
    digitalWrite(ssrPin, LOW);
  }
}
