#include "robot.h"
#include "robot_gui.h"

#define STALLED_THRESHOLD 10
#define TWO_LINE_SENSORS
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

extern pros::ADILineSensor es;

extern pros::ADILineSensor es2;

extern pros::ADILineSensor cs2;

extern pros::ADIGyro gyro;
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
            if(leftDriveGetPos() < counts && rightDriveGetPos() < counts){}
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
            if(leftDriveGetPos() > counts && rightDriveGetPos() > counts){}
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
            if(leftDriveGetPos() > -counts*.8 && rightDriveGetPos() < counts*.8){}
            else {
              leftDriveSet(-25);
              rightDriveSet(25);
              state = 2;
            }//check if we have reached position
            break;
    case 2:
    if(leftDriveGetPos() > -counts && rightDriveGetPos() < counts){}
    else {state = 3;}//check if we have reached position
    break;
    case 3:
    leftDriveSet(0);
    rightDriveSet(0);
    if(zeromotors){
      leftDriveMotor1.tare_position();//zero encoder
      rightDriveMotor1.tare_position();//zero encoder
    }
    state = 0;
      return 1;
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
            // if((leftDriveGetPos() <= counts*.8) && (-rightDriveGetPos() <= counts*.8))
            if(leftDriveGetPos() <= counts*.8)
            {

            }
            else {
              leftDriveSet(25);
              rightDriveSet(-25);
              state = 2;
            }//check if we have reached position
            break;
   case 2:
            // if(leftDriveGetPos() <=counts && -rightDriveGetPos() <= counts){
            if(leftDriveGetPos() <= counts){

            }
            else {state = 3;}//check if we have reached position
            break;
    case 3:
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
int shootBall(int command)
{
  static int state = 4;//holds the state machine's state
  info_printf(5,"%d",state);
  if (command == 1) {state = 0;}
  switch(state)
  {
  case 0:
      //info_printf(1, "case0");
      if(filterBallSensor() == 1) {
        launchMotor.move(-127);
        state = 1;
      }//check if ball present

      break;
  case 1:
    //info_printf(2, "case1");
    if (filterCockedSensor() == 1){state = 2;}//2check if launcher cocked
    break;
  case 2:
    //info_printf(3, "case2");
    //check if ball has left launcher
    // launchMotor.move(20);
    // pros::delay(50);
    if ((filterCockedSensor() == 0)) {
      state = 3;}
    break;
  case 3:
    //info_printf(4, "case3");
    launchMotor.move(0);
    state = 4; //restart state machine
    break;
  case 4:
    return 1;//return fired
    break;//idle
}
  return 0;//else return unfired

}

int home(int x) {
  static int hstate = 5;
  if(x == 1) {hstate = 0;}
  switch(hstate) {
    case 0:
          wristMotor.move(80);
          pros::delay(20);
          if (es.get_value() > 1000) {hstate = 1;}
          break;
   case 1:
         if (es.get_value() < 1000) {
           hstate = 2;
         }
         break;
  case 2:
        wristMotor.move(-20);
        pros::delay(20);
         if (es.get_value() < 1000) {hstate = 3;}
         break;
case 3:
        wristMotor.move(0);
        pros::delay(20);
        wristMotor.tare_position();
        hstate = 4;
        break;
case 4:
        return 1;
        break;
default:
        break;

  }
  return 0;
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
//
int elevate(int target) {
  static int dtstate = 0;
  static int lastTarget = 0;
  static int position = 0;
  static int currentTarget = 0;
  static int flag = 4;
  unsigned long int currentPos = 0;
  if(target == 0){dtstate = 0;}
  currentPos = wristMotor.get_position();
  switch(dtstate) {

    case 0:
      if     (target == 1){position = 250;}
      else if(target == 2){position = 990;}
      else if(target == 3){position = 450;}
      else if(target == 4){position = 1300;}
      else {break;}
      flag = 4;
      if (position < currentTarget) { flag = 0;}
      else {flag = 1;}
      currentTarget = (currentTarget + position - lastTarget) % 1500;
      dtstate = 5;
   break;

case 5:
// autoactive = true;
if (flag == 3)
    {
      lastTarget = currentTarget;
      dtstate = 6;
    }
      break;

case 6:
      return 1;
      break;

default:
  break;
    }

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
  return 0;
  }

/** \brief
* \details filters the launcher cocked sensor
* \return 1 if cocked, else 0
*/
int filterCockedSensor()
{
  #ifdef TWO_LINE_SENSORS
  static int cockedsensorvalue = 0;//holds value of cocked sensor
  static int cs2sensorvalue = 0;
    cockedsensorvalue = ls2.get_value();//get value of ball cocked sensor
    cs2sensorvalue = cs2.get_value();
    //cockedsensorvalue = (cockedsensorvalue << 1) | digitize(ls2.get_value());
    //pros::lcd::print(5,"B:%x",cockedsensorvalue);
    // info_printf(5,"B:%x - Max:%x - Min:%x",cockedsensorvalue, max, min);
    if ( (cockedsensorvalue < 2000) || (cs2sensorvalue < 2000))//check if in threshold
    {
      return 1;
    }
    else
    {
      return 0;
    }

#else
static int cockedsensorvalue = 0;//holds value of cocked sensor
cockedsensorvalue = ls2.get_value();//get value of ball cocked sensor
//cockedsensorvalue = (cockedsensorvalue << 1) | digitize(ls2.get_value());
//pros::lcd::print(5,"B:%x",cockedsensorvalue);
// info_printf(5,"B:%x - Max:%x - Min:%x",cockedsensorvalue, max, min);
if (cockedsensorvalue < 2000) //check if in threshold
{
  return 1;
}
else
{
  return 0;
}
#endif

}

int filterElevationHomeSensor()
{
  static int elevationsensor = 0;//holds value of cocked sensor
    elevationsensor = es.get_value();//get value of ball cocked sensor
    //cockedsensorvalue = (cockedsensorvalue << 1) | digitize(ls2.get_value());
    //pros::lcd::print(5,"B:%x",cockedsensorvalue);
    // info_printf(5,"B:%x",elevationsensor);
    if (elevationsensor < 600) //check if in threshold
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
  static int bs2value = 0;
    ballsensorvalue = ls.get_value();//get value of ball present sensor
    bs2value = es2.get_value();
    //ballsensorvalue = (ballsensorvalue << 1) | digitize(ls.get_value());
    //pros::lcd::print(6,"B2:%x",ballsensorvalue);
    // info_printf(6,"B2:%x",ballsensorvalue);
    if ( (ballsensorvalue < 700) || (bs2value < 700))//check if in threshold
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


double leftDriveGetPos() {
  return ( leftDriveMotor1.get_position() + leftDriveMotor2.get_position() ) / 2;
}

double rightDriveGetPos() {
  return (rightDriveMotor1.get_position() + rightDriveMotor2.get_position())/2;
}

void resetEncoders()
{
  leftDriveMotor1.tare_position();
  rightDriveMotor1.tare_position();
  leftDriveMotor2.tare_position();
  rightDriveMotor2.tare_position();
}
/**\brief
* \details state machine to park on blue platform
* \returns 0 when running, 1 when complete
*/

/**\brief
* \details adjusts power during a drive to keep straight
*/
void drivestraight(int dmp)//add or subtract power to stay on course when driving long distances
{

    //go straight algorithm
      static int offset = 0;
      if ( (rightDriveMotor2.get_position() - leftDriveMotor2.get_position()) >= 15  )
      {
        offset += 10;
      }

      else if ( (rightDriveMotor2.get_position() - leftDriveMotor2.get_position()) >= 10  )
      {
        offset += 5;
      }

      else if ( (rightDriveMotor2.get_position() - leftDriveMotor2.get_position()) >= 5  )
      {
        offset += 2;
      }

      else if ( (rightDriveMotor2.get_position() - leftDriveMotor2.get_position()) <= -5  )
      {
        offset -= 2;
      }
      else if ( (rightDriveMotor2.get_position() - leftDriveMotor2.get_position()) <= -10  )

      {
        offset -= 5;
      }

      else if ( (rightDriveMotor2.get_position() - leftDriveMotor2.get_position()) <= -15  )
      {
        offset -= 10;
      }


      else if ( (leftDriveMotor2.get_position() >= -5) && (leftDriveMotor2.get_position() <= 5) )
      {
        offset = 0;
      }

      if ( (offset > 500))
      {
        offset = 500;
      }
      else if (offset < -500)
      {
        offset = -500;
      }
    rightDriveSet(dmp-offset/50);
    pros::delay(30);

  }

  int gyroturn(double degrees) {
    if (degrees < 0) {
      leftDriveSet(-25);
      rightDriveSet(25);
    }
    else {
      leftDriveSet(25);
      rightDriveSet(-25);
    }
    if(gyro.get_value() > degrees * 10) {
      leftDriveSet(0);
      rightDriveSet(0);
      return 1;
    }
    return 0;
  }
