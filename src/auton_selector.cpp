#include "auton_selector.h"

using namespace vex;

double auton = 0.0;

void autonSelector() {
    // Draw auton options: Left, Right, Skills
    Brain.Screen.setPenColor(black);
    Brain.Screen.setFillColor(red);
    Brain.Screen.drawRectangle(10, 10, 150, 220);
    Brain.Screen.setCursor(6, 7);
    Brain.Screen.print("Left");
    Brain.Screen.setFillColor(blue);
    Brain.Screen.drawRectangle(170, 10, 150, 220);
    Brain.Screen.setCursor(6, 21);
    Brain.Screen.print("Right");
    Brain.Screen.setFillColor(green);
    Brain.Screen.drawRectangle(330, 10, 140, 220);
    Brain.Screen.setCursor(6, 33);
    Brain.Screen.print("Skills");

    // Wait for auton selection
    bool selected = false;
    int firstSelection = 0; // 1=Left, 2=Right, 3=Skills
    while (!selected) {
        waitUntil(Brain.Screen.pressing());
        int x = Brain.Screen.xPosition();
        Brain.Screen.setFillColor(white);
        Brain.Screen.drawRectangle(0, 0, 480, 240);
        Brain.Screen.setPenColor(black);
        if (x < 160) {
            Brain.Screen.print("Left Auton Selected");
            firstSelection = 1;
            selected = true;
        } else if (x < 320) {
            Brain.Screen.print("Right Auton Selected");
            firstSelection = 2;
            selected = true;
        } else {
            Brain.Screen.print("Skills Selected");
            firstSelection = 3;
            selected = true;
        }
        wait(500, msec); // debounce
    }

    // If left or right, show second page with more buttons
    if (firstSelection == 1 || firstSelection == 2) {
        Brain.Screen.setFillColor(white);
        Brain.Screen.drawRectangle(0, 0, 480, 240);
        Brain.Screen.setPenColor(black);
        Brain.Screen.setFillColor(purple);
        Brain.Screen.drawRectangle(10, 10, 150, 220);
        Brain.Screen.setCursor(6, 7);
        Brain.Screen.print("Match Loader");
        Brain.Screen.setFillColor(orange);
        Brain.Screen.drawRectangle(170, 10, 150, 220);
        Brain.Screen.setCursor(6, 21);
        Brain.Screen.print("Center Goal");
        Brain.Screen.setFillColor(yellow);
        Brain.Screen.drawRectangle(330, 10, 140, 220);
        Brain.Screen.setCursor(6, 33);
        Brain.Screen.print("Side Goal");

        bool subSelected = false;
        int subSelection = 0; // 1=Match Loader, 2=Center Goal, 3=Side Goal
        while (!subSelected) {
            waitUntil(Brain.Screen.pressing());
            int x = Brain.Screen.xPosition();
            Brain.Screen.setFillColor(white);
            Brain.Screen.drawRectangle(0, 0, 480, 240);
            Brain.Screen.setPenColor(black);
            if (x < 160) {
                Brain.Screen.print("cube rush Selected");
                subSelection = 1;
                subSelected = true;
            } else if (x < 320) {
                Brain.Screen.print("Center Goal Selected");
                subSelection = 2;
                subSelected = true;
            } else {
                Brain.Screen.print("Side Goal Selected");
                subSelection = 3;
                subSelected = true;
            }
            wait(500, msec); // debounce
        }
        // Set auton value based on selections
        if (firstSelection == 1) {
            auton = 1.0 + 0.1 * subSelection; // 1.1, 1.2, 1.3
        } else {
            auton = 2.0 + 0.1 * subSelection; // 2.1, 2.2, 2.3
        }
    } else if (firstSelection == 3) {
        auton = 3.0;
    }
}
