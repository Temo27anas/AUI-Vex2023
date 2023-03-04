#include "vex.h"

using namespace vex;

//______________________________________________________________________

brain Brain;

controller Controller1 = controller(primary);

//__________Chassis__________
motor leftTopMotor = motor(PORT14, ratio18_1, false);
motor leftBottomMotor = motor(PORT20, ratio18_1, false);
motor rightTopMotor = motor(PORT15, ratio18_1, true);
motor rightBottomMotor = motor(PORT13, ratio18_1, true);

//__________Grabbing System__________
motor UpperGrabber = motor(PORT2, ratio18_1, false);
motor LowerGrabber = motor(PORT16, ratio18_1, false);
motor_group GrabberGroup = motor_group(UpperGrabber, LowerGrabber);

//__________Roller Spinner__________
motor RollerSpinner = motor(PORT12, ratio18_1, false);

//__________Disk Gate__________
motor DiskGate = motor(PORT11, ratio18_1, false);

//__________Flywheel__________
motor FlywheelBack = motor(PORT17, ratio18_1, true);
motor FlywheelFront = motor(PORT18, ratio18_1, false);
motor_group FlywheelGroup = motor_group(FlywheelBack, FlywheelFront);

//___________Pneumatic__________
led PneumaticA = led(Brain.ThreeWirePort.D);
led PneumaticB = led(Brain.ThreeWirePort.E);



//If i am holding button Start the roller spinner, if i am not holding the button stop the roller spinner

void RotateRollerSpinnerForward() {
  while (Controller1.ButtonUp.pressing()) {
    RollerSpinner.spin(fwd);
    RollerSpinner.setVelocity(50, pct);
  }
  wait(0.5, seconds);
}

void StopRollerSpinner() { RollerSpinner.stop(); }

void RotateRollerSpinnerReverse() {
  while (Controller1.ButtonDown.pressing()) {
    RollerSpinner.spin(fwd);
    RollerSpinner.setVelocity(-50, pct);
  }
  wait(0.5, seconds);
}





void StopGroupGrabber() { GrabberGroup.stop(); }

void Controls() {
  rightTopMotor.spin(vex::directionType::fwd, -Controller1.Axis3.position() - Controller1.Axis1.position() + Controller1.Axis4.position(), vex::velocityUnits::pct);
  rightBottomMotor.spin(vex::directionType::fwd, -Controller1.Axis3.position() - Controller1.Axis1.position() - Controller1.Axis4.position(),  vex::velocityUnits::pct);
  leftBottomMotor.spin(vex::directionType::fwd, -Controller1.Axis3.position() + Controller1.Axis1.position() +  Controller1.Axis4.position(), vex::velocityUnits::pct);
  leftTopMotor.spin(vex::directionType::fwd, -Controller1.Axis3.position() + Controller1.Axis1.position() - Controller1.Axis4.position(), vex::velocityUnits::pct);
}



void StartGrabber() {
  while (Controller1.ButtonR1.pressing()) {
    LowerGrabber.spin(fwd, 100, pct);
    UpperGrabber.spin(fwd, 100, pct);
    
    
  }
  wait(0.5, seconds);
}

void StartGrabberReverse() {
  while (Controller1.ButtonL1.pressing()) {
    LowerGrabber.spin(reverse, 100, pct);
    UpperGrabber.spin(reverse, 100, pct);
    
    // vex::this_thread::sleep_for(50);
  }
  wait(0.5, seconds);
}



void setVelocitiesMax(){
  leftTopMotor.setVelocity(100, pct);
  leftBottomMotor.setVelocity(100, pct);
  rightBottomMotor.setVelocity(100, pct);
  rightTopMotor.setVelocity(100, pct);
 
}

void Roller(){
//int pos = Controller1.Axis2.position();
RollerSpinner.spin(forward,
              Controller1.Axis2.position(), pct);



}



void vexcodeInit(void) {

  setVelocitiesMax();


  Controller1.ButtonL1.released(StopGroupGrabber);
  Controller1.ButtonR1.released(StopGroupGrabber);
  Controller1.ButtonUp.released(StopRollerSpinner);
  Controller1.ButtonDown.released(StopRollerSpinner);




  int flag = 0;
  int flag1 = 0;
  bool PneumaticFlag = false;
  while (1) {


    vex::thread ControlsThread(Controls);
    vex::thread ShooterThread(StartGrabberReverse);
    vex::thread SpinnerThread(StartGrabber);
    thread RollerThread(Roller);
    //vex::thread RotateRollerSpinnerThread(RotateRollerSpinnerForward);
    //vex::thread RotateRollerSpinnerReverseThread(RotateRollerSpinnerReverse);

    //Cont
    while(Controller1.ButtonR2.pressing() && Controller1.ButtonL2.pressing()){
    if(PneumaticFlag == false){
      PneumaticA.on();
      PneumaticB.on();
      PneumaticFlag = true;
    }
    else{
      PneumaticA.off();
      PneumaticB.off();
      PneumaticFlag = false;
    }
    wait(400, msec);
    }

    //Diskgate
    /*while (Controller1.ButtonLeft.pressing()) {
      if (flag == 0) {
        //
        DiskGate.spinFor(fwd, 46, degrees);
        flag = 1;
      } else {
        DiskGate.spinFor(reverse, 46, degrees);
        flag = 0;
      }
      wait(0.5, seconds);
    }*/

    //Flywheel: Turning On/Of
    while (Controller1.ButtonB.pressing()) {
      if (flag1 == 0) {
        DiskGate.spinFor(fwd, 46, degrees);
        FlywheelBack.spin(fwd, 100, pct);
        FlywheelFront.spin(fwd, 100, pct);
        flag1 = 1;
      } else {
        DiskGate.spinFor(reverse, 46, degrees);
        FlywheelGroup.stop();
        flag1 = 0;
      }
      wait(0.5, seconds);
    }


    while (Controller1.ButtonX.pressing()) {



      if (flag1 == 0) {
        DiskGate.spinFor(fwd, 46, degrees);
        FlywheelBack.spin(fwd, 70, pct);
        FlywheelFront.spin(fwd, 70, pct);
        flag1 = 1;
      } else {
        DiskGate.spinFor(reverse, 46, degrees);
        FlywheelGroup.stop();
        flag1 = 0;
      }
      wait(0.5, seconds);
    }
  }
  //Pneumatic



  vex::this_thread::sleep_for(50);

}

