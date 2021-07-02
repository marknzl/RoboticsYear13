// Normal line following for going forward
void followLine()
{
  int topLeftVal = topLeftSensorVal();
  int topRightVal = topRightSensorVal();
  int bottomLeftVal = bottomLeftSensorVal();
  int bottomRightVal = bottomRightSensorVal();

//  if (topLeftVal <= (topLeftThreshold - 35) && topRightVal <= (topRightThreshold - 35))
//  {
//    forward();
//  } else if (topLeftVal <= (topLeftThreshold - 35) && !(topRightVal <= (topRightThreshold - 35)))
//  {
//    turnLeft();
//  } else if (!(topLeftVal <= (topLeftThreshold - 35) && topRightVal <= (topRightThreshold - 35)))
//  {
//    turnRight();
//  } else
//  {
//    freeze();
//  }

  if (!(topRightVal <= topRightThreshold) && topLeftVal <= topLeftThreshold)
  {
    turnLeft();
    Serial.println("Re-adjusting left");
  } else if (!(topLeftVal <= topLeftThreshold) && topRightVal <= topRightThreshold)
  {
    turnRight();
    Serial.println("Re-adjusting right");
  } else
  {
    forward();
  }
}

// Line following for going backwards after picking up object
void followLineBackwards()
{
  int topLeftVal = topLeftSensorVal();
  int topRightVal = topRightSensorVal();
  int bottomLeftVal = bottomLeftSensorVal();
  int bottomRightVal = bottomRightSensorVal();

  if (!(topRightVal <= topRightThreshold) && topLeftVal <= topLeftThreshold)
  {
    turnLeftBackward();
    Serial.println("Re-adjusting left");
  } else if (!(topLeftVal <= topLeftThreshold) && topRightVal <= topRightThreshold)
  {
    turnRightBackward();
    Serial.println("Re-adjusting right");
  } else
  {
    backward();
  }
}

void checkForCorner()
{ 
  int bottomLeftVal = bottomLeftSensorVal();
  int bottomRightVal = bottomRightSensorVal();

  if (bottomLeftVal <= 710)
  {
    Serial.println("LEFT CORNER DETECTED");

    forward();
    delay(500);
    turnLeft();
    delay(130);
    
    while (topLeftSensorVal() >= (topLeftThreshold - 35) && topRightSensorVal() >= (topRightThreshold - 35))
    {
      turnLeft();
    }

    hasTurned = true;
  } else if (bottomRightVal <= 710)
  {
    Serial.println("RIGHT CORNER DETECTED");

    forward();
    delay(500);
    turnRight();
    delay(130);
    
    while (topRightSensorVal() >= (topRightThreshold - 35) && topLeftSensorVal() >= (topLeftThreshold - 35))
    {
      turnRight();
    }

    hasTurned = true;
  }
  else
  {
    //Serial.println("NO CORNER");
  }
}

void checkForEndpoint()
{
  int bottomLeftVal = bottomLeftSensorVal();
  int bottomRightVal = bottomRightSensorVal();
  
  if (bottomLeftVal < 775 && bottomRightVal < 775)
  {
    freeze();
    reachedEndpoint = true;

    delay(3000);
    pickupObject();

    backward();
    delay(1000);

    while (true)
    {
      bottomLeftVal = bottomLeftSensorVal();

      if (bottomLeftVal < 820)
      {
        break;
      } else
      {
        backward(); 
      }
    }

    returning = true;
    reachedEndpoint = false;
    //hasTurned = false;
  }
}

void checkForOrigin()
{
  int bottomLeftVal = bottomLeftSensorVal();
  int bottomRightVal = bottomRightSensorVal();

  if (bottomLeftVal <= 800 || bottomRightVal <= 800)
  {
    Serial.println("Origin detected, stopping robot");
    freeze();

    while (!bottomReached())
    {
      liftForkliftDown();
    }

    stopForklift();
    
    delay(5000);
  }
}
