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






void
auto_test() // now is tester auton
{
    flock(false) ;
    set_drive_brake (MOTOR_BRAKE_COAST) ;
    set_drive_pid(drive, -30, DRIVE_SPEED) ; // half-platform is 26.5
    int pitch = get_gyroPitch () ;
    timer = 0 ;
    pros::delay(100) ;
    flock(true) ;
    while (!limit_switch() || timer == 250) {
      timer++;
      pros::delay(10);}
    pros::delay(200) ;
    set_drive_pid(turn, 150, DRIVE_SPEED) ;
    wait_drive() ;
    mogo_out() ;
    set_drive_pid(drive, 36, DRIVE_SPEED) ;
    wait_drive() ;
    mogo_in() ;
    pros::delay(150) ;
    set_drive_pid(turn, -150, DRIVE_SPEED) ;
    wait_drive() ;
    set_drive_pid(drive, 72, DRIVE_SPEED) ;
    wait_drive() ;
    // drop mogo and prepare platform
    set_drive_pid(drive, -20, DRIVE_SPEED) ;
    wait_drive() ;
    set_drive_pid(turn, -180, DRIVE_SPEED) ;
    wait_drive() ;
    set_drive_pid(drive, 20, DRIVE_SPEED) ;
    wait_drive() ;
    mogo_out() ;
    set_drive_pid(drive, -60, DRIVE_SPEED) ;
    wait_drive() ;

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
