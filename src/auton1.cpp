#include "main.h"
#include "robot.h"
#include "robot_gui.h"
///The number of inches to drive to reach flag
#define DRIVE1_DIST_INCHES 40
///the power used to get there
#define DRIVE1_POWER 100
/**
* \details calls the first autonomous function
*/
void auton1()
{
  pros::delay(250);//waits to allow sensors to stablize
  //info_printf(1, "auton1");
  motorSetup();//sets up the motors
  //drives forward 1 square to prepare for shooting the middle flag
  driveForward(encoderInchesToCounts(12), 100, true);
//info_printf(1, "before shoot");
  while (shootBall() == 0){//waits for ball to be shot
    pros::delay(10);
  }
  //drives forward 1 square to toggle low flag
  driveForward(encoderInchesToCounts(DRIVE1_DIST_INCHES),DRIVE1_POWER,true);
  //info_printf(1, "end auton1");
}
