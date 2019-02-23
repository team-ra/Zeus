#include "main.h"
#include "robot.h"
/**
* \details calls the fourth autonomous function
*/
void auton4()
{
resetEncoders();
  intakeOn(false);  //turns intake on
  AccelerateForward(50);
  while( driveForward(encoderInchesToCounts(33), 50, true) != 1);
  pros::delay(500);//wait for ball to enter mechanism
  intakeOff();//turn off intake
  AccelerateBackward(-75);
  while( driveBackward(encoderInchesToCounts(12), 75, true) != 1);

}
