void liftForkliftUp()
{
  digitalWrite(7, HIGH);
  digitalWrite(5, LOW);
  analogWrite(6, 255);
}

void liftForkliftDown()
{
  digitalWrite(7, LOW);
  digitalWrite(5, HIGH);
  analogWrite(6, 200);
}

void stopForklift()
{
  digitalWrite(7, LOW);
  digitalWrite(5, LOW);
}

bool topReached()
{
  if (digitalRead(TOP_LIMIT_SWITCH) == 1)
  {
    return true;
  } else
  {
    return false;
  }
}


bool bottomReached()
{
  if (digitalRead(BOTTOM_LIMIT_SWITCH) == 1)
  {
    return true;
  } else
  {
    return false;
  }
}

void reachSurfaceLevel()
{
  while (!topReached())
  {
    liftForkliftUp();
  }

  liftForkliftDown();
  delay(310);
  stopForklift();
}

void pickupObject()
{
  reachSurfaceLevel();
  forward();
  delay(400);
  freeze();
  while (!topReached())
  {
    liftForkliftUp();
  }

  stopForklift();
  backward();
  delay(2000);
}

void dropoffObject()
{
  reachSurfaceLevel();
  backward();
  delay(750);
  freeze();
}
