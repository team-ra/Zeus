#include "main.h"
#include "robot.h"
/**
* \details calls the seventh autonomous function
*/
void auton7()
{
  resetEncoders();
  driveBackward(encoderInchesToCounts(16), 75, true);//reverses to platform
  turnRight(800,50,true);//turns to face platform
  driveForward(encoderInchesToCounts(40),127,true);//drives onto platform
}
