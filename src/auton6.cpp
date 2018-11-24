#include "main.h"
#include "robot.h"
/**
* \details calls the sixth autonomous function
*/
void auton6()
{
  intakeOn(false);
  driveForward(encoderInchesToCounts(42), 50, true);
  pros::delay(500);
  driveBackward(encoderInchesToCounts(6), 50,true);
  pros::delay(500);
  intakeOff();
  driveBackward(encoderInchesToCounts(18), 50,true);
  turnLeft(500,50,true);
  intakeOn(true);
  driveForward(encoderInchesToCounts(20), 75, true);
  intakeOff();
  turnRight(300,50,true);
  while (shootBall() == 0){//waits for ball to be shot
    pros::delay(10);
  }
  //driveBackward(encoderInchesToCounts(50),100,true);
}
