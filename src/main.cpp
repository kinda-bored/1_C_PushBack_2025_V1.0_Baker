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

  // making the options for auton left or right
  auton = 0.0; // Initialize auton variable to 0 (no selection)
  Brain.Screen.setPenColor(black);
  Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(10, 10, 230, 220);
  Brain.Screen.setCursor(6, 12);
  Brain.Screen.print("left auton");
  Brain.Screen.setFillColor(blue);
  Brain.Screen.drawRectangle(240, 10, 230, 220);
  Brain.Screen.setCursor(6, 36);
  Brain.Screen.print("right auton");
  while (true){
    waitUntil(Brain.Screen.pressing());
    if (Brain.Screen.xPosition() < 240.0) {
      Brain.Screen.setFillColor(white);
      Brain.Screen.drawRectangle(0, 0, 480, 240);
      Brain.Screen.print("right auton selcted");
      auton = 1.0;
      } else {
        Brain.Screen.setFillColor(white);
        Brain.Screen.drawRectangle(0, 0, 480, 240);
        Brain.Screen.print("left auton selcted");
        auton = 2.0;
      } 
      wait(5 ,seconds);
    wait(5, msec); // Wait for 5 milliseconds to prevent rapid looping
  }

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
  if (auton == 1.0){
    intakeGroup.spin(fwd,80, percentUnits::pct); // Start the intake motors
    Drivetrain.driveFor(25,inches); // Drive forward at 50% speed
    wait(1, seconds); // Wait for 1 second
    Drivetrain.turnFor(turnType::right, 120, degrees); // Turn right 90 degrees
    scraper.set(false); // Lower the scraper
    Drivetrain.driveFor(25,inches); // Drive forward at 50% speedemmaurrrr
    wait(2, seconds); // Wait for 1 second
    intakeGroup.stop(); // Stop the intake motors
    Drivetrain.driveFor(-10,inches); // Drive backward at 50% speed
    Drivetrain.turnFor(turnType::left, 180, degrees); // Turn left 90 degrees
    aligner.set(false); 
    Drivetrain.driveFor(15,inches); // Drive forward at 50% speed
    storage.spin(fwd, 80, percentUnits::pct); // Start the storage motor
    top.spin(reverse, 80, percentUnits::pct); // Start the top motor
    intake.spin(reverse, 80, percentUnits::pct); // Start the intake motor
    wait(4, seconds); // Wait for 2 seconds to allow the intake to collect
  }else if (auton == 2.0){
    intakeGroup.spin(fwd,80, percentUnits::pct); // Start the intake motors
    Drivetrain.driveFor(25,inches); // Drive forward at 50% speed
    wait(1, seconds); // Wait for 1 second
    Drivetrain.turnFor(turnType::left, 120, degrees); // Turn right 90 degrees
    scraper.set(false); // Lower the scraper
    Drivetrain.driveFor(25,inches); // Drive forward at 50% speedemmaurrrr
    wait(2, seconds); // Wait for 1 second
    intakeGroup.stop(); // Stop the intake motors
    Drivetrain.driveFor(-10,inches); // Drive backward at 50% speed
    Drivetrain.turnFor(turnType::right, 180, degrees); // Turn left 90 degrees
    aligner.set(false); 
    Drivetrain.driveFor(15,inches); // Drive forward at 50% speed
    storage.spin(fwd, 80, percentUnits::pct); // Start the storage motor
    top.spin(reverse, 80, percentUnits::pct); // Start the top motor
    intake.spin(reverse, 80, percentUnits::pct); // Start the intake motor
    wait(4, seconds); // Wait for 2 seconds to allow the intake to collect
  }else if(auton == 0.0){
    intakeGroup.spin(fwd,80, percentUnits::pct); // Start the intake motors
    Drivetrain.driveFor(25,inches); // Drive forward at 50% speed
  }
  
 
  
  
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
