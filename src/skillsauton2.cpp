#include "main.h"
#include "robot.h"
extern pros::Motor leftDriveMotor2;
extern pros::Motor wristMotor;
extern pros::Motor leftDriveMotor1;
void skillsauton2() {

  //
  resetEncoders();
    motorSetup();//sets up the motors

    intakeOn(false);  //turns intake on
    //drive to cap
    AccelerateForward(50);
    while (driveForward(encoderInchesToCounts(34.75), 50, true) != 1);
    delay(750);//wait for ball to enter mechanism
    resetEncoders();

    //reverse from cap to starting square
    AccelerateBackward(-50);
    while(driveBackward(encoderInchesToCounts(34.75), 50,true) != 1);
    delay(500);
    resetEncoders();

    //turn to face flags
    while(turnLeft(845,50,true) != 1);
    delay(500);
    resetEncoders();

    //hit bottom flag
    AccelerateForward(70);
    while (driveForward(encoderInchesToCounts(41), 70, true) != 1);//12
    delay(500);
    resetEncoders();

    //drive back to hit middle flag
    AccelerateBackward(-50);
    while (driveBackward(encoderInchesToCounts(15), 50, true) != 1);
    delay(500);
    resetEncoders();

    //jog to get in line with flags
    while(turnLeft(300,50,true) !=1);
    delay(500);
    resetEncoders();
    while (driveBackward(encoderInchesToCounts(14), 50, true) != 1);
    delay(500);
    while(turnRight(420,50,true) !=1);
    delay(500);
    resetEncoders();

    //shoot middle flag
    while (shootBall() == 0){//waits for ball to be shot
      delay(10);
    }

    //drive back to shoot top flag
    while(driveBackward(encoderInchesToCounts(30), 50,true) != 1);//reverse from cap
    delay(500);
    resetEncoders();

    //shoot top flag
    while (shootBall() == 0){//waits for ball to be shot
      delay(10);
      }
    while(driveForward(encoderInchesToCounts(2.5),50,true) != 1);
    delay(250);
    resetEncoders();


    //rake ball off platform
    intakeOn(false);
    while(turnRight(750,50,true) != 1);
    delay(500);
    resetEncoders();
    while(driveForward(encoderInchesToCounts(13),50,true) != 1);
    delay(500);
    resetEncoders();

    //move rake(wristMotor) into position
    wristMotor.tare_position();
    wristMotor.move(-50);
    while(wristMotor.get_position() > -900);//90 degrees
    wristMotor.move(0);
    wristMotor.tare_position();
    wristMotor.move(-75);
    while(wristMotor.get_position() > -50);
    wristMotor.move(0);
    while(driveBackward(encoderInchesToCounts(9), 50,true) != 1);
    delay(500);
    resetEncoders();
    wristMotor.move(100);
    while(driveForward(encoderInchesToCounts(1),25,true) != 1);
    delay(250);
    resetEncoders();
    wristMotor.move(0);

    // while(driveBackward(encoderInchesToCounts(5), 25,true) != 1);
    // delay(250);

    // drive to second ball
    while(turnLeft(700,50,true) != 1);
    delay(500);
    resetEncoders();
    while(driveBackward(encoderInchesToCounts(20), 25,true) != 1);
    delay(500);
    resetEncoders();

    //rake second ball
    while(turnRight(750,50,true) != 1);
    delay(500);
    resetEncoders();
    while(driveForward(encoderInchesToCounts(9.5),50,true) != 1);
    delay(500);
    resetEncoders();

    //move rake(wristMotor) into position
    wristMotor.tare_position();
    wristMotor.move(-50);
    while(wristMotor.get_position() > -800);
    wristMotor.move(0);
    resetEncoders();
    wristMotor.tare_position();
    wristMotor.move(-75);
    while(wristMotor.get_position() > -50);
    wristMotor.move(0);
    while(driveBackward(encoderInchesToCounts(9), 50,true) != 1);
    delay(500);
    resetEncoders();
    wristMotor.move(100);
    while(driveForward(encoderInchesToCounts(1),25,true) != 1);//drive forward to pickup ball
    delay(500);
    resetEncoders();
    wristMotor.move(0);

    //turn to shoot far flag
    while(turnLeft(245,50,true) != 1);
    delay(500);
    resetEncoders();
    while (shootBall() == 0){//waits for ball to be shot
      delay(10);
    }

    //turn to shoot center flag
    while(turnLeft(145,50,true) != 1);
    delay(500);
    resetEncoders();
    while (shootBall() == 0){//waits for ball to be shot
      delay(10);
    }
    //turn to face platform
    while(turnRight(200,50,true) != 1);
    delay(500);
    resetEncoders();

    //park
    leftDriveMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);//configure motor to auto-hold position
    leftDriveMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);//configure motor to auto-hold position
    while( driveForward(encoderInchesToCounts(60.7),65,true) != 1);
}
