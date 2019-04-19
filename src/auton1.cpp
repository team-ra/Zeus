#include "main.h"
#include "robot.h"
#include "robot_gui.h"
///The number of inches to drive to reach flag
#define DRIVE1_DIST_INCHES 30
///the power used to get there
#define DRIVE1_POWER 65
/**
* \details calls the first autonomous function
*/
void auton1()
{
  resetEncoders();
  pros::delay(250);//waits to allow sensors to stablize
  motorSetup();//sets up the motors

  //drives forward 1 square to prepare for shooting the middle flag
intakeOn(false);
  while( driveForward(encoderInchesToCounts(8), 50, true) != 1);//12
  delay(500);

  while (shootBall(0) == 0){//waits for ball to be shot
    pros::delay(10);
  }

  //drives forward 1 square to toggle low flag
  delay(500);
  while( driveForward(encoderInchesToCounts(4),25,true) != 1);
  while( driveForward(encoderInchesToCounts(DRIVE1_DIST_INCHES),DRIVE1_POWER,true) != 1);
  while( driveBackward(encoderInchesToCounts(12),50,true) != 1);
}
