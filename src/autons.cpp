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
  
}
void far_qual() {
  
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