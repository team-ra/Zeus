#include "main.h"

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
	pros::lcd::set_text(1, "Hello PROS User1!");
	pros::lcd::set_text(2, "Hello PROS User2!");
	pros::lcd::set_text(3, "Hello PROS User3!");
	pros::lcd::set_text(4, "Hello PROS User4!");
	pros::lcd::set_text(5, "Hello PROS User5!");
	pros::lcd::set_text(6, "Hello PROS User6!");
	pros::lcd::set_text(7, "Hello PROS User7!");
	pros::lcd::set_text(8, "Hello PROS User8!");
	pros::lcd::set_text(9, "Hello PROS User9!");
	pros::lcd::set_text(0, "Hello Line 0");
	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

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
