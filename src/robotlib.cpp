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
pros::ADILineSensor ls(LINE_SENSOR_PORT);
pros::ADIPotentiometer autopot('e');
pros::ADILineSensor ls2(LINE_SENSOR_PORT2);

//Class instances for controller and motors
pros::Controller controller(pros::E_CONTROLLER_MASTER);
pros::Motor leftDriveMotor(LEFT_DRIVE_MOTOR_PORT);
pros::Motor rightDriveMotor(RIGHT_DRIVE_MOTOR_PORT);
pros::Motor launchMotor(LAUNCH_MOTOR_PORT);
pros::Motor wristMotor(WRIST_MOTOR_PORT);
pros::Motor liftMotor(LIFT_MOTOR_PORT);
pros::Motor ballIntakeMotor(BALL_INTAKE_MOTOR_PORT);

void motorSetup()
{
  //set encoder units for autonomous actions
  leftDriveMotor.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);
  rightDriveMotor.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);
  launchMotor.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
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


//sets braking mode so that any attempt to stop will occur immediately
leftDriveMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
rightDriveMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
launchMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
wristMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
ballIntakeMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
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
  pros::lcd::print(3,"LS LAuncher:%d",ls2.get_value());
  pros::lcd::print(4,"Ball Detect:%d",ls.get_value());
    if (ls.get_value() < 200 && ls2.get_value() < 800){pros::lcd::print(2,"Interlock Released");} else {pros::lcd::print(2,"Interlock Engaged");}
    if(launchA == 1) {launchMotor.move(-127);} else {launchMotor.move(0);}
    if(launchB == 1) {launchMotor.move(40);}
}

void ballIntakeControl()
{
  if (intake == 1) {intakeActive = !intakeActive; pros::delay(100);}
  if (ballIntakeSetDir == 1) {intakeReverse = !intakeReverse; pros::delay(100);updateControllerLcd();}
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
}
