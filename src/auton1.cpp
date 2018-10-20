#include "main.h"
#include "robot.h"

#define DRIVE1_DIST_INCHES 36
#define DRIVE1_POWER 100
void auton1()
{
  //shootBall();
  driveForward(encoderInchesToCounts(DRIVE1_DIST_INCHES),DRIVE1_POWER,true);

}
