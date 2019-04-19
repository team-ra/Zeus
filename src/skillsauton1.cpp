// #include "main.h"
// #include "robot.h"
// extern pros::Motor leftDriveMotor2;
// void skillsauton1() {
//
//     intakeOn(false);
//     while( driveForward(encoderInchesToCounts(40), 50, true) != 1);//drive to cap
//     pros::delay(250);
//     while( driveBackward(encoderInchesToCounts(28), 75,true) != 1);
//     while( turnLeft(800,50,true) != 1);
//     //drive to shoot position
//
//     while( driveForward(encoderInchesToCounts(8), 75, true) != 1);
//
//     //shoot flag
//     while (shootBall(0) == 0){pros::delay(10);}
//
//     while( driveBackward(encoderInchesToCounts(20), 75, true) != 1);
//
//     //shoot flag
//     while (shootBall(0) == 0){pros::delay(10);}
//
//     while (driveBackward(encoderInchesToCounts(16), 75, true) != 1);
//
//     //turn to face platform
//     while( turnRight(800,50,true) != 1);
//     delay(50);
//     intakeOff();
//     //park
//   //driveForward(encoderInchesToCounts(15),100,true);//drives onto platform
//   leftDriveMotor2.tare_position();
//   leftDriveMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
//   leftDriveSet(100);
//   rightDriveSet(100);
//   while(leftDriveMotor2.get_position() < encoderInchesToCounts(60));
//   leftDriveSet(0);
//   rightDriveSet(0);
// }

#include "main.h"
#include "robot.h"

extern pros::Motor liftMotor;
void skillsauton1()
{
//   resetEncoders();
//   pros::delay(250);//waits to allow sensors to stablize
//   //info_printf(1, "auton1");
//   motorSetup();//sets up the motors
//   //drives forward 1 square to prepare for shooting the middle flag
//   intakeOn(false);  //turns intake on
//   AccelerateForward(75);
//
//   while (driveForward(encoderInchesToCounts(13), 75, true) != 1);//drive to cap 40
//   while (driveForward(encoderInchesToCounts(25), 50, true) != 1);//drive to cap 40
//
//   pros::delay(250);//wait for ball to enter mechanism
//   AccelerateBackward(-75);
//   while(driveBackward(encoderInchesToCounts(32), 75,true) != 1);//reverse from cap
//   while(turnLeft(790,50,true) != 1);
//   AccelerateForward(100);
//   while (driveForward(encoderInchesToCounts(38), 100, true) != 1);//12
//   // intakeOff();//turn off intake
//
// //info_printf(1, "before shoot");
//   resetEncoders();
//   pros::delay(100);
//   AccelerateBackward(-100);
//   while (driveBackward(encoderInchesToCounts(19), 100, true) != 1);//24
//   while(turnRight(100,50,true) !=1);
//
//   while (shootBall(0) == 0){//waits for ball to be shot
//     pros::delay(10);
//   }
//   resetEncoders();
//   while(turnLeft(100,25,true) != 1);
//   while(driveBackward(encoderInchesToCounts(30), 75,true) != 1);//reverse from cap
//   while(turnRight(100,50,true) !=1);
//   while (shootBall(0) == 0){//waits for ball to be shot
//     pros::delay(10);
//   }
//   turnLeft(100,50,true);
liftMotor.tare_position();
  liftMotor.move(-100);
  while(liftMotor.get_position() > -800);
  liftMotor.move(0);
  while(driveBackward(encoderInchesToCounts(16),25,true) != 1);//reverse from cap
  liftMotor.move(75);
  liftMotor.tare_position();
  while(liftMotor.get_position() < 50);
  liftMotor.move(0);
  resetEncoders();
  while(driveForward(encoderInchesToCounts(8),25,true) != 1);//reverse from cap


}
