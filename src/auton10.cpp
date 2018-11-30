#include "main.h"
#include "robot.h"
/**
* \details calls the tenth autonomous function
*/
void auton10()
{
  resetEncoders();
  pros::delay(250);
  driveForward(encoderInchesToCounts(14),50,true);
  while (shootBall() == 0){//waits for ball to shoot
    pros::delay(10);
  }
  //driveForward(encoderInchesToCounts(4), 50, true);//reverses to platform
  turnRight(800,50,true);//turns to face platform
  driveForward(encoderInchesToCounts(40),127,true);//drives onto platform
}
