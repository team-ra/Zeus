#include "main.h"
#include "robot.h"
extern pros::Motor leftDriveMotor2;
void auton13()
{
  //turn to face flags
  //turnRight(100,50,true);

  intakeOn(false);
  while( driveForward(encoderInchesToCounts(40), 50, true) != 1);//drive to cap
  pros::delay(250);
  while( driveBackward(encoderInchesToCounts(28), 75,true) != 1);
  while( turnLeft(800,50,true) != 1);
  //drive to shoot position

  while( driveForward(encoderInchesToCounts(8), 75, true) != 1);

  //shoot flag
  while (shootBall() == 0){pros::delay(10);}

  while( driveBackward(encoderInchesToCounts(20), 75, true) != 1);

  //shoot flag
  while (shootBall() == 0){pros::delay(10);}

  while (driveBackward(encoderInchesToCounts(14), 75, true) != 1);

  //turn to face platform
  while( turnRight(800,50,true) != 1);
  delay(50);
  //park
  //while(platformpresentred() != 1){delay(10);}
  leftDriveMotor2.tare_position();
  leftDriveMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  leftDriveSet(100);
  rightDriveSet(100);
  while(leftDriveMotor2.get_position() < encoderInchesToCounts(30));
  leftDriveSet(0);
  rightDriveSet(0);
}
