#include "main.h"
#include "EZ-Template/auton.hpp"
#include "autons.hpp"
#include "pros/adi.hpp"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "pros/rotation.hpp"
#include "pros/rtos.hpp"
#include "pros/screen.hpp"
#include <iostream>
#include <string>

int stage = 0;

Drive chassis (
  {-1,-2,-3}
  ,{4,5,6}
  ,13
  ,4.125
  ,200

  // External Gear Ratio (MUST BE DECIMAL)
  //    (or gear ratio of tracking wheel)
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 2.333.
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 0.6.
  ,64/(float)36
);

void initialize() {
  pros::delay(500); // Stop the user from doing anything while legacy ports configure.

  chassis.toggle_modify_curve_with_controller(false); // Enables modifying the controller curve with buttons on the joysticks
  chassis.set_active_brake(0.1); // recommended 0.1.
  chassis.set_curve_default(0, 0); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)  
  default_constants(); // Set the drive to your own constants from autons.cpp!
  exit_condition_defaults(); // Set the exit conditions to your own constants from autons.cpp!

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.add_autons({
    Auton("No Auton", blank),
    Auton("Left Side Win Point", left_side_winpoint),
    Auton("Right Side Win Point", right_side_winpoint),
    Auton("Skills Auton", skills),
  });

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();

}

void disabled() {

}

void competition_initialize() {
  
}

void autonomous() {
  chassis.reset_pid_targets();
  chassis.reset_gyro();
  chassis.reset_drive_sensor();
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD); // helps autonomous consistency.

  ez::as::auton_selector.call_selected_auton();
}

void opcontrol() {
  pros::Controller controller(pros::E_CONTROLLER_MASTER);

  pros::lcd::clear();
  pros::lcd::print(0, "  ___  _  _ ___ __   __");
  pros::lcd::print(1, " |__ \\| || |__ \\\\ \\ / /");
  pros::lcd::print(2, "    ) | || |_ ) |\\ V / ");
  pros::lcd::print(3, "   / /|__   _/ /  > <  ");
  pros::lcd::print(4, "  / /_   | |/ /_ / . \\ ");
  pros::lcd::print(5, " |____|  |_|____/_/ \\_\\");
  pros::Motor cata(-10);
  pros::Motor intake(-20);
  intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  pros::Rotation rot(11);
  pros::ADIDigitalOut wings('h');
  pros::ADIDigitalOut atwp('a');
  wings.set_value(false);
  atwp.set_value(false);
  rot.reset_position();


  float speed = 0.7;
  const int maxspeed = 12000;
  
  const int finalposition = 36800;
  const int midposition = 33500;
  const int autonposition = 19500;

  const float kp = 0.7;
  const float ki = 0.03;
  float error = 0;
  float intergral = 0;

  bool wingstate = false;
  bool awpstate = false;

  chassis.set_drive_brake(MOTOR_BRAKE_COAST);

  while (true) {
    controller.set_text(0, 0, "                        ");
    controller.set_text(0, 0, "Speed(%) : " + std::to_string((int) (speed*100)));
    //chassis.tank(); // Tank control
    chassis.arcade_standard(ez::SPLIT); // Standard split arcade
    // chassis.arcade_standard(ez::SINGLE); // Standard single arcade
    // chassis.arcade_flipped(ez::SPLIT); // Flipped split arcade
    // chassis.arcade_flipped(ez::SINGLE); // Flipped single arcade

    // user code here
    if (stage == 0) { // cata is loadable
      if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) { // fire
        rot.reset_position();
        stage = 1;
        error = 0;
        intergral = 0;
      } else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) { // reload to intake blocker
        rot.reset_position();
        stage = 2;
        error = 0;
        intergral = 0;
      }
    } else if (stage == 4) {
      if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) { // bring back to load angle
        stage = 1;
        intergral = 0;
      }
    }
    
    if (stage == 1) { // bring to fire angle
      if (rot.get_position() < finalposition) {
        error = abs(rot.get_position() - finalposition);
        float proportional = error;
        if (finalposition-rot.get_position() <= 0.5*(finalposition)){
          intergral += error;
        }
        cata.move_voltage(proportional*kp + intergral*ki);
      } else {
        cata.move_voltage(0);
        stage = 0;
      }
    } else if (stage == 2) { // bring to blocker angle
      if (rot.get_position() < midposition) {
        error = abs(rot.get_position() - midposition);
        float proportional = error;
        if (midposition-rot.get_position() <= 0.5*(midposition)){
          intergral += error;
        }
        cata.move_voltage(proportional*kp + intergral*ki);
      } else {
        cata.move_voltage(0);
        stage = 4;
      }
    } else if (stage == 5) {
      if (rot.get_position() < midposition) {
      error = abs(rot.get_position() - midposition);
      float proportional = error;
      if (midposition-rot.get_position() <= 0.5*(midposition)){
        intergral += error;
      }
      cata.move_voltage(proportional*kp + intergral*ki);
    } else {
      cata.move_voltage(0);
      stage = 0;
    }
    }

    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
    {
      cata.move_voltage(12000*speed);
    } else {
      if (stage != 1 and stage != 2 and stage != 5) {
        cata.move_voltage(0);
      }
    }

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
      speed += 0.01;
    }
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
      speed -= 0.01;
    }

    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) and (stage == 0 or stage == 4)) {
      intake = 95;
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
      intake = -95;
    } else {
      intake = 0;
    }

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
      wingstate = !wingstate;
      wings.set_value(wingstate);
    }

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
      awpstate = !awpstate;
      atwp.set_value(awpstate);
    }

    // dont touch
    pros::delay(ez::util::DELAY_TIME);
  }
}
