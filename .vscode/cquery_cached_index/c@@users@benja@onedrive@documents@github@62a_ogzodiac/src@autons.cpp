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



//
// PLATFORMING CODE V1?
//
// //platforming Drive
//   set_drive_pid(drive, -20, DRIVE_SPEED);
//   wait_drive();
//   while (get_gyroPitch() >= 10)
//   {
//     if (get_gyroPitch() > 20)
//       set_tank(-127, -127);
//     else
//       set_tank(-100, -100);
//   }
//   set_tank(0, 0);


void
auto_test() // now is tester auton
{
  set_drive_brake(MOTOR_BRAKE_COAST) ;
  set_drive_pid(drive, , DRIVE_SPEED) ;
}






void
auto_rightHomeRow() { // ring row and AWP

  // rush
    set_drive_brake(MOTOR_BRAKE_COAST);
    set_drive_pid(drive, 43, DRIVE_SPEED/1.25) ; // was 38
    // grip FMogo
    Auton_mogo_out () ;
    wait_drive() ;
    set_drive_brake(MOTOR_BRAKE_BRAKE);
  // retreat
    mogo_in () ; // test
    // set_mogo_position (-780, 127) ;
    set_drive_pid(drive, -24, DRIVE_SPEED) ;
  // back lift up
    set_lift_position(625, 100);
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
  set_drive_pid(l_swing, -35, DRIVE_SPEED) ; // test
  wait_drive() ;
  set_drive_pid(drive, 40, DRIVE_SPEED) ;
  wait_drive() ;
  //rush
  set_drive_pid(turn, -180, DRIVE_SPEED) ;
  wait_drive() ;
  set_drive_pid(drive, -90, DRIVE_SPEED) ;
  //raise lift
  set_lift_position(625, 100);
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
auto_AWPRightNeut() {
  //grab ally1 with 6bar
  tareLift() ;
  sixlock(false) ;
  set_lift_position(0, 100) ;
  pros::delay(250) ;
  set_drive_pid(drive, -7, DRIVE_SPEED) ;
  wait_drive() ;
  pros::delay(200) ;
  sixlock(true) ;

  intake(100) ;
  pros::delay(200) ;
  set_drive_pid(drive, 13, DRIVE_SPEED) ;

  intake(0) ;
  wait_drive() ;


  set_drive_pid(r_swing, -35, DRIVE_SPEED) ;
  wait_drive() ;
  set_drive_pid(drive, -40, DRIVE_SPEED) ;
  wait_drive() ;
  //rush
  set_drive_pid(turn, 0, DRIVE_SPEED) ;
  wait_drive() ;
  set_drive_pid(drive, -90, DRIVE_SPEED/1.5) ;
  //raise lift
  set_lift_position(625, 50);
  claw (false) ;
  int timer = 0 ;
  pros::delay(500) ; // make sure drive doesnt die
  while (!limit_switch() && timer < 400) {
    timer++;
    pros::delay(10);
  }
  claw (true) ;
  pros::delay(250) ;
  intake (100) ;
  pros::delay(500) ;
  //allign iwht right neut
  set_drive_pid(drive, 26, DRIVE_SPEED) ; // check to alligh
  wait_drive() ;
  intake(0) ;
  set_drive_pid(turn, 90, DRIVE_SPEED) ;
  wait_drive() ;
  mogo_out() ;
  set_drive_pid(drive, 15, DRIVE_SPEED/1.25) ;
  wait_drive() ;
  mogo_in() ;
  //retret
  set_drive_pid(drive, -35, DRIVE_SPEED) ;
  wait_drive() ;

}



void
auto_AWPLeftNeut()
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
  intake(100) ;
  pros::delay(300) ;
  intake (0) ;
  //lift up
  set_lift_position(700, 100) ;
  pros::delay(500) ;
  set_drive_pid(drive, 3, DRIVE_SPEED) ;
  wait_drive() ;
  //turn
  set_drive_pid(turn, 90, DRIVE_SPEED/1.5) ;
  wait_drive() ;

  //rush neutral
  mogo_out() ;
  set_drive_pid(drive, 43, DRIVE_SPEED/1.5) ;
  pros::delay(250) ;
  set_lift_position(120, DRIVE_SPEED) ;
  wait_drive() ;
  //grab neutral
  mogo_in() ;

  //retreat
  set_drive_pid(drive, -22, DRIVE_SPEED) ;
  wait_drive() ;
  set_drive_pid(turn, 0, DRIVE_SPEED) ;
  wait_drive() ;
  set_drive_pid(drive, -110, DRIVE_SPEED) ;
  //raise lift
  set_lift_position(625, 100);
  claw (false) ;
  int timer = 0 ;
  pros::delay(500) ;
  while (!limit_switch() && timer < 500) {
    timer++;
    pros::delay(10);
  }
  claw (true) ;
  pros::delay(250) ;
  intake (100) ;
  pros::delay(500) ;
  set_drive_pid(drive, 30, DRIVE_SPEED) ;

}




void
auto_AWPCenterNeut()
{
  //grab ally1 with 6bar
  tareLift() ;
  sixlock(false) ;
  set_lift_position(0, 100) ;
  pros::delay(250) ;
  set_drive_pid(drive, -7, DRIVE_SPEED) ;
  wait_drive() ;
  pros::delay(200) ;
  sixlock(true) ;

  intake(100) ;
  pros::delay(200) ;
  set_drive_pid(drive, 13, DRIVE_SPEED) ;

  intake(0) ;
  wait_drive() ;


  set_drive_pid(r_swing, -35, DRIVE_SPEED) ;
  wait_drive() ;
  set_drive_pid(drive, -40, DRIVE_SPEED) ;
  wait_drive() ;
  //rush
  set_drive_pid(turn, 0, DRIVE_SPEED) ;
  wait_drive() ;
  set_drive_pid(drive, -90, DRIVE_SPEED/1.5) ;
  //raise lift
  pros::delay(200) ;
  set_lift_position(625, 50);
  claw (false) ;
  int timer = 0 ;
  pros::delay(500) ; // make sure drive doesnt die
  while (!limit_switch() && timer < 400) {
    timer++;
    pros::delay(10);
  }
  if (limit_switch())
  {
    claw (true) ;
    pros::delay(250) ;
    intake (100) ;
    pros::delay(500) ;
    //allign iwht tall neut
    set_drive_pid(drive, 26, DRIVE_SPEED) ; // check to alligh
    wait_drive() ;
    // face tall
    set_drive_pid(turn, 45, DRIVE_SPEED) ;
    wait_drive() ;
    mogo_out() ;
    set_drive_pid(drive, 32, DRIVE_SPEED) ;
    wait_drive() ;
    // grab
    mogo_in() ;

    intake(0) ;
    set_drive_pid(drive, -40, DRIVE_SPEED) ;
    wait_drive() ;
  }
  else if (!limit_switch())
  {
    claw (true) ;
    pros::delay(250) ;
    intake (100) ;
    pros::delay(500) ;
    //allign iwht tall neut
    set_drive_pid(drive, 26, DRIVE_SPEED) ; // check to alligh
    wait_drive() ;
    intake(0) ;
    // face tall
    set_drive_pid(turn, 45, DRIVE_SPEED) ;

    set_lift_position(30, 100) ;

    wait_drive() ;
    mogo_out() ;
    set_drive_pid(drive, 32, DRIVE_SPEED) ;
    wait_drive() ;
    // grab
    mogo_in() ;
    set_drive_pid(drive, -40, DRIVE_SPEED) ;
    wait_drive() ;
  }
}


void
auto_allianceRight ()
{
  // rush rightside neut
  tareLift() ;
  sixlock(false) ;
  set_lift_position(0, 100) ;
  set_drive_brake(MOTOR_BRAKE_COAST);
  set_drive_pid(drive, -47, DRIVE_SPEED/1) ; // was 38

// grab with sixLock

  wait_drive() ;
  set_drive_brake(MOTOR_BRAKE_BRAKE);
// get right neut
  sixlock(true) ;

  setLiftStart(1) ;

  pros::delay(50) ;
  set_lift_position(50, DRIVE_SPEED) ;
  mogo_out() ;
  // face tall
  set_drive_pid(l_swing, 125, DRIVE_SPEED) ;
  wait_drive() ;
  // grab tall
  set_drive_pid(drive, 10, DRIVE_SPEED) ;
  wait_drive() ;
  mogo_in() ;
  set_lift_position(600, 100) ;
  // align with ally
  set_drive_pid(turn, 137, DRIVE_SPEED) ;
  wait_drive() ;
  set_drive_pid(drive, -41, DRIVE_SPEED) ;
  wait_drive() ;
  claw(false) ;
  //face ally mogo
  set_drive_pid(turn, 90, DRIVE_SPEED) ;
  wait_drive() ;
  set_drive_pid(drive, -40, DRIVE_SPEED) ;
  timer = 0 ;
  // get ally mogo
  while (!limit_switch() && timer < 150) {
    timer++;
    pros::delay(10);
  }
  pros::delay(250) ;
  claw (true) ;
  pros::delay(250) ;
  intake (115) ;

// back up
  set_drive_pid (drive, 12, DRIVE_SPEED) ;
  wait_drive() ;
// turn
  set_drive_pid(turn, 180, DRIVE_SPEED/1.5) ;
  wait_drive() ;
// drive and collect row
  set_drive_pid(drive, 20, DRIVE_SPEED/2) ;
  wait_drive() ;
// retreat
  set_drive_pid(drive, -35, DRIVE_SPEED) ;
  wait_drive () ;
  // make lift grab
}




void
auto_allianceLeft ()
{
  tareLift() ;
  sixlock(false) ;
  set_lift_position(0, 100) ;
  set_drive_brake(MOTOR_BRAKE_COAST);
  set_drive_pid(drive, -47, DRIVE_SPEED/1) ; // was 38

// grab with sixLock

  wait_drive() ;
  set_drive_brake(MOTOR_BRAKE_BRAKE);
// get right neut
  sixlock(true) ;

  setLiftStart(1) ;

  pros::delay(50) ;
  set_lift_position(50, DRIVE_SPEED) ;
  mogo_out() ;
  set_drive_pid(r_swing, -125, DRIVE_SPEED) ; // test angle adn type
  wait_drive() ;
  set_drive_pid(drive, 10, DRIVE_SPEED) ;
  wait_drive() ;
  mogo_in() ;
  set_lift_position(600, 100) ;
  set_drive_pid(drive, -10, DRIVE_SPEED) ;
  wait_drive() ;
  set_drive_pid(turn, -180, DRIVE_SPEED/1.5) ;
  wait_drive() ;
  set_drive_pid(drive, -47, DRIVE_SPEED) ;
  wait_drive() ;
  set_drive_pid(turn, -90, DRIVE_SPEED) ;
  claw(false) ;
  wait_drive() ;
  set_drive_pid(drive, -30, DRIVE_SPEED) ;
  timer = 0 ;
  while (!limit_switch() && timer < 150) {
    timer++;
    pros::delay(10);
  }
  claw (true) ;
  pros::delay(250) ;
  intake (115) ;
  set_tank(0, 0) ;
}









void
auto_skillz() {
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
  //lift up
  set_lift_position(700, 100) ;
  pros::delay(500) ;
  set_drive_pid(drive, 3, DRIVE_SPEED) ;
  wait_drive() ;
  //turn
  set_drive_pid(turn, 90, DRIVE_SPEED/1.5) ;
  wait_drive() ;

  //rush neutral
  mogo_out() ;
  set_drive_pid(drive, 50, DRIVE_SPEED/1.5) ;
  pros::delay(250) ;
  set_lift_position(120, 100) ;
  wait_drive() ;
  //grab neutral
  mogo_in() ;

  //move to position
    set_drive_pid(turn, -46, DRIVE_SPEED) ;
    wait_drive() ;
    //drive in front of platform
    set_drive_pid(drive, -46, DRIVE_SPEED) ; // was -44
    wait_drive() ;
  //place ally mogo
    set_lift_position(700, 100) ;
    pros::delay(400) ;
    set_drive_pid(turn, -108, DRIVE_SPEED/1.5) ; // was -108
    wait_drive() ;
    //reverse into platform
    set_drive_pid(drive, -19, DRIVE_SPEED) ;
    wait_drive() ;
    //drop lift
    set_lift_position(400, 90) ;
    //set_drive_pid(turn, -105, DRIVE_SPEED) ;
    wait_drive() ;
    pros::delay(2000) ;
    sixlock(false) ;
    pros::delay(750) ;
    set_drive_pid(drive, 10, DRIVE_SPEED) ;
    pros::delay (200) ;
    set_lift_position(650, 100) ;
    wait_drive() ;

  //platform neutral
    set_drive_pid(turn, -180, DRIVE_SPEED) ;
    wait_drive() ;
    //drop
    mogo_out() ;
    set_drive_pid(drive, 15, DRIVE_SPEED/1.5) ;
    wait_drive() ;
    set_drive_pid(drive, -10, DRIVE_SPEED) ;
    wait_drive() ;
    mogo_in() ;
    //face neutral
    set_drive_pid(turn, 0, DRIVE_SPEED) ;
    set_lift_position(0, 100) ;
    wait_drive() ;
    //grab
    sixlock(false) ;
    set_drive_pid(drive, -34, DRIVE_SPEED/1.5) ;
    wait_drive() ;
    pros::delay(200) ;
    sixlock(true) ;
    pros::delay(300) ;
    //platform neut

    set_drive_pid(drive, 20, DRIVE_SPEED) ; //was 22

    set_lift_position(700, 100) ;
    wait_drive() ;
    //face to platform
    set_drive_pid(turn, -85, DRIVE_SPEED/1.75) ;
    wait_drive() ;
    set_drive_pid(drive, -19, DRIVE_SPEED/1.5) ;
    wait_drive() ;
    set_lift_position(400, 100) ;
    //place
    pros::delay(750) ;
    sixlock(false) ;
    pros::delay(500) ;
    //escape
    set_drive_pid(drive, 15, DRIVE_SPEED) ;
    pros::delay(200) ;
    set_lift_position(650, 100) ;
    wait_drive() ;

    // get position for tall neut
    set_drive_pid(turn, 0, DRIVE_SPEED) ;
    wait_drive() ;
    set_drive_pid(drive, 15, DRIVE_SPEED) ; // align with tall
    wait_drive() ;
  //platform tall neutral
    //face tall neutral
    set_drive_pid(turn, 90, DRIVE_SPEED) ;

    // zero lifts and stuff wahwighwarfhowrgbvwrngvjkebf
    while (limit_switch () == false)
    {
      moveLift (-100) ;
    }
    moveLift (0) ;
    zero_lift() ;

    wait_drive() ;
    //drive tall neut
    set_drive_pid(drive, -30, DRIVE_SPEED/1.5) ;
    sixlock(false) ;
    wait_drive() ;
    //grab
    pros::delay(500) ;
    sixlock(true) ;
    pros::delay(750) ;

    //face drive to platform
    set_drive_pid(turn, 262, DRIVE_SPEED/1.75) ; //was 264
    wait_drive() ;

    // ben method
    //lift up
    set_lift_position(700, 100) ;
    pros::delay(2000);
    //drive into
    set_drive_pid(drive, -52, DRIVE_SPEED/1.5) ;
    pros::delay (1100) ;
    set_lift_position(390, 60) ;
    wait_drive() ;

    // // dru method <-- F
    // //lift up
    // set_lift_position(800, 100) ;
    // //drive into
    // set_drive_pid(drive, -47, DRIVE_SPEED/2) ;
    // pros::delay(1750);
    // set_lift_position(390, 100) ;
    // wait_drive() ;


    //place
    pros::delay(750) ;
    sixlock(false) ;
    pros::delay(750) ;

    //escape
    set_drive_pid(drive, 13, DRIVE_SPEED) ;
    pros::delay(250) ;
    set_lift_position(650, DRIVE_SPEED) ;
    wait_drive() ;

    //get last neut
    set_drive_pid(turn, 37, DRIVE_SPEED) ;
    wait_drive() ;
    set_lift_position(0, 115) ;
    sixlock(false) ;
    pros::delay(200) ;
    set_drive_pid(drive, -49, DRIVE_SPEED/1.5) ;
    wait_drive() ;
    // grab
    pros::delay(500) ;
    sixlock(true) ;
    pros::delay(750) ;
    // back to the platform
    set_drive_pid(drive, 43, DRIVE_SPEED) ;
    set_lift_position(650, 100) ;
    wait_drive() ;
    set_drive_pid(turn, -95, DRIVE_SPEED/1.5) ;
    wait_drive() ;
    set_drive_pid(drive, -19, DRIVE_SPEED) ;
    wait_drive() ;
    // place
    set_lift_position(400, 100) ;
    pros::delay(750) ;
    sixlock(false) ;
    pros::delay(500) ;
    //escape
    set_drive_pid(drive, 13, DRIVE_SPEED) ; // was 11
    pros::delay(250) ;
    set_lift_position(650, 100) ;
    wait_drive() ;



    // get ally1
    set_drive_pid(turn, -180, DRIVE_SPEED) ; // was -180
    wait_drive() ;
    set_lift_position(0, 100) ;
    // reverse into
    set_drive_pid(drive, -67, DRIVE_SPEED/1.25) ;
    pros::delay(250) ;
    //grab
    sixlock(false) ;
    wait_drive() ;
    sixlock(true) ;
    //rush opposite platform
    set_drive_pid(drive, 60, DRIVE_SPEED) ;
    wait_drive() ;
    //face plat
    set_drive_pid(turn, -270, DRIVE_SPEED) ;
    wait_drive() ;
    //lift and drive
    set_drive_pid(drive, -85, DRIVE_SPEED) ;
    set_lift_position(650, 100) ;
    wait_drive() ;

    //platform
    set_lift_position(390, 60) ;
    pros::delay(1500) ;
    sixlock(false) ;
    pros::delay(750) ;

    //escape
    set_drive_pid(drive, 10, DRIVE_SPEED) ;
    pros::delay(250) ;
    set_lift_position(650, DRIVE_SPEED) ;
    wait_drive() ;
}



void
auto_basic() { //can't go wrong
  // lift 6bar
    claw (true) ;
    set_lift_position(625, 100);
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
