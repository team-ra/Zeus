#include "main.h"
#include "robot.h"
/**
* \details calls the seventh autonomous function
*/
void auton7()
{
  resetEncoders();
  while( driveBackward(encoderInchesToCounts(16), 100, true) != 1);
  while( turnRight(800,50,true) != 1);//turns to face platform
  while( driveForward(encoderInchesToCounts(40), 127, true) != 1);
}
