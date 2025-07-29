/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       jb3152                                                    */
/*    Created:      7/22/2025, 2:59:01 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
brain Brain;
motor motor1 (PORT1, ratio18_1, false); // Motor on port 1 with 18:1 gear ratio
motor motor2(PORT2, ratio18_1, false);  // Motor
motor motor3(PORT3, ratio18_1, false); // Motor on port 3 with 18:1 gear ratio
motor_group leftdrive(motor1, motor2, motor3);
motor motor4(PORT4,ratio18_1, true); 
motor motor5(PORT5, ratio18_1, true); // Motor on port 5 with 18:1 gear ratio
motor motor6(PORT6, ratio18_1, true); // Motor on port 6 with 18:1 gear ratio
motor_group rightdrive(motor4, motor5, motor6);
motor intake(PORT7,ratio18_1, false); // Intake motor on port 7 with 18:1 gear ratio
motor storage(PORT8, false); // Storage motor on port 8 with 18:1 gear ratio
motor top(PORT9, false); // Top motor on port 9 with 18:1 gear ratio // Middle motor on port 10 with 18:1 gear ratio
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






/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

  // All activities that occur before the competition starts
  scraper.set(true); // Set the scrapper to the up position
  scrapperUp = true; // Initialize the scrapper state to up
  // Set the initial velocity of the motors
  leftdrive.setVelocity(100, percentUnits::pct);
  rightdrive.setVelocity(100, percentUnits::pct);
  intake.setVelocity(100, percentUnits::pct);
  top.setVelocity(100, percentUnits::pct);
  storage.setVelocity(100, percentUnits::pct);
  // Set the stopping mode of the motors
  leftdrive.setStopping(brakeType::brake);
  rightdrive.setStopping(brakeType::brake);
  intake.setStopping(brakeType::brake);
  top.setStopping(brakeType::brake);
  storage.setStopping(brakeType::brake);
  Drivetrain.setTurnVelocity(50, percentUnits::pct); // Set the turn velocity of the drivetrain
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  
  intakeGroup.spin(fwd); // Start the intake motors
  Drivetrain.driveFor(25,inches, 90, rpm); // Drive forward at 50% speed
  wait(1, seconds); // Wait for 1 second
  Drivetrain.turnFor(turnType::right, 90, degrees); // Turn right 90 degrees
  Drivetrain.driveFor(25,inches); // Drive forward at 50% speed
  Drivetrain.turnFor(turnType::left, 90, degrees); // Turn left 90 degrees
  Drivetrain.driveFor(25,inches); // Drive forward at 50% speed
  wait(1, seconds); // Wait for 1 second
  intakeGroup.stop(); // Stop the intake motors
  top.spin(fwd); // Start the top motor
  storage.spin(reverse); // Start the storage motor
  wait(5, seconds);
  Drivetrain.driveFor(-25,inches); 
  
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
