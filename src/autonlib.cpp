#include "robot.h"
#include "robot_gui.h"

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

/** \brief
* \details encoderInchesToCounts - Converts inches to encoder counts
* \param inches the number of inches to move
* \return int
*/
int encoderInchesToCounts(float inches)
{
  int counts;
  auto gearset = leftDriveMotor1.get_gearing();
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

/** \brief
* \details Drives Forward
* \param counts the number of counts to move
* \param power the power to drive at
* \param zeromotors whether or not to set motor home position when finished
*/
void driveForward(int counts,int power,bool zeromotors)
{
  leftDriveMotor1.move(power);
  rightDriveMotor1.move(-power);
  leftDriveMotor2.move(power);
  rightDriveMotor2.move(-power);
  while(leftDriveMotor1.get_position() <= counts && rightDriveMotor1.get_position() >= -counts);
  leftDriveMotor2.move(0);
  leftDriveMotor1.move(0);
  rightDriveMotor2.move(0);
  rightDriveMotor1.move(0);
  if(zeromotors){
    leftDriveMotor1.tare_position();
    rightDriveMotor1.tare_position();
  }
}
/** \brief
* \details Drives Backward
* \param counts the number of counts to move
* \param power the power to drive at
* \param zeromotors whether or not to set motor home position when finished
*/
void driveBackward(int counts,int power,bool zeromotors)
{
  rightDriveMotor1.move_relative(counts,power);
  leftDriveMotor2.move(-power);
  rightDriveMotor2.move(power);
  while(leftDriveMotor1.get_position() >= -counts && rightDriveMotor1.get_position() <= counts);
  leftDriveMotor2.move(0);
  rightDriveMotor2.move(0);
  if(zeromotors){
    leftDriveMotor1.tare_position();
    rightDriveMotor1.tare_position();
  }
}
/** \brief
* \details Turns Left
* \param counts the number of counts to move
* \param power the power to drive at
* \param zeromotors whether or not to set motor home position when finished
*/
void turnLeft(int counts,int power,bool zeromotors)
{
  rightDriveMotor1.move_relative(-counts,power);
  leftDriveMotor2.move(-power);
  rightDriveMotor2.move(power);
  while(leftDriveMotor1.get_position() <= -counts && rightDriveMotor1.get_position() <= -counts);
  leftDriveMotor2.move(0);
  rightDriveMotor2.move(0);
  if(zeromotors){
    leftDriveMotor1.tare_position();
    rightDriveMotor1.tare_position();
  }
}
/** \brief
* \details Turns Right
* \param counts the number of counts to move
* \param power the power to drive at
* \param zeromotors whether or not to set motor home position when finished
*/
void turnRight(int counts,int power,bool zeromotors)
{
  rightDriveMotor1.move_relative(counts,-power);
  leftDriveMotor2.move(power);
  rightDriveMotor2.move(-power);
  while(leftDriveMotor1.get_position() <= -counts && rightDriveMotor1.get_position() <= -counts);
  leftDriveMotor2.move(0);
  rightDriveMotor2.move(0);
  if(zeromotors){
    leftDriveMotor1.tare_position();
    rightDriveMotor1.tare_position();
  }
}
/** \brief
* \details Shoots the ball
* \return int
*/
int shootBall()
{
  static int state = 0;
  int retval = 0;
  switch(state)
  {
  case 0:
      //info_printf(1, "case0");
      if(filterBallSensor() == 1) {state = 1;}
      break;
  case 1:
    //info_printf(2, "case1");
    launchMotor.move(-127);
    if (filterCockedSensor() == 1){state = 2;}
    break;
  case 2:
    //info_printf(3, "case2");
    if ((filterBallSensor() == 0) || (filterCockedSensor() == 0)) { state = 3;}
    break;
  case 3:
  {
    //info_printf(4, "case3");
    launchMotor.move(0);
    state = 0;
    retval = 1;
  }
}
  return retval;

}
/** \brief
* \details Digitizes a sensor value
* \param value the value to digitize according to the threshold
* \return int
*/
int digitize(uint32_t value)
{
    if (value <= SHOOTER_THRESHOLD)
    {
      return 1;
    }
    else
    {
      return 0;
    }
}
/** \brief
* \details filters the launcher cocked sensor
* \return int
*/
int filterCockedSensor()
{
  static int cockedsensorvalue = 0;
    cockedsensorvalue = ls2.get_value();
    //cockedsensorvalue = (cockedsensorvalue << 1) | digitize(ls2.get_value());
    //pros::lcd::print(5,"B:%x",cockedsensorvalue);
    info_printf(5,"B:%x",cockedsensorvalue);
    if (cockedsensorvalue < 600)
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
* \return int
*/
int filterBallSensor()
{
  static int ballsensorvalue = 0;
    ballsensorvalue = ls.get_value();
    //ballsensorvalue = (ballsensorvalue << 1) | digitize(ls.get_value());
    //pros::lcd::print(6,"B2:%x",ballsensorvalue);
    info_printf(6,"B2:%x",ballsensorvalue);
    if (ballsensorvalue < 700)
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
    ballIntakeMotor.move(-100);
  }
  else{
    ballIntakeMotor.move(100);
  }
}
/** \brief
* \details Turns ball intake off
*/
void intakeOff()
{
  ballIntakeMotor.move(0);
}
