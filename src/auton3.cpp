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
    driveForward(encoderInchesToCounts(42), 50, true);
    pros::delay(500);
    driveBackward(encoderInchesToCounts(6), 50,true);
    pros::delay(1000);
    intakeOff();
    driveBackward(encoderInchesToCounts(18), 50,true);
    turnLeft(400,50,true);
    intakeOn(true);
    driveForward(encoderInchesToCounts(40), 75, true);
    intakeOff();
    //driveBackward(encoderInchesToCounts(50),100,true);
}
