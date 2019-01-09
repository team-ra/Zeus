#include "robot.h"
#include "main.h"

void frontauton1()
{
  static int state = 0;
  static int shootballstate = 0;

  while(state != 11){
    switch(state)
  {
    case 0:
            intakeOn(false);  //turns intake on
            driveForward(encoderInchesToCounts(11),25,true);
            driveForward(encoderInchesToCounts(22),50,true);
            // driveForward(encoderInchesToCounts(22), 75, true);//drive to cap
            //driveForward(encoderInchesToCounts(44), 50, true);//drive to cap
            state = 1;
            break;
    case 1:
            pros::delay(500);//wait for ball to enter mechanism
            driveBackward(encoderInchesToCounts(12), 50,true);//reverse from cap
            state = 2;
            break;
    case 2:
            // driveBackward(encoderInchesToCounts(4),25,true);
            // driveBackward(encoderInchesToCounts(4),50,true);
            // driveBackward(encoderInchesToCounts(18),75,true);
            driveBackward(encoderInchesToCounts(26),50,true);
            intakeOff();//turn off intake
            state = 3;
            break;

    case 3:
            turnRight(750,50,true);
            state = 5;
            break;
    case 4:
            driveForward(encoderInchesToCounts(10), 100, true);
            state = 5;
            break;
    case 5:
            shootballstate = shootBall();
            if (shootballstate == 1) {state = 6;}
            break;
    case 6:
            driveForward(encoderInchesToCounts(42),100,true);
            state = 7;
            break;
    case 7:
            driveBackward(encoderInchesToCounts(62), 100, true);
            state= 8;
            break;
    case 8:
            shootballstate = shootBall();
            if (shootballstate == 1) {state = 9;}
            break;
    case 9:
            turnLeft(800,50,true);
            state = 10;
            break;
    case 10:
            platformpresentblue();
            state = 11;
            break;


    }
  }
}
