#include "autons.hpp"
#include "pros/motors.hpp"

const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;

pros::Motor kicker(14);

//
// Autons
//
/*
void left_side_winpoint() {
  intake = 127;

  chassis.set_drive_pid(8, 127);
  chassis.wait_drive();

  intake = 0;

  chassis.set_turn_pid(30, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(2, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(40, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(7, 127);
  intake = -127;
  chassis.wait_until(4);
  intake = 0;
  chassis.wait_drive();

  chassis.set_drive_pid(-6, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  wings.set_value(true);

  chassis.set_drive_pid(-6, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-6, DRIVE_SPEED);
  chassis.wait_drive();

  wings.set_value(false);

  chassis.set_turn_pid(-180, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(4, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-230, TURN_SPEED);
  chassis.wait_drive();

  intake = -127;

  chassis.set_drive_pid(8.5, DRIVE_SPEED*2/3);
  chassis.wait_drive();
}

void right_side_winpoint() {
  intake = 127;

  chassis.set_drive_pid(8, 127);
  chassis.wait_drive();

  intake = 0;

  chassis.set_turn_pid(-30, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(2, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-40, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(6, 127);
  intake = -127;
  chassis.wait_until(4);
  intake = 0;
  chassis.wait_drive();

  chassis.set_drive_pid(-2.5, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-130, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(14, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-100, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(8, DRIVE_SPEED);
  intake = 127;
  chassis.wait_drive();
  intake = 0;

  chassis.set_turn_pid(15, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(14, 127);
  chassis.wait_until(8);
  intake = -127;
  chassis.wait_drive();
  intake = 0;

  chassis.set_drive_pid(-3, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-175, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-5, 127);
  chassis.wait_drive();

  chassis.set_drive_pid(17, 127);
  chassis.wait_drive();
}

void aggressive_left_elim() {
  intake = 127;
  chassis.set_drive_pid(22, DRIVE_SPEED);
  chassis.wait_until(12);
  wings.set_value(true);
  chassis.wait_until(22);
  wings.set_value(false);
  chassis.wait_drive();

  chassis.set_drive_pid(-3, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(135, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(9, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(160, TURN_SPEED);
  chassis.wait_drive();

  intake = -127;

  chassis.set_drive_pid(2, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-2, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(250, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(7, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(160, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(10, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(70, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(10, DRIVE_SPEED);
  chassis.wait_drive();

  intake = 0;

  chassis.set_drive_pid(-15, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(115, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-8, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(160, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-8, 127);
  chassis.wait_drive();
}

void aggressive_right_elim() {
  intake = 127;
  chassis.set_drive_pid(26, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(115, TURN_SPEED);
  chassis.wait_drive();

  wings.set_value(true);

  chassis.set_drive_pid(12, 127);
  chassis.wait_until(4);
  intake = -127;
  chassis.wait_drive();
  intake = 0;

  wings.set_value(false);

  chassis.set_drive_pid(-2, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(260, TURN_SPEED);
  chassis.wait_drive();

  intake = 127;
  chassis.set_drive_pid(13, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(175, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(20, DRIVE_SPEED);
  chassis.wait_drive();

  wings.set_value(true);

  chassis.set_turn_pid(80, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(3.5, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(35, TURN_SPEED);
  chassis.wait_drive();

  wings.set_value(false);

  chassis.set_turn_pid(80, TURN_SPEED);
  chassis.wait_drive();

  intake = -127;
  chassis.set_drive_pid(8, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-130, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-6, 127);
  chassis.wait_drive();

  chassis.set_drive_pid(2, 127);
  chassis.wait_drive();
}
*/

void skills() {
  
  pros::delay(35000);

  chassis.set_tank(-127, -127);
  pros::delay(5000);
  chassis.set_tank(100, 100);
  pros::delay(3000);
  chassis.set_tank(0,0);
}

void back() {
  chassis.set_tank(-127, -127);
  pros::delay(10000);
  chassis.set_tank(20,20);
  pros::delay(3000);
  chassis.set_tank(0,0);
}

// used for no auton if necessary
//    (its a failsafe)
void blank() {}