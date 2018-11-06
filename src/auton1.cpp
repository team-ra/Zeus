#include "main.h"
#include "robot.h"

#define DRIVE1_DIST_INCHES 40
#define DRIVE1_POWER 100
void auton1()
{
  pros::delay(250);
  driveForward(encoderInchesToCounts(12), 100, true);
  while (shootBall() == 0);
  //driveForward(encoderInchesToCounts(DRIVE1_DIST_INCHES),DRIVE1_POWER,true);

}
