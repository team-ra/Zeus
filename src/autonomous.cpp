#include "main.h"
#include "robot.h"
#include "robot_gui.h"

using namespace pros::literals;
/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {

  motorSetup();
  extern pros::ADILineSensor ls2;
  ls2.calibrate();
//int mode = setAutonMode();
//pros::lcd::print(1,"%d",mode);
//startauto(2);
// //driveForward(encoderInchesToCounts(10),100,true);
// driveBackward(encoderInchesToCounts(10),100,true);
// turnLeft(100, 50, true);

  (*auton_ptr)(); // pointer to function assigned by robot_gui selection
}
