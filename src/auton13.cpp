#include "main.h"
#include "robot.h"
/**
* \details calls the eleventh autonomous function
*/
void auton13()
{
  resetEncoders();
  pros::delay(250);
  driveForward(encoderInchesToCounts(22),75,true);
  // while (shootBall() == 0){//waits for ball to shoot
  //   pros::delay(10);
  // }
  //driveForward(encoderInchesToCounts(6), 50, true);//reverses to platform
  turnRight(700,50,true);//turns to face platform
  //driveForward(encoderInchesToCounts(40),127,true);//drives onto platform
  while(platformpresentred() != 1){delay(10);}

}
