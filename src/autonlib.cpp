#include "robot.h"
#include "robot_gui.h"

#define STALLED_THRESHOLD 10

using namespace pros::literals;
/// The Back left drive motor
extern pros::Motor leftDriveMotor1;
/// The Back right drive motor
extern pros::Motor rightDriveMotor1;
/// The Front left drive motor
extern pros::Motor leftDriveMotor2;
/// The Front right drive motor
extern pros::Motor rightDriveMotor2;
/// The launcher motor
extern pros::Motor launchMotor;
/// The wrist motor
extern pros::Motor wristMotor;
/// The lift motor
extern pros::Motor liftMotor;
/// The ball intake motor
extern pros::Motor ballIntakeMotor;
/// The ball present sensor
extern pros::ADILineSensor ls2;
/// The launcher cocked sensor
extern pros::ADILineSensor ls;
///the platform sensor
extern pros::ADILineSensor ps;
/** \brief
* \details encoderInchesToCounts - Converts inches to encoder counts
* \param inches the number of inches to move
* \return number of encoder counts in specified inches
*/
int encoderInchesToCounts(float inches)
{
  double pi = 3.14159265359;
  int counts;
  auto gearset = leftDriveMotor1.get_gearing();//alllows function to make the correct calculation based on the configured gearset
  if (gearset == pros::E_MOTOR_GEARSET_36)//checks if 36:1 gearset is configured
  {
      counts = inches * (1800/(4*pi));//calculates the number of counts
  }
  else if (gearset == pros::E_MOTOR_GEARSET_18)//checks if 18:1 gearset is configured
  {
      counts = inches * (900/(4*pi));//calculates the number of counts
  }
  else if (gearset == pros::E_MOTOR_GEARSET_06)//checks if 6:1 gearset is configured
  {
     counts = inches * (300/(4*pi));//calculates the number of counts
  }
  return counts;//return counts
}

/** \brief
* \details Drives Forward
* \param counts the number of counts to move
* \param power the power to drive at
* \param zeromotors whether or not to set motor home position when finished
*/
int driveForward(int counts,int power,bool zeromotors)
{
  static int state = 0;
  switch(state) {
    case 0:
            leftDriveSet(power);
            rightDriveSet(power);
            state = 1;
            break;

    case 1:
            if(leftDriveMotor1.get_position() < counts && rightDriveMotor1.get_position() > -counts){}
            else {state = 2;}//check if we have reached position
            break;
    case 2:
            leftDriveSet(0);
            rightDriveSet(0);
            if(zeromotors){
              leftDriveMotor1.tare_position();//zero encoder
              rightDriveMotor1.tare_position();//zero encoder
            }
    state = 0;
    return 1;

    break;
  }
  return 0;
}
/** \brief
* \details Drives Backward
* \param counts the number of counts to move
* \param power the power to drive at
* \param zeromotors whether or not to set motor home position when finished
*/
int driveBackward(int counts,int power,bool zeromotors)
{
  static int state = 0;
  switch(state) {
    case 0:
            leftDriveSet(-power);
            rightDriveSet(-power);
            state = 1;
            break;
    case 1:
            if(leftDriveMotor1.get_position() < counts && rightDriveMotor1.get_position() > -counts){}
            else {state = 2;}//check if we have reached position
            break;
    case 2:
            leftDriveSet(0);
            rightDriveSet(0);
            if(zeromotors){
              leftDriveMotor1.tare_position();//zero encoder
              rightDriveMotor1.tare_position();//zero encoder
            }
    state = 0;
    return 1;

    break;
  }
  return 0;

}
/** \brief
* \details Turns Left
* \param counts the number of counts to move
* \param power the power to drive at
* \param zeromotors whether or not to set motor home position when finished
*/
int turnLeft(int counts,int power,bool zeromotors)
{
  static int state = 0;
  switch(state) {
    case 0:
            leftDriveSet(-power);
            rightDriveSet(power);
            state = 1;
            break;
    case 1:
            if(leftDriveMotor1.get_position() > -counts && rightDriveMotor1.get_position() > -counts){}
            else {state = 2;}//check if we have reached position
            break;
    case 2:
            leftDriveSet(0);
            rightDriveSet(0);
            if(zeromotors){
              leftDriveMotor1.tare_position();//zero encoder
              rightDriveMotor1.tare_position();//zero encoder
            }
            state = 0;
    return 1;

    break;
  }
  return 0;

}
/** \brief
* \details Turns Right
* \param counts the number of counts to move
* \param power the power to drive at
* \param zeromotors whether or not to set motor home position when finished
*/
int turnRight(int counts,int power,bool zeromotors)
{
  static int state = 0;
  switch(state) {
    case 0:
            leftDriveSet(power);
            rightDriveSet(-power);
            state = 1;
            break;
    case 1:
            if(leftDriveMotor1.get_position() <= counts && rightDriveMotor1.get_position() >= -counts){}
            else {state = 2;}//check if we have reached position
            break;
    case 2:
            leftDriveSet(0);
            rightDriveSet(0);
            if(zeromotors){
              leftDriveMotor1.tare_position();//zero encoder
              rightDriveMotor1.tare_position();//zero encoder
            }
            state = 0;
    return 1;
    break;
  }
  return 0;
}
/** \brief
* \details State machine that shoots the ball. Must be called until it returns 1
* \return 1 if ball fired, else 0
*/
int shootBall()
{
  static int state = 0;//holds the state machine's state
  int retval = 0;// holds the value to return
  switch(state)
  {
  case 0:
      //info_printf(1, "case0");
      if(filterBallSensor() == 1) {state = 1;}//check if ball present
      break;
  case 1:
    //info_printf(2, "case1");
    launchMotor.move(-127);
    if (filterCockedSensor() == 1){state = 2;}//check if launcher cocked
    break;
  case 2:
    //info_printf(3, "case2");
    //check if ball has left launcher
    if ((filterBallSensor() == 0) || (filterCockedSensor() == 0)) { state = 3;}
    break;
  case 3:
  {
    //info_printf(4, "case3");
    launchMotor.move(0);
    state = 0; //restart state machine
    retval = 1;//return fired
  }
}
  return retval;//else return unfired

}
/** \brief
* \details Digitizes a sensor value
* \param value the value to digitize according to the threshold
* \return 1 if above threshold, else 0
*/
int digitize(uint32_t value)
{
    if (value <= SHOOTER_THRESHOLD) //check if in threshold
    {
      return 1;//return below threshold
    }
    else
    {
      return 0;//return above threshold
    }
}
/** \brief
* \details filters the launcher cocked sensor
* \return 1 if cocked, else 0
*/
int filterCockedSensor()
{
  static int cockedsensorvalue = 0;//holds value of cocked sensor
    cockedsensorvalue = ls2.get_value();//get value of ball cocked sensor
    //cockedsensorvalue = (cockedsensorvalue << 1) | digitize(ls2.get_value());
    //pros::lcd::print(5,"B:%x",cockedsensorvalue);
    info_printf(5,"B:%x",cockedsensorvalue);
    if (cockedsensorvalue < 600) //check if in threshold
    {
      return 1;
    }
    else
    {
      return 0;
    }
}
/** \brief
* \details filters the ball present sensor
* \return 1 if ball present, else 0
*/
int filterBallSensor()
{
  static int ballsensorvalue = 0;
    ballsensorvalue = ls.get_value();//get value of ball present sensor
    //ballsensorvalue = (ballsensorvalue << 1) | digitize(ls.get_value());
    //pros::lcd::print(6,"B2:%x",ballsensorvalue);
    info_printf(6,"B2:%x",ballsensorvalue);
    if (ballsensorvalue < 700)//check if in threshold
    {
      return 1;
    }
    else
    {
      return 0;
    }
}
/** \brief
* \details Turns ball intake on
* \param reverse Whether to turn the ball intake on in reverse
*/
void intakeOn(bool reverse)
{
  if(reverse)
  {
    ballIntakeMotor.move(-127);//turn intake on in reverse
  }
  else{
    ballIntakeMotor.move(127);//turn intake on normally
  }
}
/** \brief
* \details Turns ball intake off
*/
void intakeOff()
{
  ballIntakeMotor.move(0); //turns ball intake off
}
/**\brief
* \details abstraction to address left side of drivetrain
*/
void leftDriveSet(int power)
{
  leftDriveMotor1.move(power);//start moving rear left drive motor
  leftDriveMotor2.move(power);//start moving front left drive motor
}
/**\brief
* \details abstraction to address right side of drivetrain
*/
void rightDriveSet(int power)
{
  rightDriveMotor1.move(power);//start moving rear right drive motor
  rightDriveMotor2.move(power);//start moving front right drive motor
}

void resetEncoders()
{
  leftDriveMotor1.tare_position();
  rightDriveMotor1.tare_position();
}
//
int platformpresentblue()
{
  static int state = 0;
  switch(state)
  {
    //
    case 0:
            leftDriveSet(75);
            rightDriveSet(75);
            state = 1;
            break;
    case 1:
            if (ps.get_value() <= PLATFORM_CONTACT_BLUE) {state = 2;}
            break;
    case 2:
            delay(250);
            if (ps.get_value() <= PLATFORM_CONTACT_YELLOW) {state = 4;}
            break;
    case 3:
            // // leftDriveSet(127);
            // // rightDriveSet(127);
            // leftDriveSet(75);
            // rightDriveSet(75);
            // if (ps.get_value() <= PLATFORM_CONTACT_YELLOW && ps.get_value() <= PLATFORM_CONTACT_BLUE) {state = 4;}//leftDriveSet(0);rightDriveSet(0);}
            // break;//
    case 4:

            leftDriveSet(0);
            rightDriveSet(0);
            state = 0;
            return 1;
            break;

  }
  return 0;
  //
}

int platformpresentred()
{
  static int state = 0;
  switch(state)
  {
    //
    case 0:
            leftDriveSet(75);
            rightDriveSet(75);
            state = 1;
            break;
    case 1:
            // if (ps.get_value() <= PLATFORM_CONTACT_RED) {state = 2;}
            filterPlatform();
            state = 2;
            break;
    case 2:
            delay(500);
            // if (ps.get_value() <= PLATFORM_CONTACT_YELLOW) {state = 4;}
            filterPlatform();
            state = 4;
            break;
    case 3:
            // // leftDriveSet(127);
            // // rightDriveSet(127);
            // leftDriveSet(75);
            // rightDriveSet(75);
            // if (ps.get_value() <= PLATFORM_CONTACT_YELLOW && ps.get_value() <= PLATFORM_CONTACT_BLUE) {state = 4;}//leftDriveSet(0);rightDriveSet(0);}
            // break;//
    case 4:

            leftDriveSet(0);
            rightDriveSet(0);
            state = 0;
            return 1;
            break;

  }
  return 0;
}

void filterPlatform() {
  int count = 0;
  while (count < 3)
  {
    delay(25);
    if (ps.get_value() < PLATFORM_CONTACT_RED) {count++;}
    else {count = 0;}
  }
}

bool checkIfStalled() {
static int startcounts = leftDriveMotor1.get_position();
static int timesunderthreshold = 0;
if (leftDriveMotor1.get_position() - startcounts <= STALLED_THRESHOLD)
{
    timesunderthreshold++;
    intakeOn(false);
    pros::delay(20);
}
else {
  timesunderthreshold = 0;
}

if (timesunderthreshold >= 5)
{
  timesunderthreshold = 0;
  intakeOff();
  return true;
}
return false;
}
