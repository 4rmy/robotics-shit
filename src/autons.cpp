#include "autons.hpp"
#include "pros/motors.hpp"

const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;

// Mechs
pros::Motor kicker(17);
pros::Motor intake(15);
pros::ADIDigitalOut wings('a');
pros::ADIDigitalOut pto('b');
pros::ADIDigitalOut arm('c');

//
// Autons
//
void close_qual() {
  /*

    1. Roll alliance triball to goal
    2. Grab center triball
    3. Get corner triball out
    4. Roll all balls under
    5. Touch bar
  
  */
  intake = -127;
  pros::delay(400);
  chassis.set_turn_pid(80, TURN_SPEED);
  chassis.wait_drive();

  intake = 127;
  chassis.set_drive_pid(24, 127);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, 127);
  chassis.wait_drive();

  // arm down

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  // arm up

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-6, 127);
  chassis.wait_drive();

  chassis.set_turn_pid(135, TURN_SPEED);
  chassis.wait_drive();

  intake = -127;
  pros::delay(400);

  chassis.set_turn_pid(-40, TURN_SPEED);
  chassis.wait_drive();

  intake = 0;

  chassis.set_drive_pid(-14, 127);
  chassis.wait_drive();

  chassis.set_turn_pid(-30, TURN_SPEED);
  chassis.wait_drive();

  // arm down
}
void far_qual() {
  /*

    1. Slap alliance triball
    2. Grab top triball
    3. Score middle 2 triballs
    4. Grab third triball
  
  */
}
void close_elim() {
  
}
void far_elim() {

}
void skills() {
  
}
void back() {
  chassis.set_tank(-127, -127);
  pros::delay(5000);
  chassis.set_tank(100, 100);
  pros::delay(2000);
  chassis.set_tank(0,0);
}

// used for no auton if necessary
//    (its a failsafe)
void blank() {}