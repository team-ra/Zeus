//
// Created by subaru on 3/5/19.
//

#include "robot.h"

using namespace pros::literals;


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
 pros::Motor wristMotor(7);
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
pros::ADILineSensor es('f');
//controller and motor state variables
int leftDrivePower;
int rightDrivePower;
uint8_t launchA;
uint8_t launchB;
uint8_t ballIntakeSetDir;
uint8_t ballIntakeSetOut;
uint8_t intake;
uint8_t changespeed;
uint8_t controlr;
uint8_t wristleft;
uint8_t wristright;
uint8_t liftup;
uint8_t liftdown;

// void ballIntakeControl() {
//     static int state = 0;
//     static bool intActive = false;
//     static bool intReverse = false;
//     int intPower = 100;
//     float speedMult = .5;
//     static bool lastActive = false;
//
//     switch (state) {
//         case 0:
//             if (intake && !lastActive) { state = 1; }
//             if (ballIntakeSetDir && !lastActive) { state = 2;}
//             break;
//         case 1:
//             intActive = !intActive;
//             lastActive = true;
//             state = 3;
//             break;
//         case 2:
//             intReverse = !intReverse;
//             state = 3;
//             break;
//         case 3:
//             if (intActive && intReverse) {ballIntakeMotor.move(-intPower);}
//             else if (intActive && !intReverse) {ballIntakeMotor.move(intPower);}
//             else {ballIntakeMotor.move(0);}
//             state = 0;
//             break;
//     }
// }

void ballIntakeControl() {
    static int activestate = 0;
    static int reversestate = 0;
    static bool intActive = false;
    static bool intReverse = false;
    int intPower = 100;
    float speedMult = .5;
    static int lastState = 0;
    static int lastRevState = 0;

    switch (activestate) {
        case 0:
              if(intake && (lastState == 0)) {
                activestate = 1;
              }
              break;
        case 1:
              if(intake && (lastState == 1)) {
                activestate = 2;
              }
              break;
        case 2:
              if (intake == 0 && (lastState == 2)) {
                activestate = 3;
              }
              break;
        case 3:
              intActive = !intActive;
              if (intActive){ballIntakeMotor.move(intPower);}
              else {ballIntakeMotor.move(0);}
              activestate = 0;

    }

    switch (reversestate) {
        case 0:
              if(ballIntakeSetDir && (lastRevState == 0)) {
                reversestate = 1;
              }
              break;
        case 1:
              if(ballIntakeSetDir && (lastRevState == 1)) {
                reversestate = 2;
              }
              break;
        case 2:
              if (ballIntakeSetDir == 0 && (lastRevState == 2)) {
                reversestate = 3;
              }
              break;
        case 3:
              intReverse = !intReverse;
              if(intActive && intReverse){ballIntakeMotor.move(-intPower);}
              reversestate = 0;

    }

lastState = activestate;
lastRevState = reversestate;
}


void liftControl()
{

  static int state = 0;
  if (liftup == 1) {liftMotor.move(-127);}//if we are above descoring height move to scoring height
  else if (liftdown == 1) {liftMotor.move(75);}
  else {liftMotor.move(0);}//we are at an unknown position try again

}


int debounceButton(pros::controller_digital_e_t button) {

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

void launcherControl()
{
    int rackPower = -127;
    int revPower = 40;
    static int state = 0;
    switch(state) {
        case 0:
            if (launchA) {state = 1;}
            else if (launchB) {state = 2;}
            else {state = 3;}
            break;
        case 1:
            launchMotor.move(rackPower);
            state = 0;
            break;
        case 2:
            launchMotor.move(revPower);
            state = 0;
            break;
        case 3:
            launchMotor.move(0);
            state = 0;
            break;
    }

}

void rakeControl()
{
    static int state = 0;
    int rakePower = 100;
    switch(state) {
        case 0:
            if (wristleft && wristright) { state = 3;}
            else if (wristleft == 1){ state = 1;}
            else if (wristright == 1) { state = 2;}
            else { state = 3;}
            break;
        case 1:
            wristMotor.move(rakePower);
            state = 0;
            break;
        case 2:
            wristMotor.move(-rakePower);
            state= 0;
            break;
        case 3:
            wristMotor.move(0);
            state = 0;;
            break;

    }
}

void elevationControl() {
        static int elstate = 0;
        static int  lastTarget = 0;
        static int position = 0;
        static int currentTarget = 0;
        static int flag = 3;
        unsigned long int currentPos = 0;
        static int lastElState = 0;
        static bool doneHoming = true;
  	    switch(elstate) {

  	      case 0:
  		      if(controller.get_digital(DIGITAL_Y)) {elstate = 1;}
  		      else if(controller.get_digital(DIGITAL_R1)){elstate = 2;}
  		      else if(controller.get_digital(DIGITAL_R2)){elstate = 3;}
  		      else if(controller.get_digital(DIGITAL_L1)){elstate = 4;}
  		      else if(controller.get_digital(DIGITAL_L2)){elstate = 5;}
  		      break;

          case 1:
                wristMotor.move(25);
                if (es.get_value() > 1680) {elstate = 10;}
                break;

      		case 2:
          	if ( elstate == lastElState ) {elstate = 0; break;}
  		      position = 250;
  		      // current = wristMotor.get_position();
  		      if (position < currentTarget) { flag = 0;}
  		      else {flag =1;}
  			currentTarget = (currentTarget + position - lastTarget) % 800;
  		      elstate = 9;
            lastElState = 2;
  		      break;
  		case 3:
            if ( elstate == lastElState ) {elstate = 0; break;}
  		      position = 450;
  		      // current = wristMotor.get_position();
  		      if (position < currentTarget) { flag = 0;}
  		      else {flag =1;}
  			currentTarget = (currentTarget + position - lastTarget) % 800;

            elstate = 9;
            lastElState = 3;
  		      break;

  	      	case 4:
            if ( elstate == lastElState ) {elstate = 0; break;}
  		      position = 650;
  		      // current = wristMotor.get_position();
  		      if (position < currentTarget) { flag = 0;}
  		      else {flag =1;}
  			currentTarget = (currentTarget + position - lastTarget) % 800;
  		      elstate = 9;
            lastElState = 4;
  		      break;
  		case 5:
            if ( elstate == lastElState ) {elstate = 0; break;}
  		      position = 750;
  		      // current = wristMotor.get_position();
  		      if (position < currentTarget) { flag = 0;}
  		      else {flag =1;}
  			currentTarget = (currentTarget + position - lastTarget) % 800;
  		      elstate = 9;
            lastElState = 5;
  		      break;

  		case 9:
  		  lastTarget = currentTarget;
        controller.print(2,0,"%x",wristMotor.get_position());
    		delay(50);
        currentPos = wristMotor.get_position();
  			if(flag == 2) {
          elstate = 0;
        }
  			break;

      case 10:
        if (es.get_value() < 1680) {
          wristMotor.move(0);
          delay(20);
          wristMotor.tare_position();
          elstate = 0;
        }
        break;
      case 11:
            flag = 4;
            if (wristMotor.get_power() != 25) {wristMotor.move(25);}
              doneHoming = false;
              while (es.get_value() > 1680);
              while(es.get_value() < 1680);
              wristMotor.move(0);
              delay(20);
              wristMotor.tare_position();
              doneHoming = true;
              elstate = 9;

          break;
  		    }

  			switch(flag) {
  				case 0:
            wristMotor.move(25);
            if ((10 < (currentPos % 800)) &&  ((currentPos % 800) < 20) ) {flag = 1;}

  					break;
  				case 1:
  				if ( (currentPos % 800) <= currentTarget) {
  						wristMotor.move(25);
  					}
  					else { flag = 2;}
  					break;

  			     case 2:
  					      wristMotor.move(0);
                  break;

            case 4:
                  if(doneHoming) {flag = 1;}
  			}

  }

void driveControl()
{
    static int state = 0;
    static bool halfspeed = false;
    switch(state) {
        case 0:
            if (changespeed) { state = 1;}
            else {state = 2;}
            break;
        case 1:
            halfspeed = !halfspeed;
            state = 2;
            break;
        case 2:
            if (halfspeed) {
                leftDriveSet(leftDrivePower *.5);//sets drive power of left motor to half
                rightDriveSet(rightDrivePower*.5);//sets drive power of right motor to half
            }
            else {
                leftDriveSet(leftDrivePower);//sets drive power of left motor
                rightDriveSet(rightDrivePower);//sets drive power of right motor
            }
            state = 0;
            break;


    }
}



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
wristMotor.set_gearing(pros::E_MOTOR_GEARSET_36);//high speed
liftMotor.set_gearing(pros::E_MOTOR_GEARSET_18);//torque
ballIntakeMotor.set_gearing(pros::E_MOTOR_GEARSET_06);//high speed

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
liftMotor.set_reversed(true);
wristMotor.set_reversed(true);
}

void updateControllerLcd()
{
    char line1[16];
    sprintf(line1,"Intr:%d Spd:%d",0,1);
    updateLineData(line1);
    updateLineNumber(0);
    requestLcdUpdate();
}

//set controller states
void readJoystick()
{
    leftDrivePower = controller.get_analog(ANALOG_LEFT_Y);
    rightDrivePower = controller.get_analog(ANALOG_RIGHT_Y);
    // liftup = controller.get_digital(DIGITAL_R1);
    // liftdown = controller.get_digital(DIGITAL_R2);
    // wristleft = controller.get_digital(DIGITAL_L1);;
    // wristright = controller.get_digital(DIGITAL_L2);
    launchA = controller.get_digital(DIGITAL_A);
    launchB = controller.get_digital(DIGITAL_B);
    ballIntakeSetDir = controller.get_digital(DIGITAL_UP);
    intake = controller.get_digital(DIGITAL_X);
    changespeed = debounceButton(DIGITAL_LEFT);
    controlr = debounceButton(DIGITAL_RIGHT);
}

//provides reassurance of operation
