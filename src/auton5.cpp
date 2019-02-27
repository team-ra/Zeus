#include "main.h"
#include "robot.h"
/**
* \details calls the fifth autonomous function
*/

extern pros::Motor liftMotor;
void auton5()
{
  extern pros::Motor leftDriveMotor1;
  resetEncoders();
  AccelerateForward(100);
  while( driveForward(encoderInchesToCounts(20),100,true) == 0);
  while( turnRight(1100,50,true) == 0);
  liftMotor.move(-50);
  AccelerateBackward(-100);
  while( driveBackward(encoderInchesToCounts(24),75,true) == 0);
  liftMotor.move(-100);
  delay(100);
  liftMotor.move(0);
  AccelerateBackward(-100);
  while( driveBackward(encoderInchesToCounts(24),75,true) == 0);

  while( driveForward(encoderInchesToCounts(20),100,true) == 0);
  
}
