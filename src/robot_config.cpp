#include "vex.h"
#include "robot_config.h"
using namespace vex;

brain Brain;
motor motor1 (PORT18, ratio18_1, false); // Motor on port 1 with 18:1 gear ratio
motor motor2(PORT19, ratio18_1, true);  // Motor
motor motor3(PORT20, ratio18_1, false); // Motor on port 3 with 18:1 gear ratio
motor_group leftdrive(motor1, motor2, motor3);
motor motor4(PORT1,ratio18_1, true); 
motor motor5(PORT2, ratio18_1, false); // Motor on port 5 with 18:1 gear ratio
motor motor6(PORT3, ratio18_1, true); // Motor on port 6 with 18:1 gear ratio
motor_group rightdrive(motor4, motor5, motor6);
motor intake(PORT12,ratio18_1, false); // Intake motor on port 7 with 18:1 gear ratio
motor storage(PORT13, false); // Storage motor on port 8 with 18:1 gear ratio
motor top(PORT11, false); // Top motor on port 9 with 18:1 gear ratio // Middle motor on port 10 with 18:1 gear ratio
motor_group intakeGroup(intake, storage, top); // Group for intake motors
digital_out scraper(Brain.ThreeWirePort.A);
controller Controller1 = controller(primary); // Controller for user input
drivetrain Drivetrain(leftdrive, rightdrive); // Drivetrain object using left and right motor groups
bool RemoteControlCodeEnabled = true; // A flag to control remote control code execution
bool Controller1LeftShoulderControlMotorsStopped = true;
bool Controller1RightShoulderControlMotorsStopped = true;
bool DrivetrainLNeedsToBeStopped_controller1 = true;
bool DrivetrainRNeedsToBeStopped_controller1 = true;
bool scrapperUp = true; // Variable to track the state of the scrapper
double turnSpeed = 0.5; // Default turn speed for the drivetrain

int rc_auto_loop_function_controller1(){
  while(true){
    if(RemoteControlCodeEnabled){
      int drivetrainLeftSideSpeed = Controller1.Axis3.position() - Controller1.Axis1.position()*turnSpeed;
      int drivetrainRightSideSpeed = Controller1.Axis3.position() + Controller1.Axis1.position()*turnSpeed;
      if(drivetrainLeftSideSpeed < 7 && drivetrainLeftSideSpeed > -7){
        if(DrivetrainLNeedsToBeStopped_controller1){
          leftdrive.stop();
          DrivetrainLNeedsToBeStopped_controller1 = false;
        }
      } else {
        DrivetrainLNeedsToBeStopped_controller1 = true;
      }
      if(drivetrainRightSideSpeed < 7 && drivetrainRightSideSpeed > -7){
        if(DrivetrainRNeedsToBeStopped_controller1){
          rightdrive.stop();
          DrivetrainRNeedsToBeStopped_controller1 = false;
        }
      } else {
        DrivetrainRNeedsToBeStopped_controller1 = true;
      }
      if(DrivetrainLNeedsToBeStopped_controller1){
        leftdrive.setVelocity(drivetrainLeftSideSpeed, percentUnits::pct);
        leftdrive.spin(directionType::fwd);
      }
      if(DrivetrainRNeedsToBeStopped_controller1){
        rightdrive.setVelocity(drivetrainRightSideSpeed, percentUnits::pct);
        rightdrive.spin(directionType::fwd);
      }
      if(Controller1.ButtonR1.pressing()){
        intake.spin(fwd, 80, percentUnits::pct);
        top.spin(fwd, 80, percentUnits::pct);
        storage.spin(fwd, 80, percentUnits::pct);
      } else if(Controller1.ButtonR2.pressing()){
        intake.spin(reverse, 30, percentUnits::pct);
        top.spin(reverse,80, percentUnits::pct);
        storage.spin(reverse, 80, percentUnits::pct);
      }else if(Controller1.ButtonL1.pressing()){
        storage.spin(fwd, 80, percentUnits::pct);
        top.spin(reverse, 80, percentUnits::pct);
        intake.spin(reverse, 80, percentUnits::pct);
      } else if(Controller1.ButtonL2.pressing()){
        intake.spin(fwd, 80, percentUnits::pct);
        top.spin(fwd, 80, percentUnits::pct);
        storage.spin(reverse, 80, percentUnits::pct);
      } else {
        intake.stop(hold);
        top.stop(hold);
        storage.stop(hold);
      }
      if(Controller1.ButtonA.pressing()){
        if(scrapperUp){
          scraper.set(true);
          scrapperUp = false;
        } else {
          scraper.set(false);
          scrapperUp = true;
        }
      }
      if(Controller1.ButtonDown.PRESSED){
        scraper.set(false);
        scrapperUp = false;
      } else if(Controller1.ButtonUp.PRESSED){
        scraper.set(true);
        scrapperUp = true;
      }
    }
    wait(20, msec); // Wait for 20 milliseconds to prevent CPU overload
  }
  return 0; // Return 0 to indicate successful execution
}
void vexcodeInit(void){
  task rc_auto_loop_function_controller1(rc_auto_loop_function_controller1); // Start the remote control auto loop function for Controller1
}
