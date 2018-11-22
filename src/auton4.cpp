#include "main.h"
#include "robot.h"
/**
* \details calls the fourth autonomous function
*/
void auton4()
{
  driveForward(encoderInchesToCounts(44),100,true);
  driveBackward(encoderInchesToCounts(24),100,true);
  turnLeft(180, 100,true);
  intakeOn(true);
  driveForward(encoderInchesToCounts(24),100,true);
  intakeOff();
  driveBackward(encoderInchesToCounts(20), 100, true);
}
