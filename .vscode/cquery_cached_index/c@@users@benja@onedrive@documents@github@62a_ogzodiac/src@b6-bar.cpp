#include "main.h"


const int num_of_pos = 6; // Number of lift positions // was 5
const int lift_heights[num_of_pos] = {0, 0, 575, 321, 575, 140}; // Lift Positions
//                          {pick_up/ready , compact/drive, lift_above_platform, place_on_platform, max_height}

// Driver Control Variables
int up_lock = 0;
int down_lock = 0;
int lift_state = 0 ; //<-- when switch to drive mode, start here

int b_press = 0 ;
bool b_lock = true ;

pros::Motor lift(10, MOTOR_GEARSET_36, false, MOTOR_ENCODER_DEGREES);

//bmogo lock
pros::ADIDigitalOut sixLock(7);


void sixlock(bool position)
{
  sixLock.set_value(position);
}

void setLiftStart (int position)
{
  lift_state = position ;
}

//back claw (under conveyor)
pros::ADIDigitalOut Claw (6);

int claw_state = 0 ;

void claw (bool position)
{
  Claw.set_value (position) ;
}

pros::ADIDigitalIn limiter (4) ;

bool limit_switch ()
{
  if (limiter.get_value () == 0)
    return false ;
  return true ;
}

void set_lift(int input)  { lift = input; }

void zero_lift()    { lift.tare_position(); }
int  get_lift()     { return lift.get_position(); }
int  get_lift_vel() { return lift.get_actual_velocity(); }

void set_lift_position(int target, int speed)
{
  //printf("Lift Position: %d \n", target);
  lift.move_absolute(target, speed);
}

///
// Driver Control
//  - when R1 is pressed, bring the lift up the position ladder
///
void
lift_control(void*) {
  // move lift value up
  while(1)
  {
  if (master.get_digital(DIGITAL_R1) && up_lock==0) {
    printf("R1 \n") ;
    // If lift value is at max, bring it down to 0
    if(!b_lock)
    {
      lift_state = num_of_pos - 2;
      b_lock = !b_lock ;
    }
    else if(lift_state==num_of_pos-2 || lift_state==num_of_pos - 1)
      lift_state = 0;
    // Otherwise, bring the lift value up
    else
      lift_state++;


    up_lock = 1;
  }

  // //special position for intaking rings
  // else if (master.get_digital(DIGITAL_B) && b_press == 0) {
  //   printf("b \n") ;
  //   if (b_lock)
  //     lift_state = num_of_pos - 1 ;
  //   else if (!b_lock)
  //     lift_state = num_of_pos - 2 ;
  //
  //   b_lock = !b_lock ;
  //   b_press = 1 ;
  //
  // }

  // else if (!master.get_digital(DIGITAL_R1) && !master.get_digital(DIGITAL_B)) {

  //actual motor moving stuff
    if(lift_state == 0)
    {
      //actuate pneumatic
      sixlock(false);
      //move motor to pos
      set_lift_position(lift_heights[lift_state], 100);
    }
    else if (lift_state == 1)
    {
      set_lift_position(lift_heights[lift_state], 100) ;
      pros::delay (150) ;
      sixlock (true) ;
    }
    else if (lift_state == 3)
    {
      set_lift_position(lift_heights[lift_state], 100);
      pros::delay(250) ;
      sixlock(false) ;
    }

    else
    {
      //deactuate pneumatic
      sixlock(true);
      //move motor to pos
      set_lift_position(lift_heights[lift_state], 100);
    }

  // }



  // if (!master.get_digital(DIGITAL_B))
  // {
  //   b_press = 0 ;
  // }
  if (!master.get_digital(DIGITAL_R1))
  {
    up_lock = 0 ;
  }


  // activate MogoClaw
  if (master.get_digital(DIGITAL_L2) && claw_state == 0)
  {
    //activate claw
    printf("open \n");
    claw_state = 1 ;
    claw(true) ;
  }
  else if (master.get_digital(DIGITAL_L2) && claw_state == 1)
  {
    //deactivate claw
    claw_state = 0 ;
    claw(false) ;
  }

  pros::delay (20) ;
}
}
