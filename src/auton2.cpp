#include "main.h"
#include "robot.h"

void auton2()
{
   turnRight(30, 50,true);
  driveForward(encoderInchesToCounts(19), 100,true);
  while (shootBall() == 0);
}
