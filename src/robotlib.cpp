// #include "main.h"
#include "robot.h"
#include "robot_gui.h"

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
bool launcherActive = false;
 int controlr = 0;
bool reversecontrols = false;
char controllertext[14];
bool halfspeed;
int changespeed;
int swirlstate;
pros::ADILineSensor ls(LINE_SENSOR_PORT);
pros::ADILineSensor ls2(LINE_SENSOR_PORT2);

//Class instances for controller and motors
pros::Controller controller(pros::E_CONTROLLER_MASTER);
pros::Motor leftDriveMotor1(LEFT_DRIVE_MOTOR_1PORT);
pros::Motor rightDriveMotor1(RIGHT_DRIVE_MOTOR_1PORT);
pros::Motor launchMotor(LAUNCH_MOTOR_PORT);
pros::Motor wristMotor(WRIST_MOTOR_PORT);
pros::Motor liftMotor(LIFT_MOTOR_PORT);
pros::Motor ballIntakeMotor(BALL_INTAKE_MOTOR_PORT);
pros::Motor leftDriveMotor2(LEFT_DRIVE_MOTOR2_PORT);
pros::Motor rightDriveMotor2(RIGHT_DRIVE_MOTOR_2PORT);

void motorSetup()
{
  //set encoder units for autonomous actions
  leftDriveMotor1.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);
  rightDriveMotor1.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);
  launchMotor.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);
  wristMotor.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);
  liftMotor.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);
  ballIntakeMotor.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);
//set gearsets for motors
leftDriveMotor1.set_gearing(pros::E_MOTOR_GEARSET_18);
rightDriveMotor1.set_gearing(pros::E_MOTOR_GEARSET_18);
launchMotor.set_gearing(pros::E_MOTOR_GEARSET_36);
wristMotor.set_gearing(pros::E_MOTOR_GEARSET_18);
liftMotor.set_gearing(pros::E_MOTOR_GEARSET_36);
ballIntakeMotor.set_gearing(pros::E_MOTOR_GEARSET_18);

//sets braking mode so that any attempt to stop will occur immediately
leftDriveMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
rightDriveMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
launchMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
wristMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
ballIntakeMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}
void updateInfoScreen()
{
  info_printf(1,"LeftDrive:%d",leftDriveMotor1.get_position());
  info_printf(2,"RightDrive:%d",rightDriveMotor1.get_position());
  info_printf(3,"Wrist:%d",wristMotor.get_position());
  info_printf(4,"Lift:%d",liftMotor.get_position());
  filterCockedSensor();
}
void updateControllerLcd()
{
  controller.print(0, 0, "Intr:%d Spd:%d",intakeReverse,halfspeed);//updates controller LCD with the state of toggles
}
//moves drivetrain
void driveControl()
{

  static uint8_t drvactivelaststate = 0;
static uint8_t drvrevlaststate = 0;
  if (changespeed == 1 && drvactivelaststate != 1)
  {
    halfspeed = !halfspeed;//toggles intake active
    updateControllerLcd();
  }
  if (controlr == 1 && drvrevlaststate != 1)
  {
    reversecontrols = !reversecontrols;
  }
  if (reversecontrols)
  {
    leftDrivePower = -leftDrivePower;
    rightDrivePower = -rightDrivePower;
  }
  if (!halfspeed){
  leftDriveMotor1.move(leftDrivePower);//sets drive power of left motor
  rightDriveMotor1.move(rightDrivePower);//sets drive power of right motor
  leftDriveMotor2.move(leftDrivePower);
  rightDriveMotor2.move(rightDrivePower);
  } else {
  leftDriveMotor1.move(leftDrivePower *.5);//sets drive power of left motor to half
  rightDriveMotor1.move(rightDrivePower*.5);//sets drive power of right motor to half
  leftDriveMotor2.move(leftDrivePower * .5);
  rightDriveMotor2.move(rightDrivePower * .5);
  }
  drvactivelaststate = changespeed;
  drvrevlaststate = controlr;
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
	 ballIntakeSetDir = readIntakeReverseButton(DIGITAL_UP);
	 intake = readIntakeButton(DIGITAL_X);
   changespeed = readHalfSpeedButton(DIGITAL_LEFT);
   controlr = readReverseControlsButton(DIGITAL_RIGHT);
}
//moves lift
void liftControl()
{
  if (liftMotor.get_position() >= 0)
  {
    liftMotor.move(50);
  }

  if (liftup && liftdown) {
    liftMotor.move(0);//prevents motor from oscillating
  }
  else if (liftup == 1 && liftMotor.get_position() < -900) {
    liftMotor.move(-75);//drives lift up
  }
  else if (liftup == 1) {
    liftMotor.move(-100);//drives lift up
  }
	else if (liftdown == 1) {
    liftMotor.move(100);//drives lift down
  }
  else {
    liftMotor.move(0);//stop motor
  }
}

void wristControl()
{
  if (wristleft && wristright) {
    wristMotor.move(0);//stop motor from oscillating
  }
  else if (wristleft == 1){
    wristMotor.move(100); // turn wrist left
  }
  else if (wristright == 1) {
    wristMotor.move(-100);//turn wrist right
  }
  else {
    wristMotor.move(0);//turn motor off
  }
}

void launcherControl()
{
  info_printf(3,"LS LAuncher:%d",ls2.get_value());
  info_printf(4,"Ball Detect:%d",ls.get_value());
    //if (launchA == 1) {launcherActive = !launcherActive; pros::delay(100);}
    //if (launcherActive) {launchMotor.move(-127);} else {launchMotor.move(0);}
    //if (ls.get_value() < 200 && ls2.get_value() < 800){pros::lcd::print(2,"Interlock Released");} else {pros::lcd::print(2,"Interlock Engaged");}
    if(launchA == 1) {
      launchMotor.move(-127);//cock launcher
    } else {
      launchMotor.move(0);//stop cocking
    }
    if(launchB == 1) {
      launchMotor.move(40);//reverse launcher in case of jam
    }
}

void ballIntakeControl()
{

  static uint8_t intactivelaststate = 0;
  static uint8_t intrevlaststate = 0;
  if (intake == 1 && intactivelaststate != 1)
  {
    intakeActive = !intakeActive;//toggles intake active
  }

  if (ballIntakeSetDir == 1 && intrevlaststate != 1) {
    intakeReverse = !intakeReverse;//toggles intake reverse
    updateControllerLcd();
  }
  else
  //
	if(intakeActive && intakeReverse) {
    ballIntakeMotor.move(-127);//runs ball intake in reverse
  } else if (intakeActive && !intakeReverse) {
    ballIntakeMotor.move(127); //runs ball intake normally
  } else {
    ballIntakeMotor.move(0);//stops ball intake
  }
  intactivelaststate = intake;
  intrevlaststate = ballIntakeSetDir;
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

int readIntakeButton(pros::controller_digital_e_t button)
{
  static int buttonvalue = 0;
    buttonvalue = (buttonvalue << 1) | controller.get_digital(button);
    if ((buttonvalue & 0x0F) == 0x0F)
    {
      return 1;
    }
    else
    {
      return 0;
    }
}

int readIntakeReverseButton(pros::controller_digital_e_t button)
{
  static int buttonvalue = 0;
    buttonvalue = (buttonvalue << 1) | controller.get_digital(button);//effectively appends current value to last value.
    if ((buttonvalue & 0x0F) == 0x0F)//if the button value and the mask = the mask
    {
      return 1;//button was pressed
    }
    else
    {
      return 0;//button was not pressed
    }
}

int readReverseControlsButton(pros::controller_digital_e_t button)
{
  static int buttonvalue = 0;
    buttonvalue = (buttonvalue << 1) | controller.get_digital(button);//effectively appends current value to last value.
    if ((buttonvalue & 0x0F) == 0x0F)//if the button value and the mask = the mask
    {
      return 1;//button was pressed
    }
    else
    {
      return 0;//button was not pressed
    }
}

int readHalfSpeedButton(pros::controller_digital_e_t button)
{
  static int buttonvalue = 0;
    buttonvalue = (buttonvalue << 1) | controller.get_digital(button);//effectively appends current value to last value.
    if ((buttonvalue & 0x0F) == 0x0F)//if the button value and the mask = the mask
    {
      return 1;//button was pressed
    }
    else
    {
      return 0;//button was not pressed
    }
}
