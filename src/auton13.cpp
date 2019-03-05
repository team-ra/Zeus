#include "main.h"
#include "robot.h"
extern pros::Motor liftMotor;
void auton13()
{
  resetEncoders();
  pros::delay(250);//waits to allow sensors to stablize
  //info_printf(1, "auton1");
  motorSetup();//sets up the motors
  //drives forward 1 square to prepare for shooting the middle flag
  intakeOn(false);  //turns intake on
  AccelerateForward(75);

  while (driveForward(encoderInchesToCounts(36), 75, true) != 1);//drive to cap 40
  pros::delay(250);//wait for ball to enter mechanism
  AccelerateBackward(-75);
  while(driveBackward(encoderInchesToCounts(32), 75,true) != 1);//reverse from cap
  while(turnLeft(745,50,true) != 1);//750
  AccelerateForward(100);
  while (driveForward(encoderInchesToCounts(36), 100, true) != 1);//12
  // intakeOff();//turn off intake

//info_printf(1, "before shoot");
  resetEncoders();
  pros::delay(100);
  AccelerateBackward(-100);
  while (driveBackward(encoderInchesToCounts(19), 100, true) != 1);//24
  while(turnRight(100,50,true) !=1);

  while (shootBall() == 0){//waits for ball to be shot
    pros::delay(10);
  }
  resetEncoders();
  while(turnLeft(100,25,true) != 1);
  while(driveBackward(encoderInchesToCounts(30), 75,true) != 1);//reverse from cap
  while(turnRight(100,50,true) !=1);
  while (shootBall() == 0){//waits for ball to be shot
    pros::delay(10);
  }
  while(turnLeft(100,50,true) !=1);
  resetEncoders();
  extern pros::Motor leftDriveMotor1;
  AccelerateForward(100);
  while( driveForward(encoderInchesToCounts(20),100,true) == 0);
  while( turnLeft(1000,50,true) == 0);//900
  liftMotor.move(-50);
  AccelerateBackward(-100);
  while( driveBackward(encoderInchesToCounts(24),75,true) == 0);
  liftMotor.move(-100);
  delay(100);
  liftMotor.move(0);
  AccelerateBackward(-100);
  while( driveBackward(encoderInchesToCounts(21),75,true) == 0);

  while( driveForward(encoderInchesToCounts(20),100,true) == 0);
}
