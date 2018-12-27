#include "robot.h"
#include "main.h"

void frontauton1()
{
  static int state = 0;
  static int shootballstate = 0;
  switch(state)
  {
    case 0:
            intakeOn(false);  //turns intake on
            driveForward(encoderInchesToCounts(40), 50, true);//drive to cap
            state = 1;
            break;
    case 1:
            pros::delay(250);//wait for ball to enter mechanism
            intakeOff();//turn off intake
            driveBackward(encoderInchesToCounts(12), 50,true);//reverse from cap
            state = 2;
            break;
    case 2:
            driveBackward(encoderInchesToCounts(28), 50,true);
            state = 3;
            break;

    case 3:
            turnRight(800,50,true);
            state = 4;
            break;
    case 4:
            driveForward(encoderInchesToCounts(12), 100, true);
            state = 5;
            break;
    case 5:
            shootballstate = shootBall();
            if (shootballstate == 1) {state = 6;}
            break;
    case 6:
            driveBackward(encoderInchesToCounts(40), 50, true);
            state= 7;
            break;
    case 7:
            shootballstate = shootBall();
            if (shootballstate == 1) {state = 8;}
            break;
    case 8:
            turnLeft(800,50,true);
            state = 9;
            break;
    case 9:
            platformpresentblue();
            break;


  }
}
