#include "main.h"
#include "robot.h"
void auton12()
{
  resetEncoders();
  pros::delay(250);//waits to allow sensors to stablize
  //info_printf(1, "auton1");
  motorSetup();//sets up the motors
  //drives forward 1 square to prepare for shooting the middle flag
  driveForward(encoderInchesToCounts(12), 75, true);
//info_printf(1, "before shoot");
  while (shootBall() == 0){//waits for ball to be shot
    pros::delay(10);
  }
  resetEncoders();
  driveBackward(encoderInchesToCounts(15), 75, true);
  resetEncoders();
  turnLeft(725,50,true);
    resetEncoders();
  intakeOn(false);  //turns intake on
  driveForward(encoderInchesToCounts(40), 50, true);//drive to cap
    resetEncoders();
  pros::delay(250);//wait for ball to enter mechanism
  driveBackward(encoderInchesToCounts(40), 75,true);//reverse from cap
    resetEncoders();
  turnRight(800,50,true);
    intakeOff();//turn off intake
    resetEncoders();
  driveBackward(encoderInchesToCounts(16), 75,true);//reverse from cap
  while (shootBall() == 0){//waits for ball to be shot
    pros::delay(10);
  }
    resetEncoders();
  turnLeft(750,50,true);
  while(platformpresentblue() != 1){delay(10);}
}
