#include "main.h"
#include "robot.h"
using namespace pros::literals;
extern pros::Motor leftDriveMotor;
extern pros::Motor rightDriveMotor;
extern pros::Motor launchMotor;
extern pros::Motor wristMotor;
extern pros::Motor liftMotor;
extern pros::Motor ballIntakeMotor;
extern pros::ADIPotentiometer autopot;
extern pros::ADILineSensor ls2;
extern pros::ADILineSensor ls;
void  (*autonfuncs[])() = {&auton1,&auton2,auton3,auton4,auton5,auton6,auton7,auton8,auton9,auton10};
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
void driveForward(int counts,int power,bool zeromotors)
{
  leftDriveMotor.move_relative(counts,power);
  rightDriveMotor.move_relative(-counts,-power);
  while(leftDriveMotor.get_position() <= counts && rightDriveMotor.get_position() <= counts);
  if(zeromotors){
    leftDriveMotor.tare_position();
    rightDriveMotor.tare_position();
  }
}

void driveBackward(int counts,int power,bool zeromotors)
{
  leftDriveMotor.move_relative(-counts,-power);
  rightDriveMotor.move_relative(counts,power);
  while(leftDriveMotor.get_position() >= -counts && rightDriveMotor.get_position() <= counts);
  if(zeromotors){
    leftDriveMotor.tare_position();
    rightDriveMotor.tare_position();
  }
}

void turnLeft(int counts,int power,bool zeromotors)
{
  leftDriveMotor.move_relative(-counts,-power);
  rightDriveMotor.move_relative(-counts,power);
  while(leftDriveMotor.get_position() <= -counts && rightDriveMotor.get_position() <= -counts);
  if(zeromotors){
    leftDriveMotor.tare_position();
    rightDriveMotor.tare_position();
  }
}

void turnRight(int counts,int power,bool zeromotors)
{
  leftDriveMotor.move_relative(-counts,power);
  rightDriveMotor.move_relative(counts,-power);
  while(leftDriveMotor.get_position() <= -counts && rightDriveMotor.get_position() <= -counts);
  if(zeromotors){
    leftDriveMotor.tare_position();
    rightDriveMotor.tare_position();
  }
}

int setAutonMode()
{
  int mode = 0;
  unsigned int potvalue = autopot.get_value();
  if (potvalue <= 12) {mode = 0;}
  else if (potvalue > 12 && potvalue <= 115) {mode = 1;}
  else if (potvalue > 115 && potvalue <= 695) {mode = 2;}
  else if (potvalue > 695 && potvalue <= 1182) {mode = 3;}
  else if (potvalue > 1182 && potvalue <= 1630) {mode = 4;}
  else if (potvalue > 1630 && potvalue <= 2126) {mode = 5;}
  else if (potvalue > 2126 && potvalue <= 2624) {mode = 6;}
  else if (potvalue > 2624 && potvalue <= 3200) {mode = 7;}
  else if (potvalue > 3200 && potvalue <= 3830) {mode = 8;}
  else if (potvalue > 3830 && potvalue <= 4095) {mode = 9;}
  return mode;
}

void startauto(int mode)
{
  pros::lcd::print(2,"%d",mode);
(*autonfuncs[mode])();
}

void shootBall()
{
  launchMotor.move(-127);
  if (ls2.get_value() <= 800) {pros::lcd::print(5,"Under");}
  launchMotor.move(0);
}

void waitForSensorInit(int timeoutmillis)
{
  while(ls.get_value() <= 100 && ls2.get_value() <= 100);
}
