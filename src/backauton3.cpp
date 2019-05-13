#include "robot.h"
void backauton3() {
resetEncoders();
intakeOn(false);  //turns intake on
AccelerateForward(50);
home(1);
while (driveForward(encoderInchesToCounts(33), 50, false) != 1){
  home(0);
}//drive to cap 40
pros::delay(250);//wait for ball to enter mechanism
AccelerateBackward(-50);
while(driveBackward(50, 50,true) != 1);//reverse from cap
pros::delay(100);
resetEncoders();
while(turnLeft(830,50,true) != 1);//500
resetEncoders();
AccelerateForward(50);
intakeOff();
while (driveForward(encoderInchesToCounts(20), 50, true) != 1){}//12
pros::delay(100);
resetEncoders();
while(turnRight(830,50,true) != 1);//500
pros::delay(100);
resetEncoders();
while (driveForward(encoderInchesToCounts(40), 75, false) != 1){}//12
pros::delay(100);
while(driveBackward(encoderInchesToCounts(39.5), 25,true) != 1);//reverse from cap
pros::delay(100);
resetEncoders();
elevate(1);
gyroReset();
while(gyroturn(-46) != 1){
  elevate(6);
}//500
pros::delay(100);
shootBall(1);
while(shootBall(0) != 1);
delay(100);
resetEncoders();
// while(turnLeft(225,25,true) != 1);//500
elevate(4);
while(elevate(6) != 1);
shootBall(1);
while(shootBall(0) != 1);
}
