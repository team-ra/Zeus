#include "main.h"
#include "robot.h"
/**
* \details calls the seventh autonomous function
*/
void auton7()
{
  driveBackward(encoderInchesToCounts(16), 100, true);
  turnRight(800,50,true);
  driveForward(encoderInchesToCounts(40),127,true);
}
