#include "autons.hpp"
#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "pros/rtos.hpp"

const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;

pros::Motor intake(-20);
pros::Motor cata(-10);
pros::ADIDigitalOut bitchslap('a');
pros::ADIDigitalOut wings('h');

//
// constants
//
void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void one_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void two_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void exit_condition_defaults() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

void modified_exit_condition() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

//
// Autons
//
void left_side_winpoint() {
  intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  wings.set_value(false);
  bitchslap.set_value(false);

  chassis.set_drive_pid(6, DRIVE_SPEED);
  chassis.wait_until(3);
  bitchslap.set_value(true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();
  bitchslap.set_value(false);

  chassis.set_turn_pid(25, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(6, DRIVE_SPEED);
  chassis.wait_until(3);
  intake = -127;
  chassis.wait_drive();
  intake = 0;

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-3, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(225, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-4.5, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(2, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-55, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-16, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-30, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-4, DRIVE_SPEED);
  chassis.wait_drive();

  bitchslap.set_value(true);

  chassis.set_turn_pid(-70, 50);
  chassis.wait_drive();
}

void right_side_winpoint() {
  wings.set_value(false);
  bitchslap.set_value(false);
  intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  
  chassis.set_drive_pid(10, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(4, DRIVE_SPEED);
  chassis.wait_until(2);
  intake = -127;
  chassis.wait_drive();
  intake = 0;

  chassis.set_drive_pid(-4, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(135, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-5, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(1, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-16, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(8, DRIVE_SPEED);
  chassis.wait_until(4);
  intake = 50;
  chassis.wait_drive();
  intake = 0;

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(10, DRIVE_SPEED);
  chassis.wait_until(8);
  intake = -127;
  chassis.wait_drive();
  intake = 0;

  chassis.set_drive_pid(-8, DRIVE_SPEED);
  chassis.wait_drive();
  
  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-4, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  bitchslap.set_value(true);

  chassis.set_drive_pid(-8, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-65, TURN_SPEED);
  chassis.wait_drive();
}

void skills() {
  intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  int time = pros::millis();
  while (pros::millis() < time + 20000) {
    intake = -127;
  }
  intake = 0;

  chassis.set_turn_pid(185, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-4, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(180, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-36, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(36, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-4, DRIVE_SPEED);
  chassis.wait_drive();

  time = pros::millis();
  while (pros::millis() < time + 20000) {
    intake = -127;
  }
  intake = 0;

  chassis.set_turn_pid(185, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-4, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(180, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-36, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(135, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-6, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-6, 127);
  chassis.wait_drive();

  chassis.set_drive_pid(4, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-6, 127);
  chassis.wait_drive();

  chassis.set_drive_pid(4, DRIVE_SPEED);
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