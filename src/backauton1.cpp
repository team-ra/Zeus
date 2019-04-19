#include "robot.h"

extern pros::Motor liftMotor;
void backauton1() {
  //turn to shoot center flag
  resetEncoders();
  while( turnRight(520,50,true) != 1);//575
  delay(500);
  resetEncoders();
  //shoot center flag
  while( shootBall(0) != 1);

  //turn to face cap
  while( turnLeft(465,50,true) != 1);//498

//get ball
  intakeOn(false);  //turns intake on
  while( driveForward(encoderInchesToCounts(31),65,true) != 1);
  delay(250);
  resetEncoders();

  //reverse from cap
  while( driveBackward(encoderInchesToCounts(31),65,true) != 1);
  delay(250);
  resetEncoders();
  while(turnRight(420,50,true) != 1);//
  delay(500);
  resetEncoders();
  while( driveForward(encoderInchesToCounts(14),50,true) != 1);
  delay(250);
  resetEncoders();
  while( shootBall(0) != 1);
  delay(250);
  resetEncoders();
  while( driveBackward(encoderInchesToCounts(6),75,true) != 1);
  delay(500);
  resetEncoders();
  while( turnRight(360,50,true) != 1);
  delay(500);
  resetEncoders();
  while( driveForward(encoderInchesToCounts(11),75,true) != 1);
  delay(250);
  resetEncoders();

  while( turnLeft(510,50,true) != 1);
  delay(500);
  resetEncoders();
  while( driveForward(encoderInchesToCounts(34),120,true) != 1);//75
}
