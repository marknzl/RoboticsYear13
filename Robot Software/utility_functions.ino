// Used for testing bluetooth latency
int calculateAverageLatency(int iterations)
{
  Serial.println("Starting latency test");
  
  unsigned long pingValues[iterations]; // Stores all round-trip values
  unsigned long averagePing = 0;

  for (int i = 0; i < iterations; i++)
  {
    unsigned long initialPing = millis();
    Serial.print("[Iteration ");
    Serial.print(i + 1);
    Serial.print ("] ");
    Serial.println("Ping!"); // Sends ping message

    while (true)
    {
      if (Serial.available())
      {
        char chars = Serial.read();
        if (chars == 'P') // Checks if message contains the correct reply ("P")
        {
          unsigned long currentMillis = millis();
          unsigned long roundTrip = currentMillis - initialPing; // Calculates round-trip time by subtracting current ping from initial ping time value
          pingValues[i] = roundTrip; // Stores the round-trip time in the array
          averagePing = averagePing + pingValues[i];
          break;
        }
      }
    }
  }
  
  return (averagePing = averagePing / iterations); // Calculates average ping
}

void motorTest()
{
  forward();
  delay(1500);

  backward();
  delay(1500);

  turnLeft();
  delay(1500);

  turnRight();
  delay(1500);
}

int bottomLeftSensorVal()
{
  return analogRead(BOTTOM_LEFT_SENSOR);
}

int topLeftSensorVal()
{
  return analogRead(TOP_LEFT_SENSOR);
}

int topRightSensorVal()
{
  return analogRead(TOP_RIGHT_SENSOR);
}

int bottomRightSensorVal()
{
  return analogRead(BOTTOM_RIGHT_SENSOR);
}

double average(double total, int iterations)
{
  return total / iterations;
}

void sensorReadings()
{
  Serial.print("[BOTTOM LEFT] ");
  Serial.println(bottomLeftSensorVal());
  Serial.print("[TOP LEFT] ");
  Serial.println(topLeftSensorVal());

  Serial.print("[BOTTOM RIGHT] ");
  Serial.println(bottomRightSensorVal());
  Serial.print("[TOP RIGHT] ");
  Serial.println(topRightSensorVal());
  Serial.println("");

  delay(1000);
}

int topLimitSwitchReading()
{
  return digitalRead(TOP_LIMIT_SWITCH);
}

int bottomLimitSwitchReading()
{
  return digitalRead(BOTTOM_LIMIT_SWITCH);
}

void getSensorData(int iterations)
{
  if (!startedReadings)
  {
    Serial.println("Starting sensor readings");
    startedReadings = true;
  }

  for (int i = 0; i < iterations; i++)
  {
    DynamicJsonDocument jDoc(80);
    
    jDoc["sensorPosition"] = "Top Left";
    jDoc["value"] = topLeftSensorVal();
    jDoc["millis"] = millis();
    serializeJson(jDoc, Serial);
    Serial.println();

    jDoc["sensorPosition"] = "Top Right";
    jDoc["value"] = topRightSensorVal();
    jDoc["millis"] = millis();
    serializeJson(jDoc, Serial);
    Serial.println();

    jDoc["sensorPosition"] = "Bottom Left";
    jDoc["value"] = bottomLeftSensorVal();
    jDoc["millis"] = millis();
    serializeJson(jDoc, Serial);
    Serial.println();

    jDoc["sensorPosition"] = "Bottom Right";
    jDoc["value"] = bottomRightSensorVal();
    jDoc["millis"] = millis();
    serializeJson(jDoc, Serial);
    Serial.println();
  }

  Serial.println("Ending sensor readings");
}

void topLimitSwitchCheck()
{
  if (topReached())
  {
    Serial.println("TOP LIMIT SWITCH PRESSED");
  } else
  {
    Serial.println("TOP LIMIT SWITCH RELEASED");
  }
}

void bottomLimitSwitchCheck()
{
  if (bottomReached())
  {
    Serial.println("BOTTOM LIMIT SWITCH PRESSED");
  } else
  {
    Serial.println("BOTTOM LIMIT SWITCH RELEASED");
  }
}
