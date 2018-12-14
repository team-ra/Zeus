#ifndef ROBOT_H
#define ROBOT_H
#include "main.h"
//defines
#define LEFT_DRIVE_MOTOR_1PORT 1
#define RIGHT_DRIVE_MOTOR_1PORT 20
#define LAUNCH_MOTOR_PORT 18
#define LIFT_MOTOR_PORT 5
#define WRIST_MOTOR_PORT 4
#define BALL_INTAKE_MOTOR_PORT 6
#define RIGHT_DRIVE_MOTOR_2PORT 8
#define LEFT_DRIVE_MOTOR2_PORT 9

#define BALL_SENSOR_PORT 'd'
#define COCKED_SENSOR_PORT 'b'
#define PLATFORM_SENSOR_PORT 'c'
#define LAUNCHER_ENCODER_COUNTS_TO_FIRE 6000
#define SHOOTER_THRESHOLD 250

#define PLATFORM_CONTACT_RED        1250

#define PLATFORM_NEAR_YELLOW        2860
#define PLATFORM_CONTACT_YELLOW     1900

#define PLATFORM_NEAR_BLUE          2830
#define PLATFORM_CONTACT_BLUE       2100

#define LIFT_MAX_HEIGHT -1100
#define LIFT_STACK_HEIGHT -1000
#define LIFT_GROUND_HEIGHT 10
#define LIFT_MAX_HEIGHT_PWR -127
#define LIFT_STACK_HEIGHT_PWR -75
#define LIFT_GROUND_HEIGHT_PWR 75

#define WRIST_FULL_LEFT 5
#define WRIST_FULL_RIGHT -800
//driver function prototypes
void driveControl();
void readJoystick();
void liftControl();
void wristControl();
void launcherControl();
void ballIntakeControl();
void updateControllerLcd(int line,char *linedata);
void motorSetup();
void swirl();
/************************************************/
//auton function prototypes
void driveForward(int counts,int power,bool zeromotors);
//int driveForward(int counts,int power,bool zeromotors);
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
void auton11();
void auton12();
// int setAutonMode();
// void startauto(int mode);
int shootBall();
void waitForSensorInit(int timeoutmillis);
int readIntakeButton(controller_digital_e_t button);
int readIntakeReverseButton(controller_digital_e_t button);
int readHalfSpeedButton(controller_digital_e_t button);
int readReverseControlsButton(controller_digital_e_t button);
int digitize(uint32_t value);
int filterCockedSensor();
int filterBallSensor();
void intakeOn(bool reverse);
void intakeOff();
void updateInfoScreen();
void leftDriveSet(int power);
void rightDriveSet(int power);
void resetEncoders();
int platformpresentblue();
int platformpresentred();
#endif
