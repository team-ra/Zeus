#include "robot.h"
// ///externs for accessing motors
// extern pros::Motor leftDriveMotor1;
//
// extern pros::Motor leftDriveMotor2;
// extern pros::Motor rightDriveMotor2;
// /// State Variables
// int drivedist = 0;
// int drivepower = 0;
// int backdrivedist = 0;
// int backdrivepower = 0;
// int leftturndist = 0;
// int rightturndist = 0;
// int leftturnpower = 0;
// int rightturnpower = 0;
//
// int speed = 0;
//
// void driveForwardAsync(void* param)
// {
//    leftDriveSet(getForwardDrivePwr());
//    rightDriveSet(getForwardDrivePwr());
//    if (leftDriveMotor1.get_position() > getForwardDriveDist())
//    {
//        setForwardDrivePwr(0);
//        leftDriveSet(getForwardDrivePwr());
//        rightDriveSet(getForwardDrivePwr());
//    }
// }
//
// void setBackDriveDist(int dist)
// {
//  backdrivedist = dist;
// }
//
// void setBackDrivePwr(int pwr)
// {
// backdrivepower = pwr;
// }
//
// void setForwardDriveDist(int dist)
// {
//  drivedist = dist;
// }
//
// void setForwardDrivePwr(int pwr)
// {
//  drivepower = pwr;
// }
//
// int getBackDriveDist()
// {
//  return backdrivedist;
// }
//
// int getBackDrivePwr()
// {
//  return backdrivepower;
// }
//
// int getForwardDriveDist()
// {
//  return drivedist;
// }
//
// int getForwardDrivePwr()
// {
//  return drivepower;
// }
//
// void setLeftTurnDist(int dist)
// {
//  leftturndist = dist;
// }
//
// void setRightTurnDist(int dist)
// {
//  rightturndist = dist;
// }
//
// void setLeftTurnPwr(int pwr)
// {
//  leftturnpower = pwr;
// }
//
// void setRightTurnPwr(int pwr)
// {
//  rightturnpower = pwr;
// }
//
// int getLeftTurnDist()
// {
//  return leftturndist;
// }
//
// int getLeftTurnPwr()
// {
//  return leftturnpower;
// }
//
// int getRightTurnDist()
// {
//  return rightturndist;
// }
//
// int getRightTurnPwr()
// {
//  return rightturnpower;
// }
//
// void driveBackwardAsync(void* param)
// {
//
//  leftDriveSet(-getBackDrivePwr());
//  rightDriveSet(-getBackDrivePwr());
//  if (leftDriveMotor1.get_position() < getBackDriveDist())
//  {
//      setForwardDrivePwr(0);
//      leftDriveSet(getBackDrivePwr());
//      rightDriveSet(getBackDrivePwr());
//  }
//
// }
//
// void turnLeftAsync(void* param)
// {
//    leftDriveSet(-getLeftTurnPwr());
//    rightDriveSet(getLeftTurnPwr());
//    if (leftDriveMotor1.get_position() < getLeftTurnDist())
//    {
//        setLeftTurnPwr(0);
//        leftDriveSet(getLeftTurnPwr());
//        rightDriveSet(getLeftTurnPwr());
//    }
// }
//
// void turnRightAsync(void* param)
// {
//    leftDriveSet(drivepower);
//    rightDriveSet(-drivepower);
//    if (leftDriveMotor1.get_position() > getRightTurnDist())
//    {
//        setForwardDrivePwr(0);
//        leftDriveSet(drivepower);
//        rightDriveSet(drivepower);
//    }
// }
// void taskManager(int action, pros::Task task)
// {
//    if (action == 0) { task.resume();}
//    if (action == 1) { task.suspend(); }
//    if (action == 2) { task.remove(); }
//    else {}
// }
//
// pros::Task taskCreator(pros::task_fn_t func, char* name)
// {
//  Task t = new Task(func,nullptr,TASK_PRIORITY_DEFAULT,TASK_STACK_DEPTH_DEFAULT,name);
//  return t;
// }
//
// void getSpeed() {
//   static int lastcounts = 0;
//   int a = leftDriveMotor2.get_position();
//   speed = leftDriveMotor2.get_position() - lastcounts;
//   lastcounts = a;
// }
//
/*\brief
* \details gradually increases to desired power
*/
void AccelerateForward(int power)//gradually increase power to avoid sudden jerking or steering movements
{
  int i;
  for (i = 0; i < 1; i++)
  {
    leftDriveSet(10);
    rightDriveSet(10);
    pros::delay(20);
    if (power <= 10) {break;}

    rightDriveSet(20);
    leftDriveSet(20);
    pros::delay(20);
    if (power <= 20) {break;}

    leftDriveSet(30);
    rightDriveSet(30);
    pros::delay(20);
    if (power <= 30) {break;}

    rightDriveSet(40);
    leftDriveSet(40);
    pros::delay(20);
    if (power <= 40) {break;}

    leftDriveSet(50);
    rightDriveSet(50);
    pros::delay(20);
    if (power <= 50) {break;}

    leftDriveSet(60);
    rightDriveSet(60);
    pros::delay(20);
    if (power <= 60) {break;}

    leftDriveSet(70);
    rightDriveSet(70);
    pros::delay(20);
    if (power <= 70) {break;}

    leftDriveSet(80);
    rightDriveSet(80);
    pros::delay(20);
    if (power <= 80) {break;}

    leftDriveSet(90);
    rightDriveSet(90);
    pros::delay(20);
    if (power <= 90) {break;}

    leftDriveSet(100);
    rightDriveSet(100);
    pros::delay(20);
    if (power <= 100) {break;}

    leftDriveSet(110);
    rightDriveSet(110);
    pros::delay(20);
    if (power <= 110) {break;}

    leftDriveSet(120);
    rightDriveSet(120);
    pros::delay(20);
  }
}
/*\brief
* \details gradually increases to desired power
*/
void AccelerateBackward(int power)//gradually increase power to avoid sudden jerking or steering movements
{
  int i;
  for (i = 0; i < 1; i++)
  {
    leftDriveSet(-10);
    rightDriveSet(-10);
    pros::delay(20);
    if (power >= -10) {break;}

    rightDriveSet(-20);
    leftDriveSet(-20);
    pros::delay(20);
    if (power >= -20) {break;}

    leftDriveSet(-30);
    rightDriveSet(-30);
    pros::delay(20);
    if (power >= -30) {break;}

    rightDriveSet(-40);
    leftDriveSet(-40);
    pros::delay(20);
    if (power >= -40) {break;}

    leftDriveSet(-50);
    rightDriveSet(-50);
    pros::delay(20);
    if (power >= -50) {break;}

    leftDriveSet(-60);
    rightDriveSet(-60);
    pros::delay(20);
    if (power >= -60) {break;}

    leftDriveSet(-70);
    rightDriveSet(-70);
    pros::delay(20);
    if (power >= -70) {break;}

    leftDriveSet(-80);
    rightDriveSet(-80);
    pros::delay(20);
    if (power >= -80) {break;}

    leftDriveSet(-90);
    rightDriveSet(-90);
    pros::delay(20);
    if (power >= -90) {break;}

    leftDriveSet(-100);
    rightDriveSet(-100);
    pros::delay(20);
    if (power >= -100) {break;}

    leftDriveSet(-110);
    rightDriveSet(-110);
    pros::delay(20);
    if (power >= -110) {break;}

    leftDriveSet(-120);
    rightDriveSet(-120);
    pros::delay(20);
  }
}

// void drivestraightBack(int dmp)//add or subtract power to stay on course when driving long distances but with the logic flipped since we are going backwards
// {
//
//   int leftencval = -leftDriveMotor2.get_position();//making values positive for math
//   int rightencval = -rightDriveMotor2.get_position();//making values positive for math
//   pros::delay(30);
//     //go straight algorithm
//       static int offset = 0;
//       if ( (rightencval - leftencval) >= 15  )//if off a lot, compenate accordingly
//       {
//         offset += 10;
//       }
//
//       else if ( (rightencval - leftencval) >= 10  )//if off more, compenate accordingly
//       {
//         offset += 5;
//       }
//
//       else if ( (rightencval - leftencval) >= 5  )//if off a little, compenate accordingly
//       {
//         offset += 2;
//       }
//
//        else if ( (rightencval - leftencval) <= -15  )//if off a lot, compenate accordingly
//       {
//         offset -= 10;
//       }
//
//       else if ( (rightencval - leftencval) <= -10  )//if off more, compenate accordingly
//       {
//         offset -= 5;
//       }
//
//       else if ( (rightencval - leftencval) <= -5  )//if off a little, compenate accordingly
//       {
//         offset -= 2;
//       }
//
//
//     //  if ( (leftencval == rightencval) ) //reset offset
//     //  {
//     //    offset = 0;
//     //  }
//
//       if ( (offset > 500))
//       {
//         offset = 500;
//       }
//       else if (offset < -500)
//       {
//         offset = -500;
//       }
//     rightDriveSet(dmp-offset/50);//apply offset
//     pros::delay(30);
//
// }



extern pros::Controller controller;
char line[16];
int linenum = 0;
bool updateRequested = false;

pros::Task swirlTask(swirl,(void*)"shfslhf",TASK_PRIORITY_DEFAULT,TASK_STACK_DEPTH_DEFAULT,"Swirl Task");
pros::Task updateLcdTask(updateLcd,(void*)nullptr,TASK_PRIORITY_DEFAULT,TASK_STACK_DEPTH_DEFAULT,"Update LCD Task");

void swirl(void* param)
{
  static int swirlstate = 0;

    if (swirlstate == 0 || swirlstate == 4)
    {
        controller.print(1,12,"-");
    }
    else if (swirlstate == 1 || swirlstate == 5)
    {
        controller.print(1,12,"\\");
    }
    else if (swirlstate == 2 || swirlstate == 6)
    {
        controller.print(1,12,"|");
    }
    else if (swirlstate == 3 || swirlstate == 7)
    {
        controller.print(1,12,"/");
    }
    else
    {
        swirlstate = 0;
    }
    swirlstate++;
    pros::delay(50);
}

void updateLcd(void* param) {
    if (updateRequested) {
        controller.print(linenum, 0, line);
    }
}

void updateLineData(char* data) {
    sprintf(line,"%s",data);
}

void updateLineNumber(int linenumber) {
    linenum  = linenumber;
}

void requestLcdUpdate() {
    updateRequested = true;
}
