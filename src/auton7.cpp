#include "main.h"
#include "robot.h"
/**
* \details calls the seventh autonomous function
*/
void auton7()
{
  driveBackward(encoderInchesToCounts(16), 100, true);//reverses to platform
  turnRight(800,50,true);//turns to face platform
  driveForward(encoderInchesToCounts(40),127,true);//drives onto platform
}
