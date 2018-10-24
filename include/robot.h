#ifndef ROBOT_H
#define ROBOT_H
//defines
#define LEFT_DRIVE_MOTOR_PORT 1
#define RIGHT_DRIVE_MOTOR_PORT 2
#define LAUNCH_MOTOR_PORT 3
#define WRIST_MOTOR_PORT 4
#define LIFT_MOTOR_PORT 5
#define BALL_INTAKE_MOTOR_PORT 6
#define LINE_SENSOR_PORT 'd'
#define LINE_SENSOR_PORT2 'b'
#define LAUNCHER_ENCODER_COUNTS_TO_FIRE 6000


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
void auton1();
void auton2();
void auton3();
void auton4();
void auton5();
void auton6();
void auton7();
void auton8();
void auton9();
void auton10();
int setAutonMode();
void startauto(int mode);
void shootBall();
void waitForSensorInit(int timeoutmillis);
#endif
