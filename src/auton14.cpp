#include "main.h"
#include "robot.h"
extern pros::Motor liftMotor;
void auton12()
{
  resetEncoders();
  //info_printf(1, "auton1");
  motorSetup();//sets up the motors
  //drives forward 1 square to prepare for shooting the middle flag
  intakeOn(false);  //turns intake on

  AccelerateForward(50);
  while (driveForward(encoderInchesToCounts(33), 50, true) != 1);//drive to cap 40
  pros::delay(250);//wait for ball to enter mechanism
  AccelerateBackward(-75);
  while(driveBackward(encoderInchesToCounts(30), 75,true) != 1);//reverse from cap
  delay(250);
  while(turnRight(1140,50,true) != 1);
  delay(250);
  AccelerateForward(100);
  while (driveForward(encoderInchesToCounts(42), 100, true) != 1);//12
  // intakeOff();//turn off intake

//info_printf(1, "before shoot");
  resetEncoders();
  pros::delay(100);
  AccelerateBackward(-75);
  while (driveBackward(encoderInchesToCounts(17), 75, true) != 1);//24

  while (shootBall(0) == 0){//waits for ball to be shot
    pros::delay(10);
  }

  while(driveBackward(encoderInchesToCounts(30), 75,true) != 1);//reverse from cap
  while (shootBall(0) == 0){//waits for ball to be shot
    pros::delay(10);
  }
  extern pros::Motor leftDriveMotor1;
  resetEncoders();
  AccelerateForward(100);
  while( driveForward(encoderInchesToCounts(20),100,true) == 0);
  while( turnRight(950,50,true) == 0);
  liftMotor.move(-50);
  AccelerateBackward(-100);
  while( driveBackward(encoderInchesToCounts(32),75,true) == 0);
  liftMotor.move(-100);
  delay(100);
  liftMotor.move(0);

  while( driveForward(encoderInchesToCounts(15),100,true) == 0);
}
