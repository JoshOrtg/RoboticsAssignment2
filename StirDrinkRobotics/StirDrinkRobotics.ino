#include <Servo.h>

//creates servo objects for each of the servos in the robot arm.
Servo rotation, height, reach, claw;

//Creates variables to be manipulated in the main code.
int clawAngle;
int heightAngle;
int reachAngle;
int rotationAngle;
bool isStirring = true;

void setup() 
{
  Serial.begin(9600);

  //Attaches the servo objects to the pins on the Arduino Uno board. 
  //The servos use pseudo analogue output in the form of pulse width modulation.
  rotation.attach(11);
  height.attach(10);
  reach.attach(9);
  claw.attach(6);

  //Moves the arm to its start position when the arm is powered up.
  StartPosition();
}

void loop() 
{
  if (Serial.available()) 
  {
    char inChar = Serial.read(); 
    int rotationPos;
    //switch statement uses key input to select a function
    switch (inChar) 
    {
      //Runs stir function
      case 'g':
        Serial.println("Start");
        LowerArm();
        delay(300);
        
        //Cycles through the loop 10 times to stir the drink, the resets the position/lifts the spoons form the drink.
        for (int i = 0; i < 10; i++) 
        {

          //Moves the rotation servo from left to right to stir the drink.
          for (rotationPos = 70; rotationPos <= 110; rotationPos += 1)
          { 
            rotation.write(rotationPos);

            delay(15); 
          }
          for (rotationPos = 110; rotationPos >= 70; rotationPos -= 1)
          { 
            rotation.write(rotationPos); 

            delay(15);
          }

          Serial.println(i);

          //breaks out of the loop once the loop has cycled 10 times.
          if(i == 9)
          {
            StartPosition();                   
            break;
          }
        }
        break;  
      
      //Resets the position
      case 's':
        Serial.println("Stop!");
        StartPosition();

      default:
        break;
    }
  }

  delay(200);
}

//function which stores the start positions of each servo and moves the servo to those positions.
void StartPosition()
{
  clawAngle = 90;
  heightAngle = 140;
  reachAngle = 120;
  rotationAngle = 90;

  rotation.write(rotationAngle);
  height.write(heightAngle);
  reach.write(reachAngle);
  claw.write(clawAngle);
}

//function to lower the arm, placing the spoon in the cup/mug.
void LowerArm()
{
  int heightPos = 90;
  height.write(heightPos);
}
