#include "main.h"

extern pros::Motor leftDriveMotor;
extern pros::Motor rightDriveMotor;
extern pros::Motor launchMotor;
extern pros::Motor wristMotor;
extern pros::Motor liftMotor;
extern pros::Motor ballIntakeMotor;

void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User");
	pros::lcd::register_btn1_cb(on_center_button);

}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
	leftDriveMotor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	rightDriveMotor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	launchMotor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	wristMotor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	ballIntakeMotor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
leftDriveMotor.move(0);
rightDriveMotor.move(0);
launchMotor.move(0);
wristMotor.move(0);
liftMotor.move(0);
ballIntakeMotor.move(0);
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}
