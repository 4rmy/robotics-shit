#pragma once

#include "EZ-Template/drive/drive.hpp"

extern Drive chassis;
// autons
void close_qual();
void far_qual();
void close_elim();
void far_elim();
void skills();
void back();
void blank();

// contants
void default_constants();
void one_mogo_constants();
void two_mogo_constants();
void exit_condition_defaults();
void modified_exit_condition();