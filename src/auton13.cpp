#include "main.h"
#include "robot.h"
extern pros::Motor liftMotor;
extern pros::Motor launchMotor;
void auton13()
{
  resetEncoders();
  pros::delay(250);//waits to allow sensors to stablize
  //info_printf(1, "auton1");
  motorSetup();//sets up the motors
  //drives forward 1 square to prepare for shooting the middle flag
  intakeOn(false);  //turns intake on
  AccelerateForward(50);

  while (driveForward(encoderInchesToCounts(33), 50, false) != 1){
    elevate(0);
  }//drive to cap 40
  pros::delay(500);//wait for ball to enter mechanism
  AccelerateBackward(-50);
  while(driveBackward(100, 50,true) != 1);//reverse from cap
  delay(250);
  while(turnLeft(950,50,true) != 1);//500
  delay(250);
  AccelerateForward(50);
  while (driveForward(encoderInchesToCounts(15), 50, true) != 1){}//12
  // intakeOff();//turn off intake
  while(shootBall() != 1);
  while(elevate(4) != 1);
  while(shootBall() != 1);

//info_printf(1, "before shoot");
  pros::delay(250);
  resetEncoders();
  while( turnLeft(80,50,true) != 1);
  delay(250);
  resetEncoders();
  while(driveForward(encoderInchesToCounts(28),50,true) != 1);
  // AccelerateBackward(-50);(250);
  // while (driveBackward(encoderInchesToCounts(19), 50, true) != 1);//24
  // while(turnRight(100,50,true) !=1);

  // while (shootBall() == 0){//waits for ball to be shot
  //   pros::delay(10);
  // }
  // while(turnLeft(100,25,true) != 1);
  // while(driveBackward(encoderInchesToCounts(30), 50,true) != 1);//reverse from cap
  // while(turnRight(100,50,true) !=1);
}
