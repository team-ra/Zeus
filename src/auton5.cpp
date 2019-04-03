#include "main.h"
#include "robot.h"
/**
* \details calls the fifth autonomous function
*/

extern pros::Motor liftMotor;
void auton5()
{
  intakeOn(false);
  while(driveForward(2000, 50,false) != 1);
  while(driveBackward(0, 50,false) != 1);
  while(turnLeft(500,50,true) != 1);
  while(turnRight(500,50,true) != 1);

}
