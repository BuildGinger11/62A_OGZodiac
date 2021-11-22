#include "main.h"

const int DRIVE_SPEED = 110; //  This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             //  If this is 127 and the robot tries ot heading correct, it's only correcting by
                             //  making one side slower.  When this is 87%, it's correcting by making one side
                             //  faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;

// /
//  Constants
// /

//  Reset all constants to default (what's in setup.hpp is default)
void
reset_constants() {
  reset_slew_min_power();
  reset_slew_distance();
  reset_fw_drive_constants();
  reset_bw_drive_constants();
  reset_turn_constants();
  reset_turn_i_constants();
  reset_swing_constants();
}

//  Functions to change constants
//  (if the robot has different weight to it, sometimes we need to change constants)
/*
void
one_mogo_constants() {
  set_slew_min_power(80, 80);
  set_slew_distance(7, 7);
  set_fw_drive_constants(0.45, 5);
  set_bw_drive_constants(0.375, 4);
  set_turn_constants(5, 0.003, 35);
  set_turn_i_constants(15, 30);
  set_swing_constants(12, 35);
}

void
two_mogo_constants() {
  set_slew_min_power(80, 80);
  set_slew_distance(7, 7);
  set_fw_drive_constants(0.45, 5);
  set_bw_drive_constants(0.375, 4);
  set_turn_constants(5, 0.003, 35);
  set_turn_i_constants(15, 30);
  set_swing_constants(12, 35);
}
*/



//  All drive movements use the "set_drive_pid" function
//  the first parameter is the type of motion (drive, turn, r_swing, l_swing)
//  below are example codes using each type


//
// /
//  TESTER AUTON
// /
//
int timer = 0;


void autonSkillzP1 () //get ally
{
  tareLift() ;
  sixlock(false) ;
  set_lift_position(0, 100) ;
  pros::delay(500) ;
  //drive into mogo
  set_drive_pid(drive, -7, DRIVE_SPEED/2) ;
  wait_drive() ;
  pros::delay(200) ;
  sixlock(true) ;
  pros::delay(300) ;
  set_drive_pid(drive, 3, DRIVE_SPEED) ;
  //lift up
  set_lift_position(575, 100) ;
  pros::delay(750) ;
  wait_drive() ;
  //turn
  set_drive_pid(turn, 90, DRIVE_SPEED/1.5) ;
  wait_drive() ;
}

void autonSkillzP2 () // get neutral
{
  //rush neutral
  mogo_out() ;
  set_drive_pid(drive, 50, DRIVE_SPEED/1.5) ;
  pros::delay(250) ;
  set_lift_position(100, DRIVE_SPEED) ;
  wait_drive() ;
  //grab neutral
  mogo_in() ;
}

void autonSkillzP3 () // score neutral and ally
{
//move to position
  set_drive_pid(turn, -46, DRIVE_SPEED) ;
  wait_drive() ;
  //drive in front of platform
  set_drive_pid(drive, -46, DRIVE_SPEED) ; // was -44
  wait_drive() ;
//place ally mogo
  set_lift_position(625, 100) ;
  pros::delay(400) ;
  set_drive_pid(turn, -112.5, DRIVE_SPEED/1.5) ; // was -112
  wait_drive() ;
  //reverse into platform
  set_drive_pid(drive, -18, DRIVE_SPEED) ;
  wait_drive() ;
  //drop lift
  set_lift_position(321, 100) ;
  pros::delay(500) ;
  //set_drive_pid(turn, -105, DRIVE_SPEED) ;
  wait_drive() ;
  sixlock(false) ;
  pros::delay(500) ;
  set_drive_pid(drive, 10, DRIVE_SPEED) ;
  pros::delay (200) ;
  set_lift_position(500, 100) ;
  wait_drive() ;

//platform neutral
  set_drive_pid(turn, -180, DRIVE_SPEED) ;
  //drop
  mogo_out() ;
  set_drive_pid(drive, 15, DRIVE_SPEED/1.5) ;
  wait_drive() ;
  set_drive_pid(drive, -10, DRIVE_SPEED) ;
  wait_drive() ;
  mogo_in() ;
  pros::delay(250) ;
  //face neutral
  set_drive_pid(turn, 0, DRIVE_SPEED) ;
  pros::delay(150) ;
  set_lift_position(0, 100) ;
  wait_drive() ;
  //grab
  sixlock(false) ;
  set_drive_pid(drive, -30, DRIVE_SPEED/1.5) ;
  wait_drive() ;
  pros::delay(200) ;
  sixlock(true) ;
  pros::delay(300) ;
  //actual platformy stuff

  set_drive_pid(drive, 23, DRIVE_SPEED) ;

  set_lift_position(575, 100) ;
  wait_drive() ;
  //face to platform
  set_drive_pid(turn, -85, DRIVE_SPEED/1.75) ;
  wait_drive() ;
  set_drive_pid(drive, -17, DRIVE_SPEED/1.5) ;
  wait_drive() ;
  set_lift_position(321, 100) ;
  //place
  pros::delay(750) ;
  sixlock(false) ;
  pros::delay(250) ;
  //escape
  set_drive_pid(drive, 15, DRIVE_SPEED) ;
  pros::delay(200) ;
  set_lift_position(500, 100) ;
  wait_drive() ;


}

void autonSkillzP4 () // score tall neut
{
  // get position for tall neut
  set_drive_pid(turn, 0, DRIVE_SPEED) ;
  wait_drive() ;
  set_drive_pid(drive, 8, DRIVE_SPEED) ;
  wait_drive() ;
//platform tall neutral
  //face tall neutral
  set_lift_position(0, 100) ;
  set_drive_pid(turn, 95, DRIVE_SPEED) ;
  wait_drive() ;
  //drive tall neut
  set_drive_pid(drive, -25, DRIVE_SPEED/1.5) ;
  sixlock(false) ;
  wait_drive() ;
  //grab
  pros::delay(500) ;
  sixlock(true) ;
  pros::delay(750) ;
  //face drive to platform
  set_drive_pid(turn, 268, DRIVE_SPEED/1.75) ;
  wait_drive() ;

  // ben method
  //lift up
  set_lift_position(700, 100) ;
  pros::delay(2000);
  //drive into
  set_drive_pid(drive, -47, DRIVE_SPEED/1.5) ;
  pros::delay (800) ;
  set_lift_position(230, 30) ;
  wait_drive() ;

  // // dru method
  // //lift up
  // set_lift_position(525, 100) ;
  // //drive into
  // set_drive_pid(drive, -47, DRIVE_SPEED/2) ;
  // pros::delay(1750);
  // set_lift_position(230, 100) ;
  // wait_drive() ;

  //place
  pros::delay(500) ;
  sixlock(false) ;
  pros::delay(500) ;
  //escape
  set_drive_pid(drive, 6, DRIVE_SPEED) ;
  pros::delay(150) ;
  set_lift_position(500, DRIVE_SPEED) ;
  wait_drive() ;
}

void autonSkillzP5 () // get opposite ally1 and last neut
{
  //face ally1
  set_drive_pid(turn, 176, DRIVE_SPEED) ;
  wait_drive() ;
  set_lift_position(0, 100) ;
  set_drive_pid(drive, -59, DRIVE_SPEED) ;
  wait_drive() ;
  //get ally1
  sixlock(true) ;
  pros::delay(250) ;
  set_lift_position(100, 100) ;
  //face other neut
  set_drive_pid(turn, 202, DRIVE_SPEED/1.25) ;
  wait_drive() ;
  //get last neut
  mogo_out() ;
  set_drive_pid(drive, 98, DRIVE_SPEED/1.5) ;
  wait_drive() ;
  mogo_in() ;
  pros::delay(500) ;
  //face platform
  set_drive_pid(turn, 90, DRIVE_SPEED) ;
  wait_drive() ;
  //drive platform
  set_drive_pid(drive, -55, DRIVE_SPEED) ;
  //raise lift
  set_lift_position(575, 100) ;
  wait_drive() ;
}

void autonSkillzP6 () //platforming process
{
  //face platform
  set_drive_pid(turn, 179, DRIVE_SPEED) ;
  wait_drive() ;
  //lower platfomr
  set_lift_position(0, 100) ;
  pros::delay(1500) ;
//platforming Drive
  set_drive_pid(drive, -20, DRIVE_SPEED);
  wait_drive();
  while (get_gyroPitch() >= 10)
  {
    if (get_gyroPitch() > 20)
      set_tank(-127, -127);
    else
      set_tank(-100, -100);
  }
  set_tank(0, 0);

}


void
auto_test() // now is tester auton
{
    autonSkillzP1 () ;
    autonSkillzP2 () ;
    autonSkillzP3 () ;
    autonSkillzP4 () ;
    autonSkillzP5() ;
    autonSkillzP6 () ;

}

//
//
// FOR LEFT SIDE (odds)
//
//

void
auto_winPointRight() { // ring row and AWP

  // rush
    set_drive_brake(MOTOR_BRAKE_COAST);
    set_drive_pid(drive, 43, DRIVE_SPEED/1.25) ; // was 38
    // lower FMogo
    Auton_mogo_out () ;
    wait_drive() ;
    set_drive_brake(MOTOR_BRAKE_BRAKE);
  // retreat
    mogo_in () ; // test
    // set_mogo_position (-780, 127) ;
    set_drive_pid(drive, -24, DRIVE_SPEED) ;
  // back lift up
    set_lift_position(446, 100);
    wait_drive() ;
  // set fmogo motor to 0
    // set_mogo(0) ;
  // prepare claw
    claw(false) ;
  // turn to reverse face mogo
    set_drive_pid(turn, -95, DRIVE_SPEED) ; // change to angle from AUTON 2
    wait_drive() ;
  // drive into mogo
    set_drive_pid(drive, -25, DRIVE_SPEED) ;
    while (!limit_switch() || timer == 130) {
      timer++;
      pros::delay(10);
    }

    pros::delay (500) ;
  // claw grab
    claw(true) ;
    pros::delay (300) ;

  // drop rings
    intake (115) ;
  // back up
    set_drive_pid (drive, 12, DRIVE_SPEED) ;
    wait_drive() ;
  // turn
    set_drive_pid(turn, 9, DRIVE_SPEED) ;
    wait_drive() ;
  // drive and collect row
    set_drive_pid(drive, 27, DRIVE_SPEED/5) ;
    wait_drive() ;
  // retreat
    set_drive_pid(drive, -45, DRIVE_SPEED) ;
    wait_drive () ;



    intake (0) ;

}


//
//
// FOR RIGHT SIDE
//
//

void
auto_AWPcarry() {
  //set_drive_brake(MOTOR_BRAKE_BRAKE);
  // blursed ring score technique
  flock (false) ;
  pros::delay(500) ;
  flock (true) ;
  set_drive_pid(drive, -8, DRIVE_SPEED) ;
  wait_drive() ;
  set_drive_pid(l_swing, -35, DRIVE_SPEED) ;
  wait_drive() ;
  set_drive_pid(drive, 40, DRIVE_SPEED) ;
  wait_drive() ;
  //rush
  set_drive_pid(turn, -180, DRIVE_SPEED) ;
  wait_drive() ;
  set_drive_pid(drive, -90, DRIVE_SPEED) ;
  //raise lift
  set_lift_position(446, 100);
  claw (false) ;
  int timer = 0 ;
  while (!limit_switch() && timer < 400) {
    timer++;
    pros::delay(10);
  }
  claw (true) ;
  pros::delay(250) ;
  intake (100) ;
  pros::delay(1000) ;
  set_drive_pid(drive, 20, DRIVE_SPEED) ;
  wait_drive() ;

}



void
auto_allianceRight() {
  // rush
    set_drive_brake(MOTOR_BRAKE_COAST);
    set_drive_pid(drive, 43, DRIVE_SPEED/1.25) ; // was 38
    // lower FMogo
    Auton_mogo_out () ;
    wait_drive() ;
    set_drive_brake(MOTOR_BRAKE_BRAKE);
  // rush middle
    mogo_in () ;
    set_drive_pid(turn, 90, DRIVE_SPEED) ;
    //ready b6bar
    sixlock(false) ;
    wait_drive() ;
    //move to mid
    set_drive_pid(drive, -24, DRIVE_SPEED/1.25) ;
    //grab
    sixlock(true) ;
    //turn for home
    set_drive_pid(turn, 135, DRIVE_SPEED) ;
    //retreat
    set_drive_pid(drive, 40, DRIVE_SPEED) ;


}



// /
//  Swing Example
// /
void
auto_5() {
  //  The second parameter is target degrees
  //  The third parameter is speed of the moving side of the drive

  set_drive_pid(l_swing, 45, SWING_SPEED);
  wait_drive();

  set_drive_pid(drive, 24, DRIVE_SPEED, true);
  wait_until(12);

  set_drive_pid(r_swing, 0, SWING_SPEED);
  wait_drive();
}



// /
//  Auto that tests everything
// /
void
test_auton() {
  set_drive_pid(drive, 24, DRIVE_SPEED, true);
  wait_drive();

  set_drive_pid(turn, 45, TURN_SPEED);
  wait_drive();

  set_drive_pid(r_swing, -45, TURN_SPEED);
  wait_drive();

  set_drive_pid(turn, 0, TURN_SPEED);
  wait_drive();

  set_drive_pid(drive, -24, DRIVE_SPEED, true);
  wait_drive();
}



void
auto_6()
  {
  // mogo_outB(true);
  // block(true);
  set_drive_pid(drive, 10, DRIVE_SPEED);
  wait_drive();
  // block(false);
  pros::delay(100);
  // mogo_inB(true);
  pros::delay(400);
  intake(127);

  }



void
auto_7() {

}



void
auto_8() {

}



void
auto_skillz() {
  // lower FMogo
    mogo_out () ;
  // rush
    set_drive_brake(MOTOR_BRAKE_COAST);
    set_drive_pid(drive, 41, DRIVE_SPEED/1.25) ; // was 38
    wait_drive() ;
    set_drive_brake(MOTOR_BRAKE_BRAKE);
  // retreat
    mogo_in () ;
    set_drive_pid(drive, -21, DRIVE_SPEED) ;
  // back lift up
    set_lift_position(446, 100);
    wait_drive() ;
  // prepare claw
    claw(false) ;
  // turn to reverse face mogo
    set_drive_pid(turn, -95, DRIVE_SPEED) ; // change to angle from AUTON 2

  //drop neut mogo
    mogo_out() ;

    wait_drive() ;
  // drive into mogo
    set_drive_pid(drive, -30, DRIVE_SPEED) ;
    while (!limit_switch() || timer == 500) {
      timer++;
      pros::delay(10);}

  // claw grab
    pros::delay(150) ;
    claw(true) ;
    pros::delay (500) ;

  // drop rings
    intake (115) ;
  // back up
    set_drive_pid (drive, 12, DRIVE_SPEED) ;
    wait_drive() ;
  // turn
    set_drive_pid(turn, 0, DRIVE_SPEED) ;
    wait_drive() ;
  //rush mid
    set_drive_pid(drive, 38, DRIVE_SPEED/3) ;
    wait_drive() ;
  //face mid goal
    set_drive_pid(turn, -90, DRIVE_SPEED) ;
    wait_drive() ;
  //drive forward & grab rings
    set_drive_pid(drive, 46, DRIVE_SPEED/3) ;
    mogo_out() ;
    wait_drive() ;
  //pick up mid
    mogo_in () ;
  //drop ally mogo and swap to b6bar
    intake(0) ;
    claw(false) ;
    set_drive_pid(drive, 15, DRIVE_SPEED) ;
    wait_drive() ;
    set_lift_position(0, 100) ;
    sixlock(false) ;
    pros::delay(500) ;
  //pick up goal
    set_drive_pid(drive, -15, DRIVE_SPEED) ;
    wait_drive() ;
    sixlock(true) ;
  //platform

    set_drive_pid(turn, -210, DRIVE_SPEED) ;
    wait_drive() ;
    set_drive_pid(drive, -15, DRIVE_SPEED) ;

    set_lift_position(575, 100) ;

    wait_drive() ;
    set_drive_pid(turn, -180, DRIVE_SPEED) ;
    wait_drive() ;
    set_drive_pid(drive, -25, DRIVE_SPEED) ;
    wait_drive() ;
  //lower and place goal
    set_lift_position(321, 100) ;
    pros::delay(150) ;
    sixlock(false) ;
    pros::delay(100) ;
    set_drive_pid(drive, 10, DRIVE_SPEED) ;
    wait_drive () ;
    //face mogo
    set_drive_pid(turn, -270, DRIVE_SPEED) ;
    mogo_out() ;
    set_lift_position(575, 100) ;
    wait_drive() ;
    claw(false) ;
    set_drive_pid(drive, -54, DRIVE_SPEED) ;
    while (!limit_switch() || timer == 1000) {
      timer++;
      pros::delay(10);}

  // claw grab
    claw(true) ;
    pros::delay (500) ;

    // rush home
    set_drive_pid(turn, 165, DRIVE_SPEED) ;
    mogo_out() ;
    intake(115) ;
    wait_drive() ;
    set_drive_pid(drive, 32, DRIVE_SPEED) ;
    wait_drive() ;
    mogo_in() ;
    set_drive_pid(drive, 32, DRIVE_SPEED) ;

    set_drive_pid(drive, 0, 0) ;
    intake(0) ;
}



void
auto_basic() { //can't go wrong
  // lift 6bar
    claw (true) ;
    set_lift_position(446, 100);
    pros::delay(750) ;
  // drive forward
    set_drive_pid(drive, -10, DRIVE_SPEED);
    wait_drive();
    // block(false);
    pros::delay(100);
    // mogo_inB(true);
    pros::delay(400);
    claw (false);
  // run intake
    intake(127);
    pros::delay (3000) ;
    intake (0) ;
}
