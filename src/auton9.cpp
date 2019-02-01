#include "main.h"
#include "robot.h"
/**
* \details calls the ninth autonomous function
*/
void auton9()
{
  resetEncoders();
  intakeOn(false);
  while( driveForward(encoderInchesToCounts(42), 50, true) != 1);
  pros::delay(500);
  while( driveBackward(encoderInchesToCounts(6), 50, true) != 1);
  pros::delay(1000);
  intakeOff();
  while( driveBackward(encoderInchesToCounts(18), 50, true) != 1);
  while( turnRight(400,50,true) != 1);
  intakeOn(true);
  while( driveForward(encoderInchesToCounts(40), 75, true) != 1);
  intakeOff();
  while( turnRight(300,50,true) != 1);//turn to face center middle flag
  //shoot ball at flag
  while (shootBall() == 0){//waits for ball to be shot
    pros::delay(10);
  }
}
