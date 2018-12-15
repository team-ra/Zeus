// #include "main.h"
#include "robot.h"
#include "robot_gui.h"

using namespace pros::literals;

//controller,motor, and button variables. These are GLOBAL
///the left drive power
int leftDrivePower;
///the right drive power
int rightDrivePower;
///the result of checking for liftup button. 1 if pressed, else 0
int liftup;
///the result of checking for liftdown button 1 if pressed, else 0
int liftdown;
///the result of checking for wristleft button 1 if pressed, else 0
int wristleft;
///the result of checking for wristright button 1 if pressed, else 0
int wristright;
///the result of checking for shoot button 1 if pressed, else 0
int shoot;
///the result of checking for reverse shooter button 1 if pressed, else 0
int unjam;
///the result of checking for ball intake toggle button 1 if pressed, else 0
int ballIntakeSetDir;
///the result of checking for intake toggle button 1 if pressed, else 0
int intake;
///holds value of intake reverse bool 1 if pressed, else 0
bool intakeReverse;
///holds value of intake active bool 1 if active, else 0
bool intakeActive = false;
///the result of checking for reverse controls toggle button 1 if pressed, else 0
 int controlr = 0;
 ///holds value of intake reverse bool 1 if reversed, else 0
bool reversecontrols = false;
///holds the text to be written to line 0 of the joystick LCD
char line0[14];
///holds the text to be written to line 1 of the joystick LCD
char line1[14];
///holds value of half speed bool 1 if pressed, else 0
bool halfspeed;
///the result of checking for halfspeed button 1 if pressed, else 0
int changespeed;
///holds the state of the swirl animation
int swirlstate;

//Class instances for controller and motors
///the main joystick
pros::Controller controller(pros::E_CONTROLLER_MASTER);
/// The Back left drive motor
 pros::Motor leftDriveMotor1(LEFT_DRIVE_MOTOR_1PORT);
/// The Back right drive motor
 pros::Motor rightDriveMotor1(RIGHT_DRIVE_MOTOR_1PORT);
/// The Front left drive motor
 pros::Motor leftDriveMotor2(LEFT_DRIVE_MOTOR2_PORT);
/// The Front right drive motor
 pros::Motor rightDriveMotor2(RIGHT_DRIVE_MOTOR_2PORT);
/// The launcher motor
 pros::Motor launchMotor(LAUNCH_MOTOR_PORT);
/// The wrist motor
 pros::Motor wristMotor(WRIST_MOTOR_PORT);
/// The lift motor
 pros::Motor liftMotor(LIFT_MOTOR_PORT);
/// The ball intake motor
 pros::Motor ballIntakeMotor(BALL_INTAKE_MOTOR_PORT);
/// The ball present sensor
 pros::ADILineSensor ls2(COCKED_SENSOR_PORT);
/// The launcher cocked sensor
 pros::ADILineSensor ls(BALL_SENSOR_PORT);
///the platform tube detect sensor
pros::ADILineSensor ps(PLATFORM_SENSOR_PORT);
void motorSetup()
{
  //set encoder units for autonomous actions
  leftDriveMotor1.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS); //set encoder units to counts instead of degrees or revolutions
  rightDriveMotor1.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);//set encoder units to counts instead of degrees or revolutions
  leftDriveMotor2.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS); //set encoder units to counts instead of degrees or revolutions
  rightDriveMotor2.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);//set encoder units to counts instead of degrees or revolutions
  launchMotor.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);//set encoder units to counts instead of degrees or revolutions
  wristMotor.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);//set encoder units to counts instead of degrees or revolutions
  liftMotor.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);//set encoder units to counts instead of degrees or revolutions
  ballIntakeMotor.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);//set encoder units to counts instead of degrees or revolutions

//set gearsets for motors
leftDriveMotor1.set_gearing(pros::E_MOTOR_GEARSET_18);//high speed
rightDriveMotor1.set_gearing(pros::E_MOTOR_GEARSET_18);//high speed
leftDriveMotor2.set_gearing(pros::E_MOTOR_GEARSET_18);//high speed
rightDriveMotor2.set_gearing(pros::E_MOTOR_GEARSET_18);//high speed
launchMotor.set_gearing(pros::E_MOTOR_GEARSET_18);//high speed
wristMotor.set_gearing(pros::E_MOTOR_GEARSET_18);//high speed
liftMotor.set_gearing(pros::E_MOTOR_GEARSET_36);//torque
ballIntakeMotor.set_gearing(pros::E_MOTOR_GEARSET_18);//high speed

//sets braking mode
leftDriveMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);//forces motor to not apply braking when power is not applied
rightDriveMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);//forces motor to not apply braking when power is not applied
leftDriveMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);//forces motor to not apply braking when power is not applied
rightDriveMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);//forces motor to not apply braking when power is not applied
launchMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);//forces motor to not apply braking when power is not applied
wristMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);//forces motor to not apply braking when power is not applied
liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);//forces motor to not apply braking when power is not applied
ballIntakeMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);//forces motor to not apply braking when power is not applied
//sets motors in reverse
rightDriveMotor1.set_reversed(true);
rightDriveMotor2.set_reversed(true);

}

/** \brief
* \details Updates Brain info screen
*/
void updateInfoScreen()
{
  info_printf(1,"LeftDrive:%d",leftDriveMotor1.get_position());//writes current position for left drive motor in counts
  info_printf(2,"RightDrive:%d",rightDriveMotor1.get_position());//writes current position for right drive motor in counts
  info_printf(3,"Wrist:%x",wristMotor.get_position());//writes current position for wrist motor in counts
  info_printf(4,"Lift:%x",liftMotor.get_position());//writes current position for lift motor in counts
  filterCockedSensor(); //filters the launcher cocked sensor to get a stable output
}

/** \brief
* \details Updates LCD on controller
\param line The line to write to [0-2]
\param *linedata the charachter array containing the the text to display
*/
void updateControllerLcd(int line,char *linedata)
{
  //
  controller.print(line,0,linedata);//prints the passed charachter array to the specified line
  //swirl();//update swirl animation
}

/** \brief
* \details top level control of drivetrain
*/
void driveControl()
{

  static uint8_t drvactivelaststate = 0;//holds last state of half speed toggle
  static uint8_t drvrevlaststate = 0; //holds last state of reverse controls toggle
  if (changespeed == 1 && drvactivelaststate != 1)//check if button was not pressed last time throught the loop
  {
    halfspeed = !halfspeed;//toggles half speed drive
    sprintf(line0,"Intr:%d Spd:%d",intakeReverse,halfspeed);
    updateControllerLcd(0,line0);
    pros::delay(10);//allow LCD some time to update
  }
  if (controlr == 1 && drvrevlaststate != 1)//check if button was not pressed last run
  {
    reversecontrols = !reversecontrols;//reverse controls
    sprintf(line1,"Revc:%d",reversecontrols);
    updateControllerLcd(1,line1);
  }
  if (reversecontrols) // if controls reverse is active, reverse the powees
  {
    leftDrivePower = -leftDrivePower;//reverse power
    rightDrivePower = -rightDrivePower;//reverse power
  }
  if (!halfspeed){
  leftDriveMotor1.move(leftDrivePower);//sets drive power of rear left motor to desired power
  rightDriveMotor1.move(rightDrivePower);//sets drive power of rear right motor to desired power
  leftDriveMotor2.move(leftDrivePower);//sets drive power of front left motor to desired power
  rightDriveMotor2.move(rightDrivePower);//sets drive power of front right motor to desired power
  } else {
  leftDriveMotor1.move(leftDrivePower *.5);//sets drive power of rear left motor to half the desired power
  rightDriveMotor1.move(rightDrivePower*.5);//sets drive power of rear right motor to half the desired power
  leftDriveMotor2.move(leftDrivePower *.5);//sets drive power of rear left motor to half the desired power
  rightDriveMotor2.move(rightDrivePower*.5);//sets drive power of rear right motor to half the desired power
  }
  drvactivelaststate = changespeed;//set last state as current state
  drvrevlaststate = controlr;//set last state as current state
}
//reads controller states
/** \brief
* \details takes snapshot of current inputs to the joystick
*/
void readJoystick()
{

  leftDrivePower = controller.get_analog(ANALOG_LEFT_Y);//set left power to value of left analog stick
  rightDrivePower = controller.get_analog(ANALOG_RIGHT_Y);//set left power to value of left analog stick
   liftup = controller.get_digital(DIGITAL_R1);//set liftup based on state of button R1
	 liftdown = controller.get_digital(DIGITAL_R2);//set liftdown based on state of button R2
	 wristleft = controller.get_digital(DIGITAL_L1);//set wristleft based on state of button L1
	 wristright = controller.get_digital(DIGITAL_L2);//set wristright based on state of button L2
	 shoot = controller.get_digital(DIGITAL_A);//set shoot based on state of button A
	 unjam = controller.get_digital(DIGITAL_B);//set unjam based on state of button B
	 ballIntakeSetDir = readIntakeReverseButton(DIGITAL_UP);//set ballIntakeSetDir based on state of button UP
	 intake = readIntakeButton(DIGITAL_X);//set intake based on state of button X
   changespeed = readHalfSpeedButton(DIGITAL_LEFT);//set changespeed based on state of button LEFT
   controlr = readReverseControlsButton(DIGITAL_RIGHT);//set controlr based on state of button RIGHT
}
//moves lift
/** \brief
* \details moves lift using a state machine
*/
void liftControl()
{
  //
  static int state = 0;
  switch(state)
  {
    case 0:
            liftMotor.move(0);
            //if (liftup == 1 && liftMotor.get_position() >= LIFT_STACK_HEIGHT) {state = 4;}//if we are on ground move to descoring height
            if (liftup == 1) {liftMotor.move(-127);}//if we are above descoring height move to scoring height
            else if (liftdown == 1 && liftMotor.get_position() <= -1200) {state = 3;}//move to stack height if at max
            else if (liftdown == 1) {liftMotor.move(75);}
            else {state = 0;}//we are at an unknown position try again
            break;
    case 1:
            liftMotor.move(-127);
            break;
    // case 2:
    //         liftMotor.move(LIFT_GROUND_HEIGHT_PWR);//move lift at 75% power
    //         if (liftMotor.get_position() >= LIFT_GROUND_HEIGHT) {state = 0;}//move unit lift is at ground level
    //         break;
    case 3:
            liftMotor.move(LIFT_GROUND_HEIGHT_PWR);//move lift at 75% power
            if (liftMotor.get_position() >= LIFT_STACK_HEIGHT) {state = 0;}//move unit lift is at stack height
            break;
    case 4:
            liftMotor.move(LIFT_STACK_HEIGHT_PWR);//move lift at 75% power
              if (liftMotor.get_position() <= LIFT_STACK_HEIGHT) {state = 0;}//move unit lift is at descore height
              break;
    default://should never get here. Stop moving and reset.
            liftMotor.move(0);
            state = 0;
            break;

  }
}
/** \brief
* \details moves wrist using a state machine
*/
void wristControl()
{
// static int mode = 0;
// switch(mode)
// {
//   case 0:
//           wristMotor.move(0);//stop moving
//           if (wristleft && wristright) {mode = 3;}//move to stop state to prevent oscillation
//           else if (wristleft == 1 ){mode = 1;}//move wrist left
//           else if (wristright == 1){mode = 2;}//move wrist right
//           else {mode = 0;}//error occurred try again
//           break;
//   case 1:
//           wristMotor.move(100);//rotate left
//           if (wristMotor.get_position() >= WRIST_FULL_LEFT) {mode = 0;}//reset after rotate completes
//           break;
//   case 2:
//           wristMotor.move(-100);//rotate left
//           if (wristMotor.get_position() <= WRIST_FULL_RIGHT) {mode = 0;}//reset after rotate completes
//           break;
//   case 3:
//           wristMotor.move(0);//stop to prevent oscillation and reset
//           mode = 0;
//           break;
//   default://should never get here. reset
//           mode = 0;
//           break;
// }
  if (wristleft && wristright) {wristMotor.move(0);}//move to stop state to prevent oscillation
  else if (wristleft == 1 ){wristMotor.move(100);}//move wrist left
  else if (wristright == 1){wristMotor.move(-100);}//move wrist right
  else {wristMotor.move(0);}
}
/** \brief
* \details fires launcher
*/
//
void launcherControl()
{
    if(shoot == 1)
    {
      launchMotor.move(-127);//cock launcher by moving at 127 power in the reverse direction  xx%
    } else {
      launchMotor.move(0);//stop cocking launcher
    }
    if(unjam == 1) {
      launchMotor.move(40);//reverse launcher in case of jam
    }
}
/** \brief
* \details moves ball intake
*/
void ballIntakeControl()
{

  static uint8_t intactivelaststate = 0;//holds the last state of the intake active toggle
  static uint8_t intrevlaststate = 0;//holds the last state of the intake reverse toggle

  if (intake == 1 && intactivelaststate != 1)//checks if button is pressed but was not pressed last time through the loop
  {
    intakeActive = !intakeActive;//toggles intake on/off
  }

  if (ballIntakeSetDir == 1 && intrevlaststate != 1) {//checks if button is pressed but was not pressed last time through the loop
    intakeReverse = !intakeReverse;//toggles intake reverse
    sprintf(line0,"Intr:%d Spd:%d",intakeReverse,halfspeed);
    updateControllerLcd(0,line0);
  }
  else
	if(intakeActive && intakeReverse) //if intake is active and reverse was requested
  {
    ballIntakeMotor.move(-127);//runs ball intake in reverse
  } else if (intakeActive && !intakeReverse) {// if intake active and reverse was not requested
    ballIntakeMotor.move(127); //runs ball intake normally
  } else {
    ballIntakeMotor.move(0);//stops ball intake
  }
  intactivelaststate = intake;//set last state of intake active button to current state
  intrevlaststate = ballIntakeSetDir;//set last state of intake reverse button to current state
}
//provides reassurance of operation
/** \brief
* \details provides animation on controller to show that is is functioning.
* added after numerous lockups and failures during practice.
* the animation is - \ | / - \ | /.
* state has no meaningful use other that to hold which frame we are on.
*/
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
    swirlstate = 0; // restets and recovers from a invalid value
  swirlstate++;
  }
}
/** \brief
* \details reads intake toggle button
* \param button The ENUM of the button to read as intake toggle
* \return 1 if the button is pressed ,else 0
*/
int readIntakeButton(pros::controller_digital_e_t button)
{
  static int buttonvalue = 0;//keep value of button across calls
    buttonvalue = (buttonvalue << 1) | controller.get_digital(button);//append curent value of button to button value
    if ((buttonvalue & 0x0F) == 0x0F)//look for hex 15 in button value
    {
      return 1;//return pressed
    }
    else
    {
      return 0; //return not pressed
    }
}
/** \brief
* \details reads intake reverse toggle button
* \param button The ENUM of the button to read as intake reverse toggle
* \return 1 if the button is pressed ,else 0
*/
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
/** \brief
* \details reads reverse controls toggle button
* \param button The ENUM of the button to read as reverse controls toggle
* \return 1 if the button is pressed ,else 0
*/
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
/** \brief
* \details reads half speed toggle button
* \param button The ENUM of the button to read as half speed toggle
* \return 1 if the button is pressed ,else 0
*/
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
