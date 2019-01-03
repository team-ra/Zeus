#include "robot.h"
///externs for accessing motors
extern pros::Motor leftDriveMotor1;
/// State Variables
int drivedist = 0;
int drivepower = 0;
int backdrivedist = 0;
int backdrivepower = 0;
int leftturndist = 0;
int rightturndist = 0;
int leftturnpower = 0;
int rightturnpower = 0;

void driveForwardAsync(void* param)
{
   leftDriveSet(getForwardDrivePwr());
   rightDriveSet(getForwardDrivePwr());
   if (leftDriveMotor1.get_position() > getForwardDriveDist())
   {
       setForwardDrivePwr(0);
       leftDriveSet(getForwardDrivePwr());
       rightDriveSet(getForwardDrivePwr());
   }
}

void setBackDriveDist(int dist)
{
 backdrivedist = dist;
}

void setBackDrivePwr(int pwr)
{
backdrivepower = pwr;
}

void setForwardDriveDist(int dist)
{
 drivedist = dist;
}

void setForwardDrivePwr(int pwr)
{
 drivepower = pwr;
}

int getBackDriveDist()
{
 return backdrivedist;
}

int getBackDrivePwr()
{
 return backdrivepower;
}

int getForwardDriveDist()
{
 return drivedist;
}

int getForwardDrivePwr()
{
 return drivepower;
}

void setLeftTurnDist(int dist)
{
 leftturndist = dist;
}

void setRightTurnDist(int dist)
{
 rightturndist = dist;
}

void setLeftTurnPwr(int pwr)
{
 leftturnpower = pwr;
}

void setRightTurnPwr(int pwr)
{
 rightturnpower = pwr;
}

int getLeftTurnDist()
{
 return leftturndist;
}

int getLeftTurnPwr()
{
 return leftturnpower;
}

int getRightTurnDist()
{
 return rightturndist;
}

int getRightTurnPwr()
{
 return rightturnpower;
}

void driveBackwardAsync(void* param)
{

 leftDriveSet(-getBackDrivePwr());
 rightDriveSet(-getBackDrivePwr());
 if (leftDriveMotor1.get_position() < getBackDriveDist())
 {
     setForwardDrivePwr(0);
     leftDriveSet(getBackDrivePwr());
     rightDriveSet(getBackDrivePwr());
 }

}

void turnLeftAsync(void* param)
{
   leftDriveSet(-getLeftTurnPwr());
   rightDriveSet(getLeftTurnPwr());
   if (leftDriveMotor1.get_position() < getLeftTurnDist())
   {
       setLeftTurnPwr(0);
       leftDriveSet(getLeftTurnPwr());
       rightDriveSet(getLeftTurnPwr());
   }
}

void turnRightAsync(void* param)
{
   leftDriveSet(drivepower);
   rightDriveSet(-drivepower);
   if (leftDriveMotor1.get_position() > getRightTurnDist())
   {
       setForwardDrivePwr(0);
       leftDriveSet(drivepower);
       rightDriveSet(drivepower);
   }
}
void taskManager(int action, pros::Task task)
{
   if (action == 0) { task.resume();}
   if (action == 1) { task.suspend(); }
   if (action == 2) { task.remove(); }
   else {}
}

pros::Task taskCreator(task_fn_t func, char* name)
{
 Task t = new Task(func,nullptr,TASK_PRIORITY_DEFAULT,TASK_STACK_DEPTH_DEFAULT,name);
 return t;
}
