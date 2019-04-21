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
void auton16()
{
  resetEncoders();
  pros::delay(250);//waits to allow sensors to stablize
  //info_printf(1, "auton1");
  motorSetup();//sets up the motors
  //drives forward 1 square to prepare for shooting the middle flag
intakeOn(false);
  while( driveForward(encoderInchesToCounts(10), 50, true) != 1);//12
  pros::delay(500);
//info_printf(1, "before shoot");
  while (shootBall(0) == 0){//waits for ball to be shot
    pros::delay(10);
  }
  //drives forward 1 square to toggle low flag
  pros::delay(500);
  turnLeft(25,50,true);
  pros::delay(200);
  while( driveForward(encoderInchesToCounts(4),25,true) != 1);
  while( driveForward(encoderInchesToCounts(DRIVE1_DIST_INCHES),DRIVE1_POWER,true) != 1);
  //info_printf(1, "end auton1");
  while( driveBackward(encoderInchesToCounts(12),50,true) != 1);
}
