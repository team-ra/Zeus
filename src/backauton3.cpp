#include "robot.h"
void backauton3() {
resetEncoders();
intakeOn(false);  //turns intake on
AccelerateForward(50);

while (driveForward(encoderInchesToCounts(33), 50, false) != 1){
  elevate(0);
}//drive to cap 40
pros::delay(500);//wait for ball to enter mechanism
AccelerateBackward(-50);
while(driveBackward(50, 50,true) != 1);//reverse from cap
delay(250);
resetEncoders();
while(turnLeft(840,50,true) != 1);//500
resetEncoders();
AccelerateForward(50);
intakeOff();
while (driveForward(encoderInchesToCounts(22), 50, true) != 1){}//12
delay(500);
resetEncoders();
while(turnRight(840,50,true) != 1);//500
delay(500);
resetEncoders();
while (driveForward(encoderInchesToCounts(40), 75, false) != 1){}//12
delay(250);
while(driveBackward(encoderInchesToCounts(39.5), 25,true) != 1);//reverse from cap
delay(250);
resetEncoders();
while(turnLeft(425,25,true) != 1){
  elevate(3);
}//500
delay(500);
while(shootBall(0) != 1);
resetEncoders();
while(turnLeft(225,25,true) != 1);//500
while(shootBall(0) != 1);
}
