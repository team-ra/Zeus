#include "main.h"
#include "robot.h"
/**
* \details calls the third autonomous function.
*/
//marl2
void auton3()
{
    intakeOn(false);
    driveForward(encoderInchesToCounts(40), 50, true);
    pros::delay(250);
    intakeOff();
    driveBackward(encoderInchesToCounts(20), 50,true);
    turnLeft(300,50,true);
    intakeOn(true);
    driveForward(encoderInchesToCounts(20), 100, true);
    intakeOff();
    driveBackward(encoderInchesToCounts(50),100,true);
}
