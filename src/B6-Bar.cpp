#include "main.h"


const int num_of_pos = 7; // Number of lift positions
const int lift_heights[num_of_pos] = {0, 0, 700, 1700, 1050, 1050, 1700}; // Lift Positions
    // {ready, grab, allow intaking, above plat, on plat, release on plat, above plat}

// Driver Control Variables
int up_lock = 0;
int down_lock = 0;

int lift_state = 1 ;
int locked = 0 ;

int a_press = 0 ;
bool b_lock = true ;

int b_press = 0 ;

int clawLock = 0 ;


// int x_lock = 0 ;
int XTimer = 0 ;

pros::Motor lift(9);




//bmogo lock
pros::ADIDigitalOut sixLock(4);


void sixlock(bool position)
{
  sixLock.set_value(position);
}

void setLiftStart (int position)
{
  lift_state = position ;
}





//back claw (under conveyor)
pros::ADIDigitalOut Claw (1);

int claw_state = 0 ;

void claw (bool position)
{
  Claw.set_value (position) ;
}

pros::ADIDigitalIn limiter (8) ;

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

void moveLift (int power)
{
  lift.move (power) ;
}

void set_lift_position(int target, int speed)
{
  //printf("Lift Position: %d \n", target);
  lift.move_absolute(target, speed);
}

bool wait_until_lift (int target, int speed)
{
  set_lift_position(target, speed);

  int beep = 0;
  while (get_lift() != target)
  {
    beep ++ ;
    pros::delay(20) ;
  }
  return true ;
}

void tareLift ()
{
  lift.tare_position() ;
}




///
// Driver Control
//  - when R1 is pressed, bring the lift up to new position in array
///
void
lift_control(void*) {
   //<-- when switch to drive mode, start here

  // move lift value up
  while(1)
  {
  if (lockedMogo() && master.get_digital(DIGITAL_R1) && up_lock==0)
  {
    // If lift value is at max, bring it down to 0
    // if(!b_lock)
    // {
    //   lift_state = num_of_pos - 2;
    //   b_lock = !b_lock ;
    // }
    if(lift_state==num_of_pos - 1)
      lift_state = 0;
    // Otherwise, bring the lift value up
    else
      lift_state++;


    up_lock = 1;
  }

  // don't let lift get tangled in front lift
  else if (!lockedMogo())
  {
    lift_state = 0 ;
  }

//  special position for platforming
  else if (master.get_digital(DIGITAL_A) && a_press == 0) {
     lift_state = 2;

    a_press = 1 ;

  }

  // else if (master.get_digital(DIGITAL_B) && b_press == 0)
  // {
  //   lift_state = 6 ;
  //   b_press = 1 ;
  //   b_lock = false ;
  // }

  //else if (!master.get_digital(DIGITAL_X)) {

  //actual motor moving stuff

    if(lift_state == 0)
    {

      set_lift_position(lift_heights[lift_state], 127) ;

      if (get_lift() < 20)
      {
        sixlock (false) ;
      }

    }
    else if (lift_state == 1)
    {
      // // claw in
      // claw(true) ;
      sixlock (true) ;
      set_lift_position(lift_heights[lift_state], 127) ;
    }
    else if (lift_state == 5)
    {
      set_lift_position(lift_heights[lift_state], 127) ;
      sixlock(false) ;
    }
    else if (lift_state == 6)
    {
      sixlock(true) ;

      set_lift_position(lift_heights[lift_state], 127) ;
      // no sixlock
    }

    else
    {
      //actuate pneumatic
      sixlock(true);
      //move motor to pos
      set_lift_position(lift_heights[lift_state], 127);
    }

    //}


  if (!master.get_digital(DIGITAL_A))
  {
    a_press = 0 ;
  }
  if (!master.get_digital(DIGITAL_R1))
  {
    up_lock = 0 ;
  }


//reset lift if we are dumb

  // if (master.get_digital(DIGITAL_X))
  // {
  //   moveLift(-100) ;
  //   pros::delay(250) ;
  //   while (limit_switch () == false)
  //   {
  //     moveLift (-100) ;
  //   }
  //   moveLift (0) ;
  //   printf("tared \n") ;
  //   lift.tare_position() ;
  //   lift_state = 0 ;
  // }
  // if (!(master.get_digital(DIGITAL_X)))
  // {
  //   x_lock = 0 ;
  // }



  // activate MogoClaw
  if (master.get_digital(DIGITAL_L2) && claw_state == 0 && clawLock == 0)
  {
    //activate claw
    printf("open \n");
    claw_state = 1 ;
    claw(false) ;
    clawLock = 1 ;
  }
  else if (master.get_digital(DIGITAL_L2) && claw_state == 1 && clawLock == 0)
  {
    //deactivate claw
    claw_state = 0 ;
    claw(true) ;
    clawLock = 1 ;
  }
  else if (!master.get_digital(DIGITAL_L2))
  {
    clawLock = 0 ;
  }

  pros::delay (20) ;
  }
}
