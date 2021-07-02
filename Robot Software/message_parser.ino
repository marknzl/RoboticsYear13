void parseMessage(char c)
{
  if (c == 'F')
  {
    Serial.print("Message received: ");
    Serial.println("Moving forward");
    forward();
  } else if (c == 'S')
  {
    Serial.print("Message received: ");
    Serial.println("Stopping");
    freeze();
  } else if (c == 'L')
  {
    Serial.print("Message received: ");
    Serial.println("Turning left");
    turnLeft();
  } else if (c == 'R')
  {
    Serial.print("Message received: ");
    Serial.println("Turning right");
    turnRight();
  } else if (c == 'B')
  {
    Serial.print("Message received: ");
    Serial.println("Moving backward");
    backward();
  } else if (c == 'T')
  {
    Serial.println("Message receieved, going up");
    if (digitalRead(TOP_LIMIT_SWITCH) == HIGH)
    {
      Serial.println("ERROR: Forklift already too high!"); 
    } else
    {
      Serial.println("Moving up");
      liftForkliftUp();
      delay(100);
      stopForklift();
    }
  } else if (c == 'V')
  {
    if (bottomReached())
    {
      Serial.println("ERROR: Forklift already too low!");
    } else
    {
      Serial.println("Moving down");
      liftForkliftDown();
      delay(100);
      stopForklift();
    }
  } else if (c == 'W')
  {
    Serial.println("Manual control disabled! Turning on autopilot");
    manualControl = false;
  } else if (c == 'P')
  {
    pickupObject();
  } else if (c == 'D')
  {
    dropoffObject();
  } else if (c == 'C')
  {
    calibrateForklift();
  } else if (c == 'U')
  {
    reachSurfaceLevel();
  }
}
