#include "main.h"
#include "robot.h"
#define THRESHOLD 800
using namespace pros::literals;
int digitize(int value)
{
  int threshold = THRESHOLD;
  if (value < threshold) {return 0;}
  else if (value > threshold) {return 1;}
}
int sensorRead(char sensor){
  int sensorvalue = 0;
  pros::ADILineSensor sensorinst(sensor);
  sensorvalue = digitize(sensorinst.get_value());
    for (int i = 0; i < 5;i++){
      sensorvalue = sensorvalue << 1 | digitize(sensorinst.get_value());
      pros::delay(30);
    }
    if (sensorvalue & 0x3F == 0x3F){
      return 1;
    }
}


// void shootBall(){
//
// }
