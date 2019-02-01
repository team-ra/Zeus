#include "main.h"
#include "robot.h"
/**
* \details calls the third autonomous function.
*/
//marl2
void auton3()
{
  resetEncoders();
    intakeOn(false);
    while( driveForward(encoderInchesToCounts(42), 50, true) != 1);
    pros::delay(500);
    while( driveForward(encoderInchesToCounts(6), 50, true) != 1);
    pros::delay(1000);
    intakeOff();
    while( driveBackward(encoderInchesToCounts(18), 50, true) != 1);
    while( turnLeft(400,50,true) != 1);
    intakeOn(true);
    while( driveForward(encoderInchesToCounts(40), 75, true) != 1);
    intakeOff();
    //driveBackward(encoderInchesToCounts(50),100,true);
}
