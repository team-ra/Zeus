#include "main.h"
using namespace pros::literals;

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::Controller controller(pros::E_CONTROLLER_MASTER);
	pros::Motor leftDriveMotor(1);
	pros::Motor rightDriveMotor(2);
	pros::Motor launchMotor(3);
	pros::Motor wristMotor(4);
	pros::Motor liftMotor(5);
	pros::Motor ballIntakeMotor(6);
	while (true) {
	leftDriveMotor.move(controller.get_analog(ANALOG_LEFT_Y));
	rightDriveMotor.move(controller.get_analog(ANALOG_RIGHT_Y));
	int liftup = controller.get_digital(DIGITAL_R1);
	int liftdown = controller.get_digital(DIGITAL_R2);
	int wristleft = controller.get_digital(DIGITAL_L1);

	if (liftup == 1){liftMotor.move(100);} else { liftMotor.move(0);}
	if (liftdown == 1 && liftup != 1){liftMotor.move(-100);} else {liftMotor.move(0);}
	if(wristleft == 1) { wristMotor.move(-100);} else { wristMotor.move(0);}
	
}
}
