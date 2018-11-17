////////////////////////////////////////////////////////////////////////
//! @file: mab.c
//! @brief Match Autonomous Blue functions
//
// This is the collection of intermediate functions that call
// the actual auton function with the paramter BLUE. The actual
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
void mabl1() {
 info_printf(1,"in mabl1");
 // example usage
 // match_auton1(BLUE); // mirror of RED right
 auton2();
}

void mabl2() {
 info_printf(1,"in mabl2");
 auton2();
}

void mabl3() {
 info_printf(1,"in mabl3");
}

void mabl4() {
 info_printf(1,"in mabl4");
}

void mabl5() {
 info_printf(1,"in mabl5");
}

void mabl6() {
 info_printf(1,"in mabl6");
}

void mabr1() {
 info_printf(1,"in mabr1");
 auton1();
}

void mabr2() {
 info_printf(1,"in mabr2");
}

void mabr3() {
 info_printf(1,"in mabr3");
}

void mabr4() {
 info_printf(1,"in mabr4");
}

void mabr5() {
 info_printf(1,"in mabr5");
}

void mabr6() {
 info_printf(1,"in mabr6");
}
