#include "vex.h"
#include "robot_config.h"
using namespace vex;

brain Brain;
motor motor1 (PORT11, ratio18_1, false); // Motor on port 1 with 18:1 gear ratio
motor motor2(PORT12, ratio18_1, false);  // Motor
motor motor3(PORT13, ratio18_1, false); // Motor on port 3 with 18:1 gear ratio
motor_group leftdrive(motor1, motor2, motor3);
motor motor4(PORT1,ratio18_1, true); 
motor motor5(PORT2, ratio18_1, true); // Motor on port 5 with 18:1 gear ratio
motor motor6(PORT3, ratio18_1, true); // Motor on port 6 with 18:1 gear ratio
motor_group rightdrive(motor4, motor5, motor6);
motor intake(PORT9,ratio18_1, false); // Intake motor on port 7 with 18:1 gear ratio
motor storage(PORT10, false); // Storage motor on port 8 with 18:1 gear ratio
motor top(PORT8, false); // Top motor on port 9 with 18:1 gear ratio // Middle motor on port 10 with 18:1 gear ratio
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

int rc_auto_loop_function_controller1(){
  while(true){
    if(RemoteControlCodeEnabled){
      int drivetrainLeftSideSpeed = Controller1.Axis3.position() - Controller1.Axis1.position();
      int drivetrainRightSideSpeed = Controller1.Axis3.position() + Controller1.Axis1.position();
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
        intake.spin(fwd);
        top.spin(fwd);
        storage.spin(fwd);
      } else if(Controller1.ButtonR2.pressing()){
        intake.spin(reverse);
        top.spin(reverse);
        storage.spin(reverse);
      } else {
        intake.stop();
        top.stop();
        storage.stop();
      }
      if(Controller1.ButtonL1.pressing()){
        storage.spin(reverse);
        top.spin(fwd);
      }else if(Controller1.ButtonL2.pressing()){
        storage.spin(reverse);
        top.spin(reverse);
        intake.spin(forward);
      } else {
        storage.stop();
        top.stop();
        intake.stop();
      }
      if(Controller1.ButtonUp.pressing()){
        if(scrapperUp){
          scraper.set(true);
          scrapperUp = false;
        }else if(Controller1.ButtonDown.pressing()){
          scraper.set(false);
          scrapperUp = true;
        }
      }
    }
  }
}
