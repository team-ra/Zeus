#include "main.h"
#include "robot.h"

extern pros::Motor leftDriveMotor;
extern pros::Motor rightDriveMotor;
extern pros::Motor launchMotor;
extern pros::Motor wristMotor;
extern pros::Motor liftMotor;
extern pros::Motor ballIntakeMotor;

int encoderInchesToCounts(float inches)
{
  int counts = 900/(4*3.14159265359);
  return counts;
}
void driveForward(int counts,int power)
{
  leftDriveMotor.move(power);
  rightDriveMotor.move(-power);
  while(leftDriveMotor.get_position() <= counts && rightDriveMotor.get_position() <= counts);
  leftDriveMotor.move(0);
  rightDriveMotor.move(0);
}

void driveBackward(int counts)
{

}

void turnLeft(int counts)
{

}

void turnRight(int counts)
{

}
