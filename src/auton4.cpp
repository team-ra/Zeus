#include "main.h"
#include "robot.h"
/**
* \details calls the fourth autonomous function
*/
void auton4()
{

  intakeOn(false);  //turns intake on
  driveForward(encoderInchesToCounts(40), 50, true);//drive to cap
  pros::delay(250);//wait for ball to enter mechanism
  intakeOff();//turn off intake
  driveBackward(encoderInchesToCounts(12), 50,true);//reverse from cap

}
