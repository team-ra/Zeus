#include "main.h"
#include "robot.h"
/**
* \details calls the eleventh autonomous function
*/
void auton11()
{
  // resetEncoders();
  // pros::delay(250);
  // driveForward(encoderInchesToCounts(14),50,true);
  // while (shootBall() == 0){//waits for ball to shoot
  //   pros::delay(10);
  // }
  //driveForward(encoderInchesToCounts(6), 50, true);//reverses to platform
  //turnLeft(500,50,true);//turns to face platform
  //driveForward(encoderInchesToCounts(40),127,true);//drives onto platform
  while(platformpresentblue() != 1){delay(10);}

}
