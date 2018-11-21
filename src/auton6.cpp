#include "main.h"
#include "robot.h"

void auton6()
{
intakeOn(false);
driveForward(encoderInchesToCounts(40), 50, true);
pros::delay(250);
intakeOff();
driveBackward(encoderInchesToCounts(12), 50,true);

}
