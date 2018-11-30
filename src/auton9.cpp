#include "main.h"
#include "robot.h"
/**
* \details calls the ninth autonomous function
*/
void auton9()
{
  resetEncoders();
  intakeOn(false);
  driveForward(encoderInchesToCounts(42), 50, true);
  pros::delay(500);
  driveBackward(encoderInchesToCounts(6), 50,true);
  pros::delay(1000);
  intakeOff();
  driveBackward(encoderInchesToCounts(18), 50,true);
  turnRight(400,50,true);
  intakeOn(true);
  driveForward(encoderInchesToCounts(40), 75, true);
  intakeOff();
  turnRight(300,50,true);//turn to face center middle flag
  //shoot ball at flag
  while (shootBall() == 0){//waits for ball to be shot
    pros::delay(10);
  }
}
