#include "main.h"
#include "robot.h"
/**
* \details calls the fourth autonomous function
*/
void auton4()
{
  intakeOn(false);
  driveForward(encoderInchesToCounts(40), 50, true);
  pros::delay(250);
  intakeOff();
  driveBackward(encoderInchesToCounts(12), 50,true);

}
