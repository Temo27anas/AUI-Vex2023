#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;

controller Controller1 = controller(primary);
//Chassis
motor RightWheel = motor(PORT20, ratio18_1, true); 
motor LeftWheel = motor(PORT18, ratio18_1, false); 
motor_group Chassis = motor_group(LeftWheel, RightWheel);
//Spinner
motor SpinnerMotor = motor(PORT17, ratio18_1, true); 
//Catapult
motor CatapultMotor1 = motor(PORT13, ratio18_1, true);  
motor CatapultMotor2 = motor(PORT16, ratio18_1, false); 
motor_group CatapultGroup = motor_group(CatapultMotor1, CatapultMotor2);
//Expansion
motor ExpansionMotor1 = motor(PORT14, ratio18_1, true);  
motor ExpansionMotor2 = motor(PORT15, ratio18_1, false); 
motor_group ExpansionGroup = motor_group(ExpansionMotor1, ExpansionMotor2);
//Inirtial Sensor
inertial InertialSensor = inertial(PORT1);  //TO FIX

limit CatLimit = limit(Brain.ThreeWirePort.A);

//Functions: 
//Move Forward/Backward for a distance
void MoveRobotForward(bool IsForward, int distance, int speed) {
  double degrees = ((distance-5) / 5.08) * ( 180 / 3.14);

  if (IsForward) {
    // Move forward for a degres
    Brain.Screen.printAt(10, 10, "degrees: %f", degrees);
    Chassis.spinFor(forward,degrees, deg, 2*speed, rpm);
    
    
  } else {
    Chassis.spinFor(reverse, degrees, deg , 2*speed ,  rpm);
  }
  RightWheel.stop();
  LeftWheel.stop();
}
//Turn Left/Right for an angle
void TurnRobotRight(bool IsRight, int speed, int angle) {
  double Inityaw = InertialSensor.rotation();
  double yaw = InertialSensor.rotation();
  if (IsRight) {
    while (abs(yaw - Inityaw) < angle) {
      LeftWheel.spin(forward, speed, pct);
      RightWheel.spin(reverse, speed/2, pct);
      yaw = InertialSensor.rotation();
    }


  } else {
      while (abs(yaw - Inityaw) < angle){
      RightWheel.spin(forward, speed, pct);
      LeftWheel.spin(reverse, speed/2, pct);
      yaw = InertialSensor.rotation();
    }
  }
  RightWheel.stop();
  LeftWheel.stop();
}

// Spin the spinner
void SpinSpinnerFor(int seconds, int speed){
  SpinnerMotor.spin(forward, speed, pct);
  Chassis.spin(forward, 60,  pct);
  wait(seconds, sec);
  SpinnerMotor.stop();
  Chassis.stop();
}

//intirtial sensor
void InertialSensorCalibrate(){
  InertialSensor.calibrate();
  while(InertialSensor.isCalibrating()){
    wait(100, msec);
  }
}





void vexcodeInit(void) {
  
  InertialSensorCalibrate();
  MoveRobotForward(true, 20, 70);
  TurnRobotRight( true, 50, 90);
  MoveRobotForward(true, 43, 70);
  TurnRobotRight(true, 50, 75);
  SpinSpinnerFor(3, 100);
  MoveRobotForward(false, 10,  70);


  






}