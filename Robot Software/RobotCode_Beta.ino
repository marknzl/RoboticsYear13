#include <ArduinoJson.h>

///MOTORS////////////////
// LEFT MOTOR: 8, 9
// RIGHT MOTOR: 12, 13
// PULLEY: 7, 5
/////////////////////////
///SENSORS///////////////
// LEFT TOP: A5
// LEFT BOTTOM: A4
// RIGHT TOP: A2
// RIGHT BOTTOM: A3
/////////////////////////
///LIMIT SWITCH//////////
// PIN: 2
// PIN: 4
/////////////////////////

// Sensor analog pins
const int TOP_LEFT_SENSOR = A2; // Top left
const int BOTTOM_LEFT_SENSOR = A3; // Bottom left
const int TOP_RIGHT_SENSOR = A0; // Top right
const int BOTTOM_RIGHT_SENSOR = A1; // Bottom right

// Calibration thresholds
double topLeftThreshold = 0;
double topRightThreshold = 0;
double bottomLeftThreshold = 0;
double bottomRightThreshold = 0;

// Limit switch pins
const int TOP_LIMIT_SWITCH = 4;
const int BOTTOM_LIMIT_SWITCH = 2;

// State variables
bool manualControl = false;
bool startedReadings = false;
bool reachedEndpoint = false;
bool hasTurned = false;
bool returning = false;

void setup()
{
  Serial.begin(9600);

  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(TOP_LIMIT_SWITCH, INPUT_PULLUP);
  pinMode(BOTTOM_LIMIT_SWITCH, INPUT_PULLUP);
  //getSensorData(100);
  //calibrateForklift();
  //reachSurfaceLevel();
  //lineFollowingCalibration();
  //cornerDetectionCalibration();
  calibrateSensors();
}

void loop()
{
  while (manualControl)
  {
    while (Serial.available())
    {
      char c = Serial.read();
      parseMessage(c);
    }
  }

  // If manual control is toggled off, the autopilot will take over robot control
  char c = Serial.read();
  if (c == 'Q')
  {
    manualControl = true;
    freeze();
    Serial.println("Autopilot disabled! Turning on manual control");
  }

  followLine();

  if (!hasTurned)
    checkForCorner();

  if (!returning)
  {
    checkForEndpoint();
  } else
  {
    checkForOrigin();
  }

  //sensorReadings();
}
