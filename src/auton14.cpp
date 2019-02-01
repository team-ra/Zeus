#include "main.h"
#include "robot.h"
void auton12()
{
  resetEncoders();
  pros::delay(250);//waits to allow sensors to stablize
  //info_printf(1, "auton1");
  motorSetup();//sets up the motors
  //drives forward 1 square to prepare for shooting the middle flag
  intakeOn(false);  //turns intake on
  while (driveForward(encoderInchesToCounts(42), 50, true) != 1);//drive to cap 40
  pros::delay(250);//wait for ball to enter mechanism
  while(driveBackward(encoderInchesToCounts(40), 75,true) != 1);//reverse from cap
  while(turnRight(800,50,true) != 1);

  while (driveForward(encoderInchesToCounts(42), 75, true) != 1);//12
  intakeOff();//turn off intake

//info_printf(1, "before shoot");
  resetEncoders();
  pros::delay(100);
  while (driveBackward(encoderInchesToCounts(24), 75, true) != 1);
  while (shootBall() == 0){//waits for ball to be shot
    pros::delay(10);
  }

  while(driveBackward(encoderInchesToCounts(30), 75,true) != 1);//reverse from cap
  while (shootBall() == 0){//waits for ball to be shot
    pros::delay(10);
  }
  while (driveForward(encoderInchesToCounts(16), 50, true) != 1);
}
