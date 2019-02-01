#include "main.h"
#include "robot.h"
/**
* \details calls the eighth autonomous function
*/
void auton8()
{
  resetEncoders();
  while( driveBackward(encoderInchesToCounts(16), 100, true) != 1);
  while( turnLeft(800,50,true) != 1);//turns to face platform
  while( driveForward(encoderInchesToCounts(40), 127, true) != 1);
}
