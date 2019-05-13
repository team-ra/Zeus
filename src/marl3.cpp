#include "main.h"
#include "robot.h"
extern pros::Motor liftMotor;
extern pros::Motor launchMotor;
void auton13()
{
  resetEncoders();
  // pros::delay(250);//waits to allow sensors to stablize
  //info_printf(1, "auton1");
  motorSetup();//sets up the motors
  //drives forward 1 square to prepare for shooting the middle flag
  intakeOn(false);  //turns intake on
  AccelerateForward(50);
  home(1);
  while (driveForward(encoderInchesToCounts(33), 50, false) != 1){
    home(0);
  }//drive to cap 40
  pros::delay(500);//wait for ball to enter mechanism
  AccelerateBackward(-50);
  while(driveBackward(50, 50,true) != 1);//reverse from cap
  pros::delay(250);
  while(turnLeft(900,50,true) != 1);//500
  pros::delay(250);
  AccelerateForward(50);
  while (driveForward(encoderInchesToCounts(12), 50, true) != 1){}//12
  // intakeOff();//turn off intake
  shootBall(1);
  while(shootBall(0) != 1);
  while(elevate(4) != 1);
  shootBall(1);
  while(shootBall(0) != 1);
//info_printf(1, "before shoot");
  pros::delay(250);
  resetEncoders();
  while( turnLeft(80,50,true) != 1);
  pros::delay(250);
  resetEncoders();
  while(driveForward(encoderInchesToCounts(34),50,true) != 1);
  pros::delay(50);
  resetEncoders();
  while( turnRight(300,50,true) != 1);
  pros::delay(50);
  resetEncoders();
  while( turnLeft(150,50,true) != 1);
  // AccelerateBackward(-50);(250);
  // while (driveBackward(encoderInchesToCounts(19), 50, true) != 1);//24
  // while(turnRight(100,50,true) !=1);

  // while (shootBall(0) == 0){//waits for ball to be shot
  //   pros::delay(10);
  // }
  // while(turnLeft(100,25,true) != 1);
  // while(driveBackward(encoderInchesToCounts(30), 50,true) != 1);//reverse from cap
  // while(turnRight(100,50,true) !=1);
}
