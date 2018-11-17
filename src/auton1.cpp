#include "main.h"
#include "robot.h"
#include "robot_gui.h"

#define DRIVE1_DIST_INCHES 40
#define DRIVE1_POWER 100
void auton1()
{
  pros::delay(250);
  //info_printf(1, "auton1");
  motorSetup();
  driveForward(encoderInchesToCounts(12), 100, true);
  //info_printf(1, "before shoot");
  while (shootBall() == 0){
    pros::delay(10);
  }
  driveForward(encoderInchesToCounts(DRIVE1_DIST_INCHES),DRIVE1_POWER,true);
  //info_printf(1, "end auton1");
}
