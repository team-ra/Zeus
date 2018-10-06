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
  int counts;
  auto gearset = leftDriveMotor.get_gearing();
  if (gearset == pros::E_MOTOR_GEARSET_36)
  {
      counts = inches * (1800/(4*3.14159265359));
  }
  else if (gearset == pros::E_MOTOR_GEARSET_18)
  {
      counts = inches * (900/(4*3.14159265359));
  }
  else if (gearset == pros::E_MOTOR_GEARSET_06)
  {
     counts = inches * (300/(4*3.14159265359));
  }
  return counts;
}
void driveForward(int counts,int power)
{
  leftDriveMotor.move_relative(counts,power);
  rightDriveMotor.move_relative(-counts,-power);
  while(leftDriveMotor.get_position() <= counts && rightDriveMotor.get_position() <= counts);
  leftDriveMotor.tare_position();
  rightDriveMotor.tare_position();
}

void driveBackward(int counts,int power)
{
  leftDriveMotor.move_relative(-counts,power);
  rightDriveMotor.move_relative(counts,-power);
  while(leftDriveMotor.get_position() <= -counts && rightDriveMotor.get_position() <= -counts);
  leftDriveMotor.tare_position();
  rightDriveMotor.tare_position();
}

void turnLeft(int counts)
{

}

void turnRight(int counts)
{

}
