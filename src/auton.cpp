#include "robot_config.h"
#include "vex.h"
using namespace vex;

void auton_right() {
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
}
void auton_left() {
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
}
void auton_skill() {
}

// Sub-autons for left
void auton_left_match_loader() {
    // Add code for left match loader auton
}
void auton_left_center_goal() {
    // Add code for left center goal auton
}
void auton_left_side_goal() {
    // Add code for left side goal auton
}

// Sub-autons for right
void auton_right_match_loader() {
    // Add code for right match loader auton
}
void auton_right_center_goal() {
    // Add code for right center goal auton
}
void auton_right_side_goal() {
    // Add code for right side goal auton
}
  // Autonomous code for the skill challenge
  // Add your autonomous logic here
