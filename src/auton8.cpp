#include "main.h"
#include "robot.h"
/**
* \details calls the eighth autonomous function
*/
void auton8()
{
  resetEncoders();
  driveBackward(encoderInchesToCounts(16), 100, true);//reverses to platform
  turnLeft(800,50,true);//turns to face platform
  driveForward(encoderInchesToCounts(40),127,true);//drives onto platform
}
