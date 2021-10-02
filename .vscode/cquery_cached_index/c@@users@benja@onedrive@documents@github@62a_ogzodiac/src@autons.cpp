#include "main.h"

const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries ot heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;

///
// Constants
///

// Reset all constants to default (what's in setup.hpp is default)
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

// Functions to change constants
// (if the robot has different weight to it, sometimes we need to change constants)
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



// All drive movements use the "set_drive_pid" function
// the first parameter is the type of motion (drive, turn, r_swing, l_swing)
// below are example codes using each type


///
// Drive Example
///
void
auto_1() //dead does nothing
{
  // flock(true);
  // set_drive_pid(drive, 50, 127);
  // for (int i=0; i<1000; i++) {
  //   //mogo_out(false);
  //   pros::delay(1);
  // }
  // pros::delay(200);
  // flock(false);
  // set_drive_pid(drive, -50, 127);
  // mogo_in(true);
  // wait_drive();

}




void
//god auton
auto_2() {

  //mogo_outB(true);
  //block(true);
//lift 6bar
  claw (true) ;
  set_lift_position(446, 100);
  pros::delay(750) ;
//drive forward
  set_drive_pid(drive, -10, DRIVE_SPEED);
  wait_drive();
  //block(false);
  pros::delay(100);
  //mogo_inB(true);
  pros::delay(400);
  claw (false);
//run intake
  intake(127);
  pros::delay (3000) ;

//DRIVE BACK, DROP GOAL, RUSH MID
//shut off intake
  //intake (0) ;
//drop stuff
  //claw (true) ;
//drive back
  //set_drive_pid(drive, 20, DRIVE_SPEED) ;
  //wait_drive () ;
//turn
  //set_drive_pid(left, 30, DRIVE_SPEED) ; //make sure about angle and direction
  //wait_drive () ;
//return B6Bar to norm
  //set_lift_position (0, 100) ;
//rush mid
  //set_drive_pid(drive, 240, DRIVE_SPEED) ; //ensure distance correct

//DRIVE BACK, PLACE GOAL ON PLATFORM, RUSH MID


  //turns everything off like a sane person
  intake (0) ;


}


void
auto_3() { //testing stuff here
  //lift 6bar
    claw (true) ;
    set_lift_position(446, 100);
    pros::delay(750) ;
  //drive forward
    set_drive_pid(drive, -10, DRIVE_SPEED);
    wait_drive();
    //block(false);
    pros::delay(100);
    //mogo_inB(true);
    pros::delay(400);
    claw (false);
  //run intake
    intake(127);
    pros::delay (3000) ;
    intake (0) ;
  //drive back
    set_drive_pid(drive, 10, DRIVE_SPEED);
    wait_drive () ;
  //turn
    set_drive_pid(turn, -90, DRIVE_SPEED) ;
    wait_drive () ;
  //set down F4bar
    
  //rush time
    set_drive_pid(drive, 240, DRIVE_SPEED) ; //check distance
  //pick up


    //turns everything off like a sane person
    intake (0) ;

}



///
// Wait Until and Changing Max Speed
///
void
auto_4() {
  // wait_until will wait until the robot gets to a desired position


  // When the robot gets to 12 inches, the robot will travel the remaining distance at a max speed of 40
  set_drive_pid(drive, 24, DRIVE_SPEED, true);
  wait_until(12);
  set_max_speed(40); // After driving 12 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  wait_drive();

  set_drive_pid(turn, 45, TURN_SPEED);
  wait_drive();

  set_drive_pid(turn, -45, TURN_SPEED);
  wait_drive();

  set_drive_pid(turn, 0, TURN_SPEED);
  wait_drive();

  // When the robot gets to -12 inches, the robot will travel the remaining distance at a max speed of 40
  set_drive_pid(drive, -24, DRIVE_SPEED, true);
  wait_until(-12);
  set_max_speed(40); // After driving 12 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  wait_drive();
}



///
// Swing Example
///
void
auto_5() {
  // The second parameter is target degrees
  // The third parameter is speed of the moving side of the drive

  set_drive_pid(l_swing, 45, SWING_SPEED);
  wait_drive();

  set_drive_pid(drive, 24, DRIVE_SPEED, true);
  wait_until(12);

  set_drive_pid(r_swing, 0, SWING_SPEED);
  wait_drive();
}



///
// Auto that tests everything
///
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
  //mogo_outB(true);
  //block(true);
  set_drive_pid(drive, 10, DRIVE_SPEED);
  wait_drive();
  //block(false);
  pros::delay(100);
  //mogo_inB(true);
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
