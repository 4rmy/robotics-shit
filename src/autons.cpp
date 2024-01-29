#include "autons.hpp"
#include "EZ-Template/util.hpp"
#include "pros/motors.hpp"

const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;

// Mechs
pros::Motor hang1(19);
pros::Motor hang2(20);
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
  hang1 = 127;
  hang2 = 127;
  pros::delay(400);
  chassis.set_turn_pid(80, TURN_SPEED);
  chassis.wait_drive();
  hang1 = -127;
  hang2 = -127;

  intake = 127;
  chassis.set_drive_pid(24.5, 127);
  chassis.wait_drive();

  hang1 = 0;
  hang2 = 0;

  chassis.set_drive_pid(-24, DRIVE_SPEED);
  chassis.wait_drive();

  // arm down

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  // arm up

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-6, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(135, TURN_SPEED);
  chassis.wait_drive();

  intake = -127;
  pros::delay(400);

  chassis.set_turn_pid(-40, TURN_SPEED);
  chassis.wait_drive();

  intake = 0;

  chassis.set_drive_pid(-14.5, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(3, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-20, TURN_SPEED);
  chassis.wait_drive();

  // arm down
} // TEST ME
void far_qual() {
  /*

    1. Slap alliance triball
    2. Grab top triball
    3. Score middle 2 triballs
    4. Grab third triball
  
  */

  // wings out
  pros::delay(200);
  // wings in
  
  intake = 127;

  chassis.set_drive_pid(25, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(130, TURN_SPEED);
  chassis.wait_drive();

  // wings out
  intake = -127;
  chassis.set_drive_pid(16, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-6, DRIVE_SPEED);
  chassis.wait_drive();

  intake = 127;
  chassis.set_turn_pid(270, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(12, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(130, TURN_SPEED);
  chassis.wait_drive();

  intake = -127;
  chassis.set_drive_pid(12, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::RIGHT_SWING, -90, DRIVE_SPEED);
  chassis.wait_drive();

} // START ME
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