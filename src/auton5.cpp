#include "main.h"
#include "robot.h"
/**
* \details calls the fifth autonomous function
*/

extern pros::Motor liftMotor;
void auton5()
{
  // intakeOn(false);
  while(shootBall(0) != 1);

}
