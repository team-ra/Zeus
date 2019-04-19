#include "main.h"
#include "robot.h"
/**
* \details calls the tenth autonomous function
*/
void auton10()
{
  resetEncoders();
  pros::delay(250);
  while( driveForward(encoderInchesToCounts(14),50,true) != 1);
  while (shootBall(0) == 0){//waits for ball to shoot
    pros::delay(10);
  }
  //driveForward(encoderInchesToCounts(4), 50, true);//reverses to platform
  while( turnRight(800,50,true) != 1);//turns to face platform
  while( driveForward(encoderInchesToCounts(40),127,true) != 1);//drives onto platform
}
