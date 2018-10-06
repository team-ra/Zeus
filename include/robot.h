#ifndef ROBOT_H
#define ROBOT_H
//driver function prototypes
void driveControl();
void readJoystick();
void liftControl();
void wristControl();
void launcherControl();
void ballIntakeControl();
void updateControllerLcd();
void motorSetup();
/************************************************/
//auton function prototypes
void driveForward(int counts,int power);
void driveBackward(int counts,int power);
void turnLeft(int counts);
void turnRight(int counts);
int encoderInchesToCounts(float inches);
#endif
