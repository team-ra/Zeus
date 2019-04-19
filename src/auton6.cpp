#include "main.h"
#include "robot.h"
/**
* \details calls the sixth autonomous function
*/
void auton6()
{
  resetEncoders();
  intakeOn(false);//turn intake on
  while( driveForward(encoderInchesToCounts(42), 50, true) != 1);
  pros::delay(500);//get ball into launcher
  while( driveBackward(encoderInchesToCounts(6), 50, true) != 1);
  pros::delay(500);//get ball into launcher
  intakeOff();//shut off intake
  while( driveBackward(encoderInchesToCounts(18), 50, true) != 1);
  while( turnLeft(500,50,true) != 1);//turn to face cap
  intakeOn(true);//turn intake on in reverse to flip the cap
  while( driveForward(encoderInchesToCounts(20), 75, true) != 1);
  intakeOff();//shut off intake
  while( turnRight(300,50,true) != 1);//turn to face center middle flag

  //shoot ball at flag
  while (shootBall(0) == 0){//waits for ball to be shot
    pros::delay(10);
  }
}
