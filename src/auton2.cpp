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
  //info_printf(1, "auton1");
  motorSetup();//sets up motors

  //info_printf(1, "before shoot");
  while (shootBall() == 0){//waits for ball to shoot
    pros::delay(10);
  }
  //info_printf(1, "end auton1");
}
