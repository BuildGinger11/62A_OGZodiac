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
auto_1() // now is tester auton
{

// testing left side

// lower FMogo
  //set_mogo_position(780, 127) ;
  mogo_out () ;
  flock(true) ;
// rush
  set_drive_brake(MOTOR_BRAKE_COAST);
  set_drive_pid(drive, 38, DRIVE_SPEED/1.5) ; // was 40
  wait_drive() ;
  set_drive_brake(MOTOR_BRAKE_BRAKE);
// retreat
  flock(false) ;
  pros::delay (500) ;
  mogo_in () ; // test
  // set_mogo_position (-780, 127) ;
  set_drive_pid(drive, -23, DRIVE_SPEED) ; // was 19
// back lift up
  set_lift_position(446, 100);
  wait_drive() ;
// set fmogo motor to 0
  // set_mogo(0) ;
// prepare claw
  claw(true) ;
// turn to reverse face mogo
  set_drive_pid(turn, -95, DRIVE_SPEED) ; // change to angle from AUTON 2
  wait_drive() ;
// drive into mogo
  set_drive_pid(drive, -25, DRIVE_SPEED) ;
  while (!limit_switch() || timer == 300) {
    timer++;
    pros::delay(10);}

// claw grab
  claw(false) ;
  pros::delay (500) ;

// drop rings
  intake (115) ;
// back up
  set_drive_pid (drive, 10, DRIVE_SPEED) ;
  wait_drive() ;
// turn
  set_drive_pid(turn, 10, DRIVE_SPEED) ;
  wait_drive() ;
// drive and collect row
  set_drive_pid(drive, 35, DRIVE_SPEED/5) ;
  wait_drive() ;
// retreat
  set_drive_pid(drive, -45, DRIVE_SPEED) ;
  wait_drive () ;



  intake (0) ;





// AUTON 2 - can be improved

  //  // lift 6bar
  //    claw (true) ;
  //    set_lift_position(446, 100);
  //    pros::delay(750) ;
  //  // drive forward
  //    set_drive_pid(drive, -20, DRIVE_SPEED);
  //    wait_drive();
  //    // block(false);
  //    claw (false);
  //  // run intake
  //    intake(127);
  //    pros::delay (50) ; // check time
  //    // intake (0) ;
  //
  //    set_drive_pid (drive, 15, DRIVE_SPEED) ;
  //    wait_drive() ;
  //    set_drive_pid(turn, 140, DRIVE_SPEED) ;
  //    wait_drive() ;
  //    // intake (127) ;
  //    set_drive_pid (drive, 10, DRIVE_SPEED) ;
  //    wait_drive() ;
  //    set_drive_pid(turn, 150, DRIVE_SPEED) ;
  //    wait_drive() ;
  //    set_drive_pid(drive, 32, DRIVE_SPEED/4) ;
  //    wait_drive() ;
  //    set_drive_pid(drive, -35, DRIVE_SPEED) ;
  //
  //
  //    intake (0) ;


}

//
//
// FOR LEFT SIDE (odds)
//
//

void
auto_2() { // ring row and AWP


  // lift 6bar
    claw (true) ;
    set_lift_position(446, 100);
    pros::delay(750) ;
  // drive forward
    set_drive_pid(drive, -20, DRIVE_SPEED);
    wait_drive();
  // block(false);
    claw (false);
  // run intake
    intake(127);
    pros::delay (50) ; // check time
  // drive back
    set_drive_pid (drive, 15, DRIVE_SPEED) ;
    wait_drive() ;
  // face toward ring row
    set_drive_pid(turn, 140, DRIVE_SPEED) ;
    wait_drive() ;
  // drive
    set_drive_pid (drive, 10, DRIVE_SPEED) ;
    wait_drive() ;
  // face ring row
    set_drive_pid(turn, 150, DRIVE_SPEED) ;
    wait_drive() ;
  // drive forward and pick up
    set_drive_pid(drive, 32, DRIVE_SPEED/4) ;
    wait_drive() ;
  // retreat
    set_drive_pid(drive, -35, DRIVE_SPEED) ;

    intake (0) ;

}


//
//
// FOR RIGHT SIDE
//
//

void
auto_3() {
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



// /
//  Wait Until and Changing Max Speed
// /
void
auto_4() {

  // lower FMogo
    //set_mogo_position(780, 127) ;
    mogo_out() ;
    flock(true) ;
  // rush
    set_drive_brake(MOTOR_BRAKE_COAST);
    set_drive_pid(drive, 37, DRIVE_SPEED) ; // was 40
    wait_drive() ;
    set_drive_brake(MOTOR_BRAKE_BRAKE);
  // retreat
    flock(false) ;
    pros::delay (500) ;
    mogo_in () ; // test
    set_drive_pid(drive, -19.5, DRIVE_SPEED) ; // was 18.5

  // back lift up
    //set_lift_position(446, 100);
    mogo_in () ;
    wait_drive() ;
  // prepare claw
    claw(true) ;
  // turn to reverse face mogo
    set_drive_pid(turn, -90, DRIVE_SPEED) ; // change to angle from AUTON 2
    wait_drive() ;
  // drive into mogo
    set_drive_pid(drive, -15, DRIVE_SPEED) ;
    wait_drive () ;
  // claw grab
    claw(false) ;
  // drop rings
    intake (127) ;
  // back up
    set_drive_pid (drive, 8, DRIVE_SPEED) ;
    wait_drive() ;
  // turn
    set_drive_pid(turn, 0, DRIVE_SPEED) ;
    wait_drive() ;
  // drive and collect row
    set_drive_pid(drive, 35, DRIVE_SPEED/4) ;
    wait_drive() ;
  // retreat
    set_drive_pid(drive, -45, DRIVE_SPEED) ;
    wait_drive () ;



    intake (0) ;
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
auto_9() {

}



void
auto_10() {

}
