//
// Created by subaru on 3/5/19.
//

#include "robot.h"
#include "robot_gui.h"
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
// pros::ADILineSensor ps(PLATFORM_SENSOR_PORT);
pros::ADILineSensor es('f');
pros::ADILineSensor es2('e');
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
bool autoactive = false;
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
  if (liftup == 1) {liftMotor.move(-75);}//if we are above descoring height move to scoring height
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
    if(!autoactive) {
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
        static bool intialhomedone = false;
        info_printf(1,"%d",elstate);
        info_printf(2,"%d",((unsigned int)wristMotor.get_position() % 1500));
        switch(elstate) {

  	      case 0:
  		      if(controller.get_digital(DIGITAL_Y)) {if(!intialhomedone){elstate = 1;}intialhomedone = true;}
  		      else if(controller.get_digital(DIGITAL_R1)){elstate = 2;}
  		      else if(controller.get_digital(DIGITAL_R2)){elstate = 3;}
  		      else if(controller.get_digital(DIGITAL_L1)){elstate = 4;}
  		      else if(controller.get_digital(DIGITAL_L2)){elstate = 5;}
  		      break;

          case 1:
          wristMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
                wristMotor.move(80);
                if (es.get_value() > 1000) {elstate = 10;}
                break;

      		case 2:
          	if ( elstate == lastElState ) {elstate = 0; break;}
  		      position = 250;
  		      // current = wristMotor.get_position();
  		      if (position < currentTarget) { flag = 0;}
  		      else {flag =1;}
  			currentTarget = (currentTarget + position - lastTarget) % 1500;
  		      elstate = 9;
            lastElState = 2;
  		      break;
  		case 3:
            if ( elstate == lastElState ) {elstate = 0; break;}
  		      position = 790;
  		      // current = wristMotor.get_position();
  		      if (position < currentTarget) { flag = 0;}
  		      else {flag =1;}
  			currentTarget = (currentTarget + position - lastTarget) % 1500;

            elstate = 9;
            lastElState = 3;
  		      break;

  	      	case 4:
            if ( elstate == lastElState ) {elstate = 0; break;}
  		      position = 650;
  		      // current = wristMotor.get_position();
  		      if (position < currentTarget) { flag = 0;}
  		      else {flag =1;}
  			currentTarget = (currentTarget + position - lastTarget) % 1500;
  		      elstate = 9;
            lastElState = 4;
  		      break;
  		case 5:
            if ( elstate == lastElState ) {elstate = 0; break;}
  		      position = 800;
  		      // current = wristMotor.get_position();
  		      if (position < currentTarget) { flag = 0;}
  		      else {flag =1;}
  			currentTarget = (currentTarget + position - lastTarget) % 1500;
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
        if (es.get_value() < 1000) {
          elstate = 11;
        }
          break;
      case 11:
          wristMotor.move(-20);
           if (es.get_value() < 1000) {
            wristMotor.move(0);
            delay(20);
            wristMotor.tare_position();
            elstate = 0;
           }

  		    }

  			switch(flag) {
  				case 0:

            if(wristMotor.get_power() != 25) {wristMotor.move(25);}
            if ((50 < (currentPos % 1500)) &&  ((currentPos % 1500) < 100) ) {flag = 1;}

  					break;
  				case 1:
  				if ( (currentPos % 1500) <= currentTarget) {
  						if(wristMotor.get_power() != 25) {wristMotor.move(25);}
  					}
  					else { flag = 2;}
  					break;

  			     case 2:
  					      wristMotor.move(0);
                  break;
                }
        info_printf(3,"%d",currentTarget);

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
wristMotor.set_gearing(pros::E_MOTOR_GEARSET_18);//high speed
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
ballIntakeMotor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);//forces motor to not apply braking when power is not applied
//sets motors in reverse
rightDriveMotor1.set_reversed(true);
rightDriveMotor2.set_reversed(true);
ballIntakeMotor.set_reversed(true);
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
    liftup = controller.get_digital(DIGITAL_DOWN);
    liftdown = controller.get_digital(DIGITAL_LEFT);
    // wristleft = controller.get_digital(DIGITAL_L1);;
    // wristright = controller.get_digital(DIGITAL_L2);
    launchA = controller.get_digital(DIGITAL_A);
    launchB = controller.get_digital(DIGITAL_B);
    ballIntakeSetDir = controller.get_digital(DIGITAL_UP);
    intake = controller.get_digital(DIGITAL_X);
    changespeed = debounceButton(DIGITAL_LEFT);
    controlr = debounceButton(DIGITAL_RIGHT);
}


void doubletap() {

  static int dtstate = 0;
  static int nextdtstate = 0;
  static int  lastTarget = 0;
  static int position = 0;
  static int pos2 = 0;
  static int currentTarget = 0;
  static int flag = 4;
  unsigned long int currentPos = 0;
  static int lastdtstate = 0;
  static bool doneHoming = true;
  static bool intialhomedone = false;
  static bool flip= false;
  info_printf(1,"%d",dtstate);
  info_printf(2,"%d",flag);
  switch(dtstate) {

    case 0:
    if(controller.get_digital(DIGITAL_Y)) {dtstate = 1;}
    if(filterBallSensor() == 1) {
    if (!flip){
      if(controller.get_digital(DIGITAL_R1)){dtstate = 2;}
      else if(controller.get_digital(DIGITAL_R2)){dtstate = 3;}
      else if(controller.get_digital(DIGITAL_L1)){dtstate = 4;}
      else if(controller.get_digital(DIGITAL_L2)){dtstate = 5;}
    }
    else {
       if(controller.get_digital(DIGITAL_R2)){dtstate = 3;}
      else if(controller.get_digital(DIGITAL_R1)){dtstate = 2;}
      else if(controller.get_digital(DIGITAL_L2)){dtstate = 5;}
      else if(controller.get_digital(DIGITAL_L1)){dtstate = 4;}
    }
    flag = 4;
  }
   break;

   case 1:

         wristMotor.move(80);
         delay(20);
         if (es.get_value() > 1000) {dtstate = 11;}
         break;
    case 2:
      flip = true;
      // if ( dtstate == lastdtstate ) {break;}
      position = 50;
      // current = wristMotor.get_position();
      if (position < currentTarget) { flag = 0;}
      else {flag = 1;}
      currentTarget = (currentTarget + position - lastTarget) % 1500;
      dtstate = 9;
      lastdtstate = 2;
      break;
case 3:
      flip = false;
      // if ( dtstate == lastdtstate ) { break;}
      position = 990;
      // current = wristMotor.get_position();
      if (position < currentTarget) { flag = 0;}
      else {flag = 1;}
      currentTarget = (currentTarget + position - lastTarget) % 1500;
      dtstate = 9;
      lastdtstate = 3;
      break;

      case 4: // L1
      flip = true;
      // if ( dtstate == lastdtstate ) { break;}
      position = 450;
      // current = wristMotor.get_position();
      if (position < currentTarget) { flag = 0;}
      else {flag =1;}
      currentTarget = (currentTarget + position - lastTarget) % 1500;
      dtstate = 9;
      lastdtstate = 4;
      break;
case 5:
flip = false;
      // if ( dtstate == lastdtstate ) { break;}
      position = 1020;
      // current = wristMotor.get_position();
      if (position < currentTarget) { flag = 0;}
      else {flag = 1;}
      currentTarget = (currentTarget + position - lastTarget) % 1500;
      dtstate = 9;
      lastdtstate = 5;
      break;


case 9:
autoactive = true;
if (flag == 3)
  {
    shootBall(1);//startshoot state machine
    dtstate = 10;
  }
      break;

case 10:
  // controller.print(2,0,"%x",wristMotor.get_position());
  // delay(50);
    if(shootBall(0) == 1)
    {
      lastTarget = currentTarget;
      dtstate = 0;
      flag = 4;
      autoactive = false;
    }
  break;

case 11:
  if (es.get_value() < 1000) {
    dtstate = 12;
  }
    break;
case 12:
    wristMotor.move(-20);
     if (es.get_value() < 1000) {
      wristMotor.move(0);
      delay(20);
      wristMotor.tare_position();
      dtstate = 0;
     }

    }

    currentPos = wristMotor.get_position();
  switch(flag)
  {
    case 0:

      if(wristMotor.get_power() != 50) {wristMotor.move(70);}
      if ((50 < (currentPos % 1500)) &&  ((currentPos % 1500) < 100) ) {flag = 1;}

      break;
    case 1:
    if ( (currentPos % 1500) <= currentTarget) {
        if(wristMotor.get_power() != 50) {wristMotor.move(70);}
      }
      else { flag = 2;}
      break;
      case 2:
      if ( (currentPos % 1500) >= currentTarget) {
          if(wristMotor.get_power() != -25) {wristMotor.move(-25);}
        }
        else {flag = 3;}
        break;
       case 3:
            wristMotor.move(0);
            break;

      default:

            break;
  }
  info_printf(3,"%f",wristMotor.get_position());

}
//provides reassurance of operation
