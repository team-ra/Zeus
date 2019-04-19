#include "main.h"
#include "robot.h"
#include "robot_gui.h"
/**
* \details calls the first second function
*/
void auton2()
{
  resetEncoders();
  pros::delay(250);//waits for sensors to stabilize

  motorSetup();//sets up motors
//get in position to shoot top flag
  while( driveForward(encoderInchesToCounts(12),25,true) != 1);

//shoot high flag
  while (shootBall(0) == 0){//waits for ball to shoot
    pros::delay(10);
  }
}
