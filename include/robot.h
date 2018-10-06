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
void swirl();
/************************************************/
//auton function prototypes
void driveForward(int counts,int power,bool zeromotors);
void driveBackward(int counts,int power,bool zeromotors);
void turnLeft(int counts,int power,bool zeromotors);
void turnRight(int counts,int power,bool zeromotors);
int encoderInchesToCounts(float inches);
#endif
