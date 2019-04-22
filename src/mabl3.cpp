#include "robot.h"
void backauton4() {
  // home(1);
  // while(home(0) == 0);
  // delay(5000);
  // elevate(0);
  // elevate(1);
  // while(elevate(8) == 0);
  // delay(5000);
  // elevate(0);//reset
  // elevate(2);
  // while(elevate(8) == 0);
  // delay(5000);
  // elevate(0);//reset
  // elevate(3);
  // while(elevate(8) == 0);
  // delay(5000);
  // elevate(0);//reset
  // elevate(4);
  // while(elevate(8) == 0);

resetEncoders();
intakeOn(false);  //turns intake on
AccelerateForward(50);
elevate(0);
home(1);
while (driveForward(encoderInchesToCounts(33), 50, false) != 1){
  home(0);
}//drive to cap 40
while( home(0) != 1);
pros::delay(400);//wait for ball to enter mechanism
AccelerateBackward(-50);
while(driveBackward(50, 50,true) != 1);//reverse from cap
delay(250);
resetEncoders();
while(turnRight(650,50,true) != 1);//500
resetEncoders();
AccelerateForward(50);
intakeOff();
while (driveForward(encoderInchesToCounts(22), 50, true) != 1){}//12
delay(400);
resetEncoders();
while(turnLeft(700,50,true) != 1);//500
delay(400);
resetEncoders();
while (driveForward(encoderInchesToCounts(35), 75, false) != 1){}//12
delay(250);
while(driveBackward(encoderInchesToCounts(34.5), 25,true) != 1);//reverse from cap
delay(250);
resetEncoders();
elevate(0);
elevate(1);
while(turnRight(400,25,true) != 1){
  elevate(6);
}
while (!elevate(6)); // wait for done
//500
 delay(250);
// resetEncoders();
shootBall(1);
while(shootBall(0) != 1);
delay(40);
elevate(0);
elevate(4);
while(elevate(6) != 1);
delay(40);
shootBall(1);
while(shootBall(0) != 1);
}