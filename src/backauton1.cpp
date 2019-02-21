#include "robot.h"

extern pros::Motor liftMotor;
void backauton1() {
  intakeOn(false);  //turns intake on
  AccelerateForward(75);

  while (driveForward(encoderInchesToCounts(38), 75, true) != 1);//drive to cap 40
  pros::delay(250);//wait for ball to enter mechanism
  while(turnRight(810,50,true) != 1);
  AccelerateBackward(-50);
  while(driveBackward(encoderInchesToCounts(4),50,true) != 1);
  liftMotor.move(-100);
  delay(250);
  liftMotor.move(0);
  AccelerateForward(50);
  while(driveForward(encoderInchesToCounts(4),50,true) != 1);
  turnLeft(250,50,true);
  while (shootBall() == 0){//waits for ball to be shot
    pros::delay(10);
  }
  turnRight(250,50,true);
  while (shootBall() == 0){//waits for ball to be shot
    pros::delay(10);
  }

}
