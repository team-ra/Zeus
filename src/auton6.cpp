#include "main.h"
#include "robot.h"
/**
* \details calls the sixth autonomous function
*/
void auton6()
{
  resetEncoders();
  intakeOn(false);//turn intake on
  driveForward(encoderInchesToCounts(42), 50, true);//drive to cap
  pros::delay(500);//get ball into launcher
  driveBackward(encoderInchesToCounts(6), 50,true);//move away from cap to avoid pulling it in
  pros::delay(500);//get ball into launcher
  intakeOff();//shut off intake
  driveBackward(encoderInchesToCounts(18), 50,true);//move back to prepare to align with second cap
  turnLeft(500,50,true);//turn to face cap
  intakeOn(true);//turn intake on in reverse to flip the cap
  driveForward(encoderInchesToCounts(20), 75, true);//drive forward flipping the cap
  intakeOff();//shut off intake
  turnRight(300,50,true);//turn to face center middle flag
  //shoot ball at flag
  while (shootBall() == 0){//waits for ball to be shot
    pros::delay(10);
  }
  //driveBackward(encoderInchesToCounts(50),100,true);
}
