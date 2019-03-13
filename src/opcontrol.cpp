#include "main.h"
#include "robot.h"
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
	extern pros::Controller controller;
	std::uint32_t lasttime;//holds last time since controller LCD updated
	char line2[14];
	char initmessage[14];
	char blankline[0];
	sprintf(initmessage,"initializing");

	motorSetup();//setup motors
	// updateControllerLcd(0,initmessage);
	// pros::delay(50);
	// updateControllerLcd(1,blankline);
	// pros::delay(50);
	// updateControllerLcd(2,blankline);

	 while (true) {
		static int flag = 1;//holds whether or not to trigger screen update
		if (flag)
		{
		sprintf(line2,"JoyB:%d RobB:%f",controller.get_battery_capacity(),pros::battery::get_capacity());
	  // updateControllerLcd(2,line2);
		// 	updateControllerLcd();
			lasttime = pros::millis();//set last time updated to current system time
			flag = 0;//set that we have updated
		}
		if (lasttime + 5000 < pros::millis())//check if 50 ms have elapsed since last update
		{
			flag = 1;//set flag to request and update
		}
		// updateInfoScreen();
		readJoystick();
		driveControl();
		liftControl();
		rakeControl();
		launcherControl();
		ballIntakeControl();

		pros::delay(20);
	}
}
