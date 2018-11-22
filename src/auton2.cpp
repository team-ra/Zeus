#include "main.h"
#include "robot.h"
#include "robot_gui.h"
/**
* \details calls the first second function
*/
void auton2()
{
  pros::delay(250);
  //info_printf(1, "auton1");
  motorSetup();

  //info_printf(1, "before shoot");
  while (shootBall() == 0){
    pros::delay(10);
  }
  //info_printf(1, "end auton1");
}
