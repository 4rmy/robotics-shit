#include "autons.hpp"
#include "pros/adi.hpp"
#include "pros/motors.hpp"

const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;

pros::Motor intake(-19);
pros::Motor cata(-10);

pros::ADIDigitalOut bitchslap('G');
pros::ADIDigitalOut wings('A');
pros::ADIDigitalOut fourbar('H');
pros::ADIDigitalOut ramp('B');

//
// Autons
//
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

  wings.set_value(true);

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

void skills() {
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);

  bool run = true;
  int start = pros::millis();

  intake = 127;

  pros::delay(500);

  if (run) {
    fourbar.set_value(true);

    pros::delay(250);

    while (pros::millis() < start + 45000) { // 45 secs
      cata = 127;

      pros::delay(10);
    }

    cata = 0;
    fourbar.set_value(false);
  }

  intake = -127;

  chassis.set_turn_pid(-40, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(24, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(30, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(6, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, DRIVE_SPEED);
  chassis.wait_drive();

  wings.set_value(true);
  
  chassis.set_drive_pid(100, 127);
  chassis.wait_until(40);
  chassis.set_drive_pid(0, 0);
  chassis.wait_drive();

  chassis.set_drive_pid(-8, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(12, 127);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(12, 127);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(12, 127);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(12, 127);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, DRIVE_SPEED);
  chassis.wait_drive();
}

void blank() {}

/*
  void drive_and_turn() {
    chassis.set_drive_pid(24, DRIVE_SPEED, true);
    chassis.wait_drive();

    chassis.set_turn_pid(45, TURN_SPEED);
    chassis.wait_drive();

    chassis.set_turn_pid(-45, TURN_SPEED);
    chassis.wait_drive();

    chassis.set_turn_pid(0, TURN_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(-24, DRIVE_SPEED, true);
    chassis.wait_drive();
  }

  void wait_until_change_speed() {
    chassis.set_drive_pid(24, DRIVE_SPEED, true);
    chassis.wait_until(6);
    chassis.set_max_speed(40);
    chassis.wait_drive();

    chassis.set_turn_pid(45, TURN_SPEED);
    chassis.wait_drive();

    chassis.set_turn_pid(-45, TURN_SPEED);
    chassis.wait_drive();

    chassis.set_turn_pid(0, TURN_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(-24, DRIVE_SPEED, true);
    chassis.wait_until(-6);
    chassis.set_max_speed(40);
    chassis.wait_drive();
  }

  void swing_example() {
    chassis.set_swing_pid(ez::LEFT_SWING, 45, SWING_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(24, DRIVE_SPEED, true);
    chassis.wait_until(12);

    chassis.set_swing_pid(ez::RIGHT_SWING, 0, SWING_SPEED);
    chassis.wait_drive();
  }

  void combining_movements() {
    chassis.set_drive_pid(24, DRIVE_SPEED, true);
    chassis.wait_drive();

    chassis.set_turn_pid(45, TURN_SPEED);
    chassis.wait_drive();

    chassis.set_swing_pid(ez::RIGHT_SWING, -45, TURN_SPEED);
    chassis.wait_drive();

    chassis.set_turn_pid(0, TURN_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(-24, DRIVE_SPEED, true);
    chassis.wait_drive();
  }

  void tug (int attempts) {
    for (int i=0; i<attempts-1; i++) {
      // Attempt to drive backwards
      printf("i - %i", i);
      chassis.set_drive_pid(-12, 127);
      chassis.wait_drive();

      // If failsafed...
      if (chassis.interfered) {
        chassis.reset_drive_sensor();
        chassis.set_drive_pid(-2, 20);
        pros::delay(1000);
      }
      // If robot successfully drove back, return
      else {
        return;
      }
    }
  }

  void interfered_example() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  if (chassis.interfered) {
    tug(3);
    return;
  }

  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  }
*/

/*
1 min 30 secs
90s
90000 msec
*/