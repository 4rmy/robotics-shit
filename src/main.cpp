#include "main.h"
#include "EZ-Template/auton.hpp"
#include "EZ-Template/sdcard.hpp"
#include "EZ-Template/util.hpp"
#include "autons.hpp"
#include "pros/adi.hpp"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "pros/rtos.hpp"
#include <string>

Drive chassis (
  {-11,-12,-13}
  ,{1,2,3}
  ,21
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
    Auton("Aggressive Left Elim", aggressive_left_elim),
    Auton("Aggressive Right Elim", aggressive_right_elim),
    Auton("Skills Auton", skills),
  });

  // Initialize chassis and auton selector
  chassis.initialize();

  pros::Controller controller(pros::E_CONTROLLER_MASTER);
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

  pros::Motor kicker(-10);
  pros::Motor intake(-19);
  intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  kicker.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

  bool wingstate = false;
  bool rampstate = false;
  bool fourbarstate = false;
  bool bitchslapstate = false;
  pros::ADIDigitalOut wings('a');
  pros::ADIDigitalOut ramp('b');
  pros::ADIDigitalOut fourbar('H');
  pros::ADIDigitalOut bitchslap('G');
  wings.set_value(wingstate);
  ramp.set_value(rampstate);
  fourbar.set_value(fourbarstate);
  bitchslap.set_value(bitchslapstate);

  chassis.set_drive_brake(MOTOR_BRAKE_COAST);

  pros::lcd::clear();
  pros::lcd::print(0, "  ___  _  _ ___ __   __");
  pros::lcd::print(1, " |__ \\| || |__ \\\\ \\ / /");
  pros::lcd::print(2, "    ) | || |_ ) |\\ V / ");
  pros::lcd::print(3, "   / /|__   _/ /  > <  ");
  pros::lcd::print(4, "  / /_   | |/ /_ / . \\ ");
  pros::lcd::print(5, " |____|  |_|____/_/ \\_\\");

  while (true) {
    //chassis.tank(); // Tank control
    chassis.arcade_standard(ez::SPLIT); // Standard split arcade
    chassis.set_joystick_threshold(20);
    // chassis.arcade_standard(ez::SINGLE); // Standard single arcade
    // chassis.arcade_flipped(ez::SPLIT); // Flipped split arcade
    // chassis.arcade_flipped(ez::SINGLE); // Flipped single arcade

    // kicker control
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
      kicker = 127;
    } else {
      kicker = 0;
    }

    // intake control
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
      intake = 95;
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
      intake = -95;
    } else {
      intake = 0;
    }

    // extend wings
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
      wingstate = !wingstate;
      wings.set_value(wingstate);
    }

    // raise four-bar
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
      if (!(fourbarstate && rampstate)) {
        fourbarstate = !fourbarstate;
        fourbar.set_value(fourbarstate);
      }
    }
    
    /* control bitslap for hang
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
      bitchslapstate = !bitchslapstate;
      bitchslap.set_value(bitchslapstate);
    }*/

    // toggle instake ramp
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
      rampstate = !rampstate;
      ramp.set_value(rampstate);
    }

    // dont touch
    pros::delay(ez::util::DELAY_TIME);
  }
}
