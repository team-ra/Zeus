#include "main.h"
#include "robot.h"

void auton2()
{
  turnRight(300, 50,true);
  while (shootBall() == 0);
}
