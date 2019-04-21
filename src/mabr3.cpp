#include "robot.h"
#include "robot_gui.h"

void auton17() {
  resetEncoders();
  pros::delay(250);//waits to allow sensors to stablize
  //info_printf(1, "auton1");
  motorSetup();//sets up the motors
  //drives forward 1 square to prepare for shooting the middle flag
  intakeOn(false);  //turns intake on
  AccelerateForward(50);

  while (driveForward(encoderInchesToCounts(33), 50, false) != 1) {
    elevate(0);
  }//drive to cap 40
  pros::delay(500);//wait for ball to enter mechanism
  AccelerateBackward(-50);
  while(driveBackward(100, 50,true) != 1);//reverse from cap
  pros::delay(250);
  while(turnRight(475,50,true) != 1);//500
  pros::delay(250);
  AccelerateForward(50);
  while (driveForward(encoderInchesToCounts(15), 50, true) != 1){}//12
  // intakeOff();//turn off intake
  shootBall(1);
  while(shootBall(0) != 1);
  while(elevate(4) != 1);
  shootBall(1);
  while(shootBall(0) != 1);

  //info_printf(1, "before shoot");
  pros::delay(250);
  resetEncoders();
  while( turnRight(50,50,true) != 1);
  pros::delay(250);
  resetEncoders();
  while(driveForward(encoderInchesToCounts(28),50,true) != 1);
  pros::delay(250);
  resetEncoders();
  while(turnLeft(300,75,true) != 1);

}
