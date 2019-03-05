#include "robot.h"

extern pros::Motor liftMotor;
void backauton2() {
  //turn to shoot center flag
  while( turnLeft(450,50,true) != 1);//390
  delay(500);
  resetEncoders();
  //shoot center flag
  while( shootBall() != 1);

  //turn to face cap
  while( turnRight(430,50,true) != 1);

//get ball
  intakeOn(false);  //turns intake on
  while( driveForward(encoderInchesToCounts(31),65,true) != 1);
  delay(250);
  resetEncoders();

  //reverse from cap
  while( driveBackward(encoderInchesToCounts(31),65,true) != 1);
  delay(250);
  resetEncoders();
  while(turnLeft(380,50,true) != 1);//300
  delay(500);
  resetEncoders();
  while( driveForward(encoderInchesToCounts(14),50,true) != 1);
  delay(250);
  resetEncoders();
  while( shootBall() != 1);
  delay(250);
  resetEncoders();
  while( driveBackward(encoderInchesToCounts(6),50,true) != 1);
  delay(500);
  resetEncoders();
  while( turnLeft(300,50,true) != 1);
  delay(500);
  resetEncoders();
  while( driveForward(encoderInchesToCounts(8),50,true) != 1);
  delay(250);
  resetEncoders();

  while( turnRight(500,50,true) != 1);
  delay(500);
  resetEncoders();
  while( driveForward(encoderInchesToCounts(32),75,true) != 1);
}
