#include "main.h"
#include "robot.h"
/**
* \details calls the fifth autonomous function
*/
void auton5()
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
