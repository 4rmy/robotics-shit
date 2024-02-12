#include "autons.hpp"
#include "EZ-Template/util.hpp"
#include "pros/motors.hpp"

const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed). We
                             // don't suggest making this 127.
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;

// Mechs
pros::Motor intake(15);
pros::ADIDigitalOut wings('a');
pros::ADIDigitalOut pto('b');
pros::ADIDigitalOut arm('c');

pros::Motor_Group hang({19, 20});

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
  hang = -127;
  pros::delay(1200);
  chassis.set_turn_pid(80, TURN_SPEED);
  chassis.wait_drive();

  intake = 127;
  chassis.set_drive_pid(23.9, 127);
  chassis.wait_until(16);
  hang = 0;
  chassis.wait_drive();

  pros::delay(400);

  chassis.set_drive_pid(-23.5, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  pros::delay(100);
  arm.set_value(true);
  chassis.wait_drive();

  arm.set_value(false);

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-6, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(135, TURN_SPEED);
  chassis.wait_drive();

  intake = -127;
  pros::delay(400);

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  intake = 0;

  chassis.set_drive_pid(-14.5, DRIVE_SPEED);
  chassis.wait_drive();
}
void far_qual() {
  /*

    1. Slap alliance triball
    2. Grab top triball
    3. Score middle 2 triballs
    4. Grab third triball

  */

  wings.set_value(true);
  hang = -127;
  pros::delay(800);
  wings.set_value(false);
  intake = 127;

  chassis.set_drive_pid(25, 127);
  chassis.wait_drive();

  chassis.set_turn_pid(130, TURN_SPEED);
  chassis.wait_drive();

  hang = 0;

  wings.set_value(true);
  intake = -127;
  chassis.set_drive_pid(14, 127);
  chassis.wait_drive();
  wings.set_value(false);

  chassis.set_drive_pid(-6, DRIVE_SPEED);
  chassis.wait_drive();

  intake = 127;
  chassis.set_turn_pid(270, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(12, 127);
  chassis.wait_drive();

  chassis.set_turn_pid(150, TURN_SPEED);
  chassis.wait_drive();

  intake = 0;

  chassis.set_drive_pid(14, 127);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::RIGHT_SWING, 45, 127);
  chassis.wait_drive();

  intake = -127;

  chassis.set_drive_pid(6, 127);
  chassis.wait_drive();

  chassis.set_drive_pid(-6, 127);
  chassis.wait_drive();

  chassis.set_turn_pid(60, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-6, 127);
  chassis.wait_drive();

  chassis.set_turn_pid(110, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-16, 127);
  chassis.wait_drive();

}
void close_elim() {
  hang = -127;
  arm.set_value(true);
  pros::delay(50);
  hang = 0;
  pros::delay(100);
  arm.set_value(false);

  intake = 127;
  chassis.set_drive_pid(21, DRIVE_SPEED);
  chassis.wait_drive();
  pros::delay(500);
  chassis.set_drive_pid(-21, DRIVE_SPEED*2/3);
  chassis.wait_drive();

  chassis.set_turn_pid(125, TURN_SPEED);
  chassis.wait_drive();

  intake = -127;
  pros::delay(500);

  chassis.set_drive_pid(-16, 127);
  chassis.wait_drive();

  chassis.set_turn_pid(130, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(9, 127);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  arm.set_value(true);
  pros::delay(100);

  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();

  pros::delay(100);

  arm.set_value(false);

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-8, 127);
  chassis.wait_drive();

  chassis.set_turn_pid(-100, TURN_SPEED);
  chassis.wait_drive();

  hang = -127;

  chassis.set_drive_pid(-14, 127);
  chassis.wait_drive();

  pros::delay(1300);
  hang = 0;
  intake = 0;
}
void far_elim() {
  hang = -127;
  intake = 127;
  pros::delay(50);
  hang = 0;
  pros::delay(650);

  chassis.set_drive_pid(-14, 127);
  chassis.wait_drive();

  chassis.set_turn_pid(-40, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-6, 127);
  arm.set_value(true);
  chassis.wait_drive();
  chassis.set_turn_pid(-80, TURN_SPEED);
  chassis.wait_drive();

  arm.set_value(false);

  chassis.set_turn_pid(120, TURN_SPEED);
  chassis.wait_drive();

  intake = -127;
  pros::delay(500);

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-6, 127);
  chassis.wait_drive();

  chassis.set_turn_pid(-80, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-6, 127);
  chassis.wait_drive();

  chassis.set_drive_pid(8, 127);
  chassis.wait_drive();

  chassis.set_turn_pid(25, TURN_SPEED);
  chassis.wait_drive();

  intake = 127;
  chassis.set_drive_pid(19, 127);
  chassis.wait_drive();

  chassis.set_turn_pid(145, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(5, 127);
  intake = -127;
  chassis.wait_drive();

  pros::delay(400);
  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();
  intake = 127;

  chassis.set_drive_pid(10, 127);
  chassis.wait_drive();

  chassis.set_turn_pid(180, TURN_SPEED);
  chassis.wait_drive();

  wings.set_value(true);
  intake = -127;

  chassis.ez_auto.remove();

  chassis.set_tank(127, 127);
  pros::delay(800);
  chassis.set_tank(-127, -127);

}
void skills() {
  hang = -127;
  pros::delay(50);
  hang = 0;

  chassis.set_drive_pid(-14, 127);
  chassis.wait_drive();

  chassis.set_drive_pid(14, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-180, TURN_SPEED);
  chassis.wait_drive();
  arm.set_value(true);
  pros::delay(15000);
  arm.set_value(false);

  chassis.set_turn_pid(-235, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-33, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(33, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-170, TURN_SPEED);
  chassis.wait_drive();

  arm.set_value(true);
  pros::delay(10000);
  arm.set_value(false);

  chassis.set_turn_pid(-235, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-40, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-275, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-16, 127);
  chassis.wait_drive();

  chassis.set_turn_pid(-330, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-8, 127);
  chassis.wait_drive();

  chassis.set_drive_pid(4, 127);
  chassis.wait_drive();

  chassis.ez_auto.remove();
  chassis.set_tank(-127, -127);
  pros::delay(400);
  chassis.set_tank(127, 127);
  pros::delay(400);
  chassis.set_tank(-127, -127);
  pros::delay(400);
  chassis.set_tank(127, 127);
  pros::delay(300);
  chassis.set_tank(0, 0);
  pros::delay(100);

  chassis.set_tank(127, -127);
  pros::delay(300);
  chassis.set_tank(0, 0);
}
void back() {
  chassis.set_tank(-127, -127);
  pros::delay(5000);
  chassis.set_tank(100, 100);
  pros::delay(2000);
  chassis.set_tank(0, 0);
}

// used for no auton if necessary
//    (its a failsafe)
void blank() {}