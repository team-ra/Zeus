#include "main.h"
#include "robot.h"
#define DRIVE1_DIST_INCHES 40
#define DRIVE1_POWER 100

void auton3()
{
  pros::delay(100);
  driveForward(encoderInchesToCounts(20),100,true);
  while (shootBall() == 0);
  driveForward(encoderInchesToCounts(24),100,true);
  driveBackward(encoderInchesToCounts(24),100,true);
  turnLeft(120, 50,true);
  driveForward(encoderInchesToCounts(24),100,true);
  turnLeft(120, 50,true);
  driveForward(encoderInchesToCounts(24),100,true);
}
