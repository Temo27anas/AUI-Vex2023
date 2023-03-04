#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 Brain screen

// controller Controller1 = controller(primary);

motor release =  motor(PORT12, ratio18_1, false);
motor leftMotorA = motor(PORT13, ratio18_1, false);
motor leftMotorB = motor(PORT15, ratio18_1, false);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);
motor rightMotorA = motor(PORT20, ratio18_1, true);
motor rightMotorB = motor(PORT14, ratio18_1, true);
motor Flywheelback = motor(PORT17,ratio18_1,false);
motor Flywheelfront = motor(PORT18,ratio18_1,true);
motor_group Flywheel = motor_group(Flywheelback,Flywheelfront);
motor grabberu= motor(PORT2,ratio18_1,true);
motor grabberl= motor(PORT16,ratio18_1,true);
motor_group grabber = motor_group(grabberu,grabberl);
inertial inertiasensor = inertial(PORT19);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 295, 40, mm, 1);

void Aut1()  {
  //Slide
  rightMotorA.spin(vex::directionType::fwd, -20, vex::velocityUnits::pct);
  rightMotorB.spin(vex::directionType::fwd,20 ,  vex::velocityUnits::pct);
  leftMotorB.spin(vex::directionType::fwd,-20, vex::velocityUnits::pct);
  leftMotorA.spin(vex::directionType::fwd, 20, vex::velocityUnits::pct);
  wait(3, sec);
  //stop
  rightMotorA.stop();
  rightMotorB.stop();
  leftMotorB.stop();
  leftMotorA.stop();
  //roller
  Drivetrain.setDriveVelocity(50, pct);
  Drivetrain.turnFor(37, degrees);
  inertiasensor.calibrate();
  release.spin(forward,-100,pct);
  wait(0.5, seconds);
  //stop
  release.stop();
 
  Flywheel.spin(fwd,100,pct);
  wait(4, sec);
  grabber.spin(reverse, 100, pct);
  wait(4, sec);
  grabber.stop();
  Flywheel.stop();
  Drivetrain.setDriveVelocity(30, pct);
  Drivetrain.driveFor(fwd,150, mm);
  Drivetrain.setDriveVelocity(60, pct);
  Drivetrain.turnFor(-137, degrees);
  inertiasensor.calibrate();
  Drivetrain.driveFor(fwd,300, mm);
  Drivetrain.turnFor(387, degrees);
  inertiasensor.calibrate();
  rightMotorA.spin(vex::directionType::fwd, -20, vex::velocityUnits::pct);
  rightMotorB.spin(vex::directionType::fwd,20 ,  vex::velocityUnits::pct);
  leftMotorB.spin(vex::directionType::fwd,-20, vex::velocityUnits::pct);
  leftMotorA.spin(vex::directionType::fwd, 20, vex::velocityUnits::pct);
  wait(0.75, sec);
  grabber.spin(reverse, 100, pct);
  Drivetrain.driveFor(fwd,-1500, mm);
  grabber.stop();
  Drivetrain.turnFor(-180, degrees);
  inertiasensor.calibrate();
  rightMotorA.spin(vex::directionType::fwd, -20, vex::velocityUnits::pct);
  rightMotorB.spin(vex::directionType::fwd,20 ,  vex::velocityUnits::pct);
  leftMotorB.spin(vex::directionType::fwd,-20, vex::velocityUnits::pct);
  leftMotorA.spin(vex::directionType::fwd, 20, vex::velocityUnits::pct);
  wait(0.6 , sec);
  Drivetrain.stop();

}





void Aut2()
{
   Drivetrain.setDriveVelocity(80, pct);
   Drivetrain.driveFor(forward, 300, mm );
    rightMotorA.spin(vex::directionType::fwd, -20, vex::velocityUnits::pct);
  rightMotorB.spin(vex::directionType::fwd,20 ,  vex::velocityUnits::pct);
  leftMotorB.spin(vex::directionType::fwd,-20, vex::velocityUnits::pct);
  leftMotorA.spin(vex::directionType::fwd, 20, vex::velocityUnits::pct);
  wait(5, sec);
  Drivetrain.stop();
   grabber.spin(reverse,100,pct);
   Drivetrain.turnFor(-20, degrees);
     inertiasensor.calibrate();
  Flywheel.spin(fwd,60,pct);
  wait(4, sec);
  grabber.spin(reverse, 60, pct);
  wait(4, sec);
  //functions();

   //Drivetrain.driveFor(forward,150, mm); 
   //grabber.spin(fwd,100,pct);

//Flywheel.spin(fwd,100,pct);
  wait(6, sec);

  Drivetrain.driveFor(reverse,300,mm);
  //grabber.spin(reverse, 100, pct);
  //wait(4, sec);
  grabber.stop();
  Flywheel.stop(); 
    Drivetrain.stop();
  

}
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */

void functions( ) {
  // Nothing to initialize
  Drivetrain.setDriveVelocity(60, pct);
  Drivetrain.driveFor(reverse, 300, mm );
  Drivetrain.turnFor(80, degrees);
  inertiasensor.calibrate();
  Drivetrain.drive(reverse );
  wait(3, sec);
  Drivetrain.stop();
  Drivetrain.drive(forward );
  wait(1, sec);
  Drivetrain.stop();
}


void vexcodeInit( void ) {


 //Aut1();
 //Aut2();
functions();



}