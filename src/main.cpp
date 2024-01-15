#include "main.h"
#include "EZ-Template/auton.hpp"
#include "EZ-Template/sdcard.hpp"
#include "EZ-Template/util.hpp"
#include "autons.hpp"
#include "pros/adi.hpp"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "pros/rtos.hpp"
#include <string>

// chassis
// used for auton, and drive control
Drive chassis(
    {-1, -2, -3},
    {11, 12, 13},
    21,
    4.125,
    200,

    // External Gear Ratio (MUST BE DECIMAL)
    //    (or gear ratio of tracking wheel)
    // eg. if your drive is 84:36 where the 36t is powered, your RATIO
    // would be 2.333. eg. if your drive is 36:60 where the 60t is
    // powered, your RATIO would be 0.6.
    64 / (float)36
);

// set things up before the match
void initialize() {
    pros::delay(500); // Stop the user from doing anything while legacy ports configure.

    chassis.toggle_modify_curve_with_controller(false);  // Enables modifying the controller curve with buttons on the
    // joysticks

    chassis.set_active_brake(0.1); // recommended 0.1.
    chassis.set_curve_default(0, 0); // Defaults for curve. If using tank, only the first parameter is
    // used. (Comment this line out if you have an SD card!)
    default_constants(); // Set the drive to your own constants from autons.cpp!
    exit_condition_defaults(); // Set the exit conditions to your own constants
    // from autons.cpp!

    // Autonomous Selector using LLEMU
    ez::as::auton_selector.add_autons({
        Auton("Back", back),
        Auton("Skills Auton", skills),
        Auton("No Auton", blank),
    });

    // Initialize chassis and auton selector
    chassis.initialize();

    // used in auton selector
    pros::Controller controller(pros::E_CONTROLLER_MASTER);
    ez::as::initialize();
}

// not used
void disabled() {}

// no special initialization
void competition_initialize() {}

// used to
//  select autons
//  init hardware for autons
void autonomous() {
    chassis.reset_pid_targets();
    chassis.reset_gyro();
    chassis.reset_drive_sensor();
    chassis.set_drive_brake(MOTOR_BRAKE_HOLD); // helps autonomous consistency.

    ez::as::auton_selector.call_selected_auton();
}

// bot for driver control
void opcontrol() {
    // cool art
    pros::lcd::clear();
    pros::lcd::print(0, "  ___  _  _ ___ __   __");
    pros::lcd::print(1, " |__ \\| || |__ \\\\ \\ / /");
    pros::lcd::print(2, "    ) | || |_ ) |\\ V / ");
    pros::lcd::print(3, "   / /|__   _/ /  > <  ");
    pros::lcd::print(4, "  / /_   | |/ /_ / . \\ ");
    pros::lcd::print(5, " |____|  |_|____/_/ \\_\\");

    // controller
    pros::Controller controller(pros::E_CONTROLLER_MASTER);
    // kicker
    pros::Motor kicker(14);
    // intake
    pros::Motor intake(15);

    // pto
    pros::ADIDigitalOut pto('a');
    bool pto_toggled = false;
    pto.set_value(pto_toggled);

    // wings
    pros::ADIDigitalOut wings('b');
    bool wings_toggled = false;
    wings.set_value(wings_toggled);

    while (true) {
        //
        //    DRIVE CONTROL
        //      "Left Joystick" for forward and reverse
        //      "Right Joystick" for left and right
        //
        // chassis.tank(); // Tank control
        chassis.arcade_standard(ez::SPLIT); // Standard split arcade
        chassis.set_joystick_threshold(20);
        // chassis.arcade_standard(ez::SINGLE); // Standard single arcade
        //chassis.arcade_flipped(ez::SPLIT); // Flipped split arcade
        // chassis.arcade_flipped(ez::SINGLE); // Flipped single arcade

        //
        //    KICKER CONTROLLS
        //      "R1" to fire kicker and lower hang
        //      "R2" to raise hang
        //
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            kicker = 127;
        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            kicker = -127;
        } else {
            kicker = 0;
        }

        //
        //    INTAKE CONTROLLS
        //      "L1" to intake
        //      "L2" to out-take
        //
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            intake = 127;
        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            intake = -127;
        } else {
            intake = 0;
        }

        //
        //    PTO CONTROLL
        //      "A" to switch pto from kicker to hang and vice versa
        //
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
            pto_toggled = !pto_toggled;
            pto.set_value(pto_toggled);
        }

        //
        //    WINGS CONTROLL
        //      "Left" to extend or retract wings
        //
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
            wings_toggled = !wings_toggled;
            wings.set_value(wings_toggled);
        }

        // timing to fix loop issues
        // (noteably brain freezing)
        pros::delay(ez::util::DELAY_TIME);
    }
}
