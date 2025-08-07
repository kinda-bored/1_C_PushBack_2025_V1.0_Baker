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
#include "auton.h"
#include "auton_selector.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here




// test



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
<<<<<<< HEAD

  // making the options for auton left or right
  auton = 0.0; // Initialize auton variable to 0 (no selection)
  Brain.Screen.setPenColor(blue);
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
=======
  autonSelector();
>>>>>>> 6ec3d64 (Initial commit of paging everything project)

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
  if (auton == 1.0) {
    auton_left();
  } else if (auton == 1.1) {
    auton_left_match_loader();
  } else if (auton == 1.2) {
    auton_left_center_goal();
  } else if (auton == 1.3) {
    auton_left_side_goal();
  } else if (auton == 2.0) {
    auton_right();
  } else if (auton == 2.1) {
    auton_right_match_loader();
  } else if (auton == 2.2) {
    auton_right_center_goal();
  } else if (auton == 2.3) {
    auton_right_side_goal();
  } else if (auton == 3.0) {
    auton_skill();
  } else {
    // Default/fallback autonomous
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
