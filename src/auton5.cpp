#include "main.h"
#include "robot.h"
/**
* \details calls the fifth autonomous function
*/
void auton5()
{
  resetEncoders();
  motorSetup();
  //driveForward(100, 100,true);
  // driveBackward(100, 100,true);
  while(platformpresentred() != 1){delay(10);}
  //turnLeft(100, 100,true);
  //
  //turnRight(300, 100,true);
}
