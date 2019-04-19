#include "robot.h"
#include "main.h"

void frontauton1()
{

  static int state = 0;
  static int shootballstate = 0;
  while(state != 10) {
  switch(state)
  {
    case 0:
            intakeOn(false);  //turns intake on
            if (driveForward(encoderInchesToCounts(40), 75, true) == 1) {state = 1;}//drive to cap
            break;
    case 1:
            pros::delay(250);//wait for ball to enter mechanism
            intakeOff();//turn off intake
            if (driveBackward(encoderInchesToCounts(12), 50,true) == 1){state = 2;};//reverse from cap
            break;
    case 2:
            if( driveBackward(encoderInchesToCounts(28), 50,true) == 1){state = 3;}
            break;

    case 3:
            if( turnRight(800,50,true) == 1){state = 4;}
                break;
    case 4:
            if (driveForward(encoderInchesToCounts(12), 100, true) == 1) {state = 5;}
            break;
    case 5:
            shootballstate = shootBall(0);
            if (shootballstate == 1) {state = 6;}
            break;
    case 6:
            if( driveBackward(encoderInchesToCounts(40), 50, true) == 1) {state = 7;}
            break;
    case 7:
            shootballstate = shootBall(0);
            if (shootballstate == 1) {state = 8;}
            break;
    case 8:
            if( turnLeft(800,50,true) == 1){state = 9;}
            break;
    case 9:
            //platformpresentblue();
            state = 10;
            break;


    }
  }
}
