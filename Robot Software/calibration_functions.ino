void lineFollowingCalibration()
{
  double vals[50];
  double total = 0;

  // CALIBRATION FOR TOP LEFT SENSOR
  for (int i = 0; i < 10; i++)
  {
    double reading = topLeftSensorVal();
    vals[i] = reading;
    total = total + reading;
    
    Serial.print("[ (LEFT SIDE) Loop iteration] ");
    Serial.println(i + 1);
    Serial.print("Sensor value ");
    Serial.println(vals[i]);
    Serial.println("");
    
    delay(10);
  }
   
  topLeftThreshold = average(total, 10);

  total = 0;

  // CALIBRATION FOR TOP RIGHT SENSOR
  for (int i = 0; i < 10; i++)
  {
    vals[i] = topRightSensorVal();
    total = total + vals[i];
    
    Serial.print("[ (RIGHT SIDE) Loop iteration] ");
    Serial.println(i + 1);
    Serial.print("Sensor value ");
    Serial.println(vals[i]);
    Serial.println("");
    
    delay(10);
  }

  topRightThreshold = average(total, 10);
}

void cornerDetectionCalibration()
{
  int vals[50];
  double total = 0;

  for (int i = 0; i < 10; i++)
  {
    vals[i] = analogRead(BOTTOM_LEFT_SENSOR);
    total = total + vals[i];
    
    Serial.print("[ (LEFT SIDE) Loop iteration] ");
    Serial.println(i + 1);
    Serial.print("Sensor value ");
    Serial.println(vals[i]);
    Serial.println("");
    
    delay(10);
  }
   
  bottomLeftThreshold = average(total, 10);

  total = 0;

  for (int i = 0; i < 10; i++)
  {
    vals[i] = analogRead(BOTTOM_RIGHT_SENSOR);
    total = total + vals[i];
    
    Serial.print("[ (RIGHT SIDE) Loop iteration] ");
    Serial.println(i + 1);
    Serial.print("Sensor value ");
    Serial.println(vals[i]);
    Serial.println("");
    
    delay(10);
  }

  bottomRightThreshold = average(total, 10);

  // Signals end of calibration so that the user
  // has time to position the robot on the track properly

  forward();
  delay(750);
  freeze();
  delay(3000);
}

void calibrateSensors()
{
  unsigned long initial = millis();
  lineFollowingCalibration();
  cornerDetectionCalibration();
  unsigned long final = millis();

  Serial.print("Top left threshold: ");
  Serial.println(topLeftThreshold);

  Serial.print("Top right threshold: ");
  Serial.println(topRightThreshold);

  Serial.print("Bottom left threshold: ");
  Serial.println(bottomLeftThreshold);

  Serial.print("Bottom right threshold: ");
  Serial.println(bottomRightThreshold);

  unsigned long delta = final - initial;
  Serial.print("Calibration took ");
  Serial.print(delta / 1000);
  Serial.print(" seconds");
}

void calibrateForklift()
{
  unsigned long initial = millis();
  while (!bottomReached())
  {
    liftForkliftDown();
  }

  while (!topReached())
  {
    liftForkliftUp();
  }

  stopForklift();
  unsigned long finalT = millis();
  unsigned long delta = (finalT - initial) / 1000; // Convert to seconds from milliseconds

  Serial.print("Calibration time: ");
  Serial.println(delta);
}
