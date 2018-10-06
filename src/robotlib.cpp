#include "main.h"
#include "robot.h"

using namespace pros::literals;

//controller and motor state variables
int leftDrivePower;
int rightDrivePower;
int liftup;
int liftdown;
int wristleft;
int wristright;
int launchA;
int launchB;
int ballIntakeSetDir;
int ballIntakeSetOut;
int intake;
bool intakeReverse;
bool intakeActive = false;
char controllertext[14];
bool halfspeed;
int changespeed;
int swirlstate;


//Class instances for controller and motors
pros::Controller controller(pros::E_CONTROLLER_MASTER);
pros::Motor leftDriveMotor(1);
pros::Motor rightDriveMotor(2);
pros::Motor launchMotor(3);
pros::Motor wristMotor(4);
pros::Motor liftMotor(5);
pros::Motor ballIntakeMotor(6);
void motorSetup()
{
  //set encoder units for autonomous actions
  leftDriveMotor.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);
  rightDriveMotor.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);
  launchMotor.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);
  wristMotor.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);
  liftMotor.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);
  ballIntakeMotor.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);
//set gearsets for motors
leftDriveMotor.set_gearing(pros::E_MOTOR_GEARSET_18);
rightDriveMotor.set_gearing(pros::E_MOTOR_GEARSET_18);
launchMotor.set_gearing(pros::E_MOTOR_GEARSET_18);
wristMotor.set_gearing(pros::E_MOTOR_GEARSET_18);
liftMotor.set_gearing(pros::E_MOTOR_GEARSET_18);
ballIntakeMotor.set_gearing(pros::E_MOTOR_GEARSET_18);

}

void updateControllerLcd()
{
  controller.print(0, 0, "Intr:%d Spd:%d",intakeReverse,halfspeed);
}
//moves drivetrain
void driveControl()
{
  if (changespeed == 1) {halfspeed = !halfspeed; pros::delay(250);updateControllerLcd();}
  if (!halfspeed){
  leftDriveMotor.move(leftDrivePower);
  rightDriveMotor.move(rightDrivePower);
  } else {
  leftDriveMotor.move(leftDrivePower *.5);
  rightDriveMotor.move(rightDrivePower*.5);
  }
}
//set controller states
void readJoystick()
{
  leftDrivePower = controller.get_analog(ANALOG_LEFT_Y);
  rightDrivePower = -controller.get_analog(ANALOG_RIGHT_Y);
   liftup = controller.get_digital(DIGITAL_R1);
	 liftdown = controller.get_digital(DIGITAL_R2);
	 wristleft = controller.get_digital(DIGITAL_L1);
	 wristright = controller.get_digital(DIGITAL_L2);
	 launchA = controller.get_digital(DIGITAL_A);
	 launchB = controller.get_digital(DIGITAL_B);
	 ballIntakeSetDir = controller.get_digital_new_press(DIGITAL_UP);
	 //ballIntakeSetOut = controller.get_digital(DIGITAL_DOWN);
	 intake = controller.get_digital(DIGITAL_X);
   changespeed = controller.get_digital_new_press(DIGITAL_LEFT);

}
//moves lift
void liftControl()
{
  if (liftup && liftdown) {liftMotor.move(0);}
  else if (liftup == 1)   {liftMotor.move(100);}
	else if (liftdown == 1) {liftMotor.move(-100);}
  else {liftMotor.move(0);}
}

void wristControl()
{
  if (wristleft && wristright) {wristMotor.move(0);}
  else if (wristleft == 1)   {wristMotor.move(100);}
  else if (wristright == 1) {wristMotor.move(-100);}
  else {wristMotor.move(0);}
}

void launcherControl()
{
  	if(launchA == 1 || launchB == 1) {launchMotor.move(127);} else {launchMotor.move(0);}
}

void ballIntakeControl()
{
  if (intake == 1) {intakeActive = !intakeActive; pros::delay(250);}
  if (ballIntakeSetDir == 1) {intakeReverse = !intakeReverse; pros::delay(250);updateControllerLcd();}
  // if(ballIntakeSetIn == 1 && ballIntakeSetOut != 1) { intakeReverse = false;}
	// if(ballIntakeSetOut == 1 && ballIntakeSetIn != 1) { intakeReverse = true;}
	if(intakeActive && intakeReverse) {ballIntakeMotor.move(-127);} else if (intakeActive && !intakeReverse) {ballIntakeMotor.move(127);} else {ballIntakeMotor.move(0);}
}
//provides reassurance of operation
void swirl()
{
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
  pros::delay(250);
}
