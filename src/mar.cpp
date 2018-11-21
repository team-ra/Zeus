////////////////////////////////////////////////////////////////////////
//! @file: mar.c
//! @brief Match Autonomous RED functions
//
// This is the collection of intermediate functions that call
// the actual auton function with the paramter RED. The actual
// auton function is written to work on the RED or BLUE side
// but the function point cannot pass that information so it
// is extracted from the mabl#/mabr# function. This indirection
// also allows for the adjustment of RED right and BLUE left being
// mirrors or RED right and BLUE right being mirrors.
//
//! @author
//
//! @copyright Copyright 2018 VEX Team 5090Z Radioactive
//
//! @license GPL-3.0
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You can get a copy of the GNU General Public License at:
//  <http://www.gnu.org/licenses/>.
//
////////////////////////////////////////////////////////////////////////

#include "robot_gui.h"
#include "robot.h"
void marl1() {
 info_printf(1,"in marl1");
auton1();
}

void marl2() {
 info_printf(1,"in marl2");

}

void marl3() {
 info_printf(1,"in marl3");
}

void marl4() {
 info_printf(1,"in marl4");
}

void marl5() {
 info_printf(1,"in marl5");
}

void marl6() {
 info_printf(1,"in marl6");
}

void marr1() {
 info_printf(1,"in marr1");
auton2();
 // example usage
 // match_auton1(RED); // mirror of BLUE left
}

void marr2() {
 info_printf(1,"in marr2");
 auton6();
}

void marr3() {
 info_printf(1,"in marr3");
}

void marr4() {
 info_printf(1,"in marr4");
}

void marr5() {
 info_printf(1,"in marr5");
}

void marr6() {
 info_printf(1,"in marr6");
}
