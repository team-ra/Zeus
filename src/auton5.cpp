#include "main.h"
#include "robot.h"
extern pros::Motor leftDriveMotor1;
/**
* \details calls the fifth autonomous function
*/
void auton5()
{
  resetEncoders();
  motorSetup();
setBackDriveDist(500);
setBackDrivePwr(100);
while(leftDriveMotor1.get_power() != 0);
}
