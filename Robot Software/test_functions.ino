void randomSensorValues(int iterations)
{
  for (int i = 0; i < iterations; i++)
  {
    int randomValue = random(337, 390);
    Serial.println(randomValue);
    delay(10);
  }
}

void lineFollowingValues()
{
  Serial.print("TOP LEFT: ");
  Serial.println(topLeftSensorVal());
  Serial.print("TOP RIGHT: ");
  Serial.println(topRightSensorVal());
  Serial.println();

  delay(1000);
}

void cornerValues()
{
  Serial.print("BOTTOM LEFT: ");
  Serial.println(bottomLeftSensorVal());
  Serial.print("BOTTOM RIGHT: ");
  Serial.println(bottomRightSensorVal());
  Serial.println();
}

void readSerial()
{
  while (Serial.available())
  {
    char c = Serial.read();
    Serial.println(c);
  }
}

void downFork()
{
  digitalWrite(7, LOW);
  digitalWrite(5, HIGH);
}

void upFork()
{
  digitalWrite(7, HIGH);
  digitalWrite(5, LOW);
}

void slowLeft()
{
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  analogWrite(10, 255);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  analogWrite(11, 125);
}

void slowRight()
{
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  analogWrite(10, 125);
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
  analogWrite(11, 255);
}

void speedUp()
{
  for (int i = 0; i < 255; i++)
  {
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    analogWrite(10, i);
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);
    analogWrite(11, i);

    delay(10);
  }
}

void slowDown()
{
  for (int i = 255; i > 0; i--)
  {
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    analogWrite(10, i);
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);
    analogWrite(11, i);

    delay(10);
  } 
}

void speedUpForklift()
{
  while (!topReached())
  {
    for (int i = 0; i < 255; i++)
    {
      digitalWrite(7, HIGH);
      digitalWrite(5, LOW);
      analogWrite(6, i);
      delay(10);
    }
  }

  while (!bottomReached())
  {
    for (int i = 255; i > 0; i--)
    {
      digitalWrite(7, LOW);
      digitalWrite(5, HIGH);
      analogWrite(6, i);
      delay(10);
    }
  }

  stopForklift();
}

void forwardFullSpeed() 
{
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
}

// Makes the robot turn left
void turnLeftFullSpeed() 
{
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
}
