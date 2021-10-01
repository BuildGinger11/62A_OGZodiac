#include "main.h"


const int num_of_pos = 5; // Number of lift positions
const int lift_heights[num_of_pos] = {75, 0, 446, 321, 660}; // Lift Positions
//                          {pick_up/ready , compact/drive, lift_above_platform, place_on_platform, max_height}

// Driver Control Variables
int up_lock = 0;
int down_lock = 0;
int lift_state = 0;


pros::Motor lift(10, MOTOR_GEARSET_36, false, MOTOR_ENCODER_DEGREES);

//bmogo lock
pros::ADIDigitalOut sixLock(7);


void sixlock(bool position)
{
  sixLock.set_value(position);
}

//back claw (under conveyor)
pros::ADIDigitalOut Claw (6);

int claw_state = 0 ;

void claw (bool position)
{
  Claw.set_value (position) ;
}


void set_lift(int input)  { lift = input; }

void zero_lift()    { lift.tare_position(); }
int  get_lift()     { return lift.get_position(); }
int  get_lift_vel() { return lift.get_actual_velocity(); }

void
set_lift_position(int target, int speed) {
  printf("Lift Position: %d \n", target);
  lift.move_absolute(target, speed);
}

///
// Driver Control
//  - when R1 is pressed, bring the lift up the position ladder
///
void
lift_control(void*) {
  // Lift Up
  while(1)
  {
  if (master.get_digital(DIGITAL_R1) && up_lock==0) {
    // If lift is at max height, bring it down to 0
    if(lift_state==num_of_pos-1)
      lift_state = 0;
    // Otherwise, bring the lift up
    else
      lift_state++;

    up_lock = 1;
  }
  else if (!master.get_digital(DIGITAL_R1)) {
    up_lock = 0;
  }


  // activate MogoClaw
  if (master.get_digital(DIGITAL_R2) && claw_state == 0)
  {
    //activate claw
    printf("open \n");
    claw_state = 1 ;
    claw(true) ;
    pros::delay (500) ;
  }
  else if (master.get_digital(DIGITAL_R2) && claw_state == 1)
  {
    //deactivate claw
    claw_state = 0 ;
    claw(false) ;
    pros::delay (500) ;
  }
  pros::delay (20) ;
}
}
