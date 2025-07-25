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
motor intake(PORT7, false); // Intake motor on port 7 with 18:1 gear ratio
motor storage(PORT8, false); // Storage motor on port 8 with 18:1 gear ratio
motor top(PORT9, false); // Top motor on port 9 with 18:1 gear ratio
motor middle(PORT10, false); // Middle motor on port 10 with 18:1 gear ratio
digital_out scraper(Brain.ThreeWirePort.A);
controller Controller1 = controller(primary); // Controller for user input







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
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
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
