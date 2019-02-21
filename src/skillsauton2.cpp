#include "main.h"
#include "robot.h"
extern pros::Motor leftDriveMotor2;
extern pros::Motor wristMotor;
extern pros::Motor leftDriveMotor1;
void skillsauton2() {

  //
  // resetEncoders();
  //   pros::delay(250);//waits to allow sensors to stablize
  //   motorSetup();//sets up the motors
  //
  //   intakeOn(false);  //turns intake on
  //   //drive to cap
  //   AccelerateForward(50);
  //   while (driveForward(encoderInchesToCounts(32), 50, true) != 1);
  //   pros::delay(250);//wait for ball to enter mechanism
  //
  //   //reverse from cap to starting square
  //   AccelerateBackward(-50);
  //   while(driveBackward(encoderInchesToCounts(30.5), 50,true) != 1);
  //   delay(500);
  //   //turn to face flags
  //   while(turnLeft(845,50,true) != 1);
  //
  //   //hit bottom flag
  //   AccelerateForward(70);
  //   while (driveForward(encoderInchesToCounts(40), 70, true) != 1);//12
  //
  //   //drive back to hit middle flag
  //   delay(500);
  //   resetEncoders();
  //   AccelerateBackward(-50);
  //   while (driveBackward(encoderInchesToCounts(15), 50, true) != 1);
  //   pros::delay(100);
  //
  //   //jog to get in line with flags
  //   resetEncoders();
  //   delay(500);
  //   while(turnLeft(300,50,true) !=1);
  //   while (driveBackward(encoderInchesToCounts(12), 50, true) != 1);
  //   delay(500);
  //   while(turnRight(420,50,true) !=1);
  //
  //   //shoot middle flag
  //   while (shootBall() == 0){//waits for ball to be shot
  //     pros::delay(10);
  //   }
  //
  //   //drive back to hit top flag
  //   resetEncoders();
  //   while(driveBackward(encoderInchesToCounts(30), 75,true) != 1);//reverse from cap
  //
  //   //shoot top flag
    // while (shootBall() == 0){//waits for ball to be shot
    //   pros::delay(10);
    // }
    // while(driveForward(encoderInchesToCounts(13),50,true) != 1);
    // delay(500);
    //rake ball off platform
    intakeOn(false);
    wristMotor.move(-50);
    while(wristMotor.get_position() > -750);
    wristMotor.move(0);
    resetEncoders();
    while(turnRight(600,50,true) != 1);
    delay(500);
    resetEncoders();
    while(driveForward(encoderInchesToCounts(8),50,true) != 1);
    wristMotor.tare_position();
    wristMotor.move(-75);

    while(wristMotor.get_position() > -100);
    wristMotor.move(0);
    resetEncoders();

    while(driveBackward(encoderInchesToCounts(10), 25,true) != 1);
    delay(500);
    //while(turnLeft(1250,50,true) != 1);

    //while(driveForward(encoderInchesToCounts(4),50,true) != 1);
    delay(500);
    //while(turnLeft(320,50,true) != 1);
    delay(500);
    while (shootBall() == 0){//waits for ball to be shot
      pros::delay(10);
    }
}
