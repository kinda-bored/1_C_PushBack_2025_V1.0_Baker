/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       jb3152                                                    */
/*    Created:      7/22/2025, 2:59:01 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "robot_config.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here








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
  vexcodeInit(); // Initialize the VEXcode devices
  // All activities that occur before the competition starts
  scraper.set(true); // Set the scrapper to the up position
  scraperUp = true; // Initialize the scrapper state to up
  // Set the initial velocity of the motors
  leftdrive.setVelocity(90, percentUnits::pct);
  rightdrive.setVelocity(90, percentUnits::pct);
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
