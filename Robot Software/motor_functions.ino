// Makes the robot go forwards
void forward() 
{
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10, 150);
  
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
  digitalWrite(11, 150);
}

// Makes the robot go backwards
void backward() 
{
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  analogWrite(10, 220);
  
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  analogWrite(11, 220);
}

// Makes the robot turn left
void turnLeft() 
{
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  analogWrite(10, 220);
  
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  analogWrite(11, 150);
}

void turnLeftBackward()
{
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
}

void turnRightBackward()
{
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
}

// Makes the robot turn right
void turnRight() 
{
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  analogWrite(10, 255);
  
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
  analogWrite(11, 255);
}

// Makes the robot come to a standstill
void freeze()
{
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
}
