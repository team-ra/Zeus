#include "main.h"
#include "robot.h"
/**
* \details calls the fourth autonomous function
*/
void auton4()
{
resetEncoders();
  intakeOn(false);  //turns intake on
  while( driveForward(encoderInchesToCounts(40), 50, true) != 1);
  pros::delay(250);//wait for ball to enter mechanism
  intakeOff();//turn off intake
  while( driveBackward(encoderInchesToCounts(12), 50, true) != 1);

}
