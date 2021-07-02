# RoboticsYear13
Repo containing my robotics work from year 13  
__NOTE: This is all my original work from year 13; no modifications have been made whatsoever since 2019.__

# Project Objective
The objective of this project was to construct an autonomous line-following "warehouse" robot that can navigate using sensors, pick up a payload, and drop it off at an endpoint. I ended up implementing manual control via bluetooth for fun which allows the user to switch from autopilot to manual control seamlessly :) 

# Project Structure

## Robot Software
All my robot code is stored here. I used the Arduino IDE to write the robot software (hence the `.ino` extension), and each file in the folder handles a certain aspect of the robot's functionality.

## Control Software
This folder consists of one project (RobotController) which is a tiny piece of software I wrote to manually control my robot's operations. It's written in C# and uses the WPF framework for UI stuff. The program interfaces with the robot via bluetooth by allowing the user to select a virtual serial port assigned to the bluetooth device; hence achieving a level of abstraction which allows me to disregard the actual connection medium (e.g USB, bluetooth...)

## Utility Software
There are two main C# projects under the `Utility Software` folder - namely `AverageLatency` and `SensorUtility`. I also wrote a small helper library `SerialProvider` for serial port access which is used across the two other projects.

### Average Latency
This is a lightweight program that I wrote to, well, test out the average bluetooth latency between my robot and my laptop for testing purposes.

### SensorUtility
The `SensorUtility` program is a small program to take in sensor readings from the four sensors on my robot and format the data nicely in an `.csv` file along with other statistics such as averages and standard deviation.