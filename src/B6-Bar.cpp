#include "main.h"


const int num_of_pos = 7; // Number of lift positions // was 5
const int lift_heights[num_of_pos] = {0, 0, 650, 400, 400, 650, 325}; // Lift Positions
//                          {ready, grab, above plat, on plat, release on plat, above plat, }

// Driver Control Variables
int up_lock = 0;
int down_lock = 0;

int lift_state = 0 ;

int a_press = 0 ;
bool b_lock = true ;

int b_press = 0 ;

int clawLock = 0 ;


int x_lock = 0 ;
int XTimer = 0 ;

pros::Motor lift(10, MOTOR_GEARSET_36, true, MOTOR_ENCODER_DEGREES);

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

void moveLift (int power)
{
  lift.move (power) ;
}

void set_lift_position(int target, int speed)
{
  //printf("Lift Position: %d \n", target);
  lift.move_absolute(target, speed);
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

//  special position for intaking rings
  else if (master.get_digital(DIGITAL_A) && a_press == 0) {
     printf("b \n") ;
     lift_state = 1;

    a_press = 1 ;

  }

  else if (master.get_digital(DIGITAL_B) && b_press == 0)
  {
    lift_state = 6 ;
    b_press = 1 ;
    b_lock = false ;
  }

  else if (!master.get_digital(DIGITAL_X)) {

  //actual motor moving stuff
    if(lift_state == 0)
    {
      //claw activated to allow space
      claw(true) ;
      //actuate pneumatic
      sixlock(false);
      //move motor to pos
      set_lift_position(lift_heights[lift_state], 100);
    }
    else if (lift_state == 1)
    {
      // claw in
      claw(true) ;
      set_lift_position(lift_heights[lift_state], 100) ;
      sixlock (true) ;
    }
    else if (lift_state == 4)
    {
      set_lift_position(lift_heights[lift_state], 100) ;
      sixlock(false) ;
    }
    else if (lift_state == 5)
    {
      set_lift_position(lift_heights[lift_state], 100) ;
    }

    else
    {
      //deactuate pneumatic
      sixlock(true);
      //move motor to pos
      set_lift_position(lift_heights[lift_state], 100);
    }

  }



  if (!master.get_digital(DIGITAL_A))
  {
    a_press = 0 ;
  }
  if (!master.get_digital(DIGITAL_R1))
  {
    up_lock = 0 ;
  }
  if (!master.get_digital(DIGITAL_B))
  {
    b_press = 0 ;
  }


//reset lift if we are dumb

  if (master.get_digital(DIGITAL_X))
  {
    moveLift(-100) ;
    pros::delay(250) ;
    while (limit_switch () == false)
    {
      moveLift (-100) ;
    }
    moveLift (0) ;
    printf("tared \n") ;
    lift.tare_position() ;
    lift_state = 0 ;
  }
  if (!(master.get_digital(DIGITAL_X)))
  {
    x_lock = 0 ;
  }



  // activate MogoClaw
  if (master.get_digital(DIGITAL_L2) && claw_state == 0 && clawLock == 0 && (lift_state != 0 || lift_state != 1))
  {
    //activate claw
    printf("open \n");
    claw_state = 1 ;
    claw(false) ;
    clawLock = 1 ;
  }
  else if (master.get_digital(DIGITAL_L2) && claw_state == 1 && clawLock == 0 && (lift_state != 0 || lift_state != 1))
  {
    //deactivate claw
    claw_state = 0 ;
    claw(true) ;
    clawLock = 1 ;
  }
  else if (!master.get_digital(DIGITAL_L2) && (lift_state == 0 || lift_state == 1))
  {
    claw (true) ;
    clawLock = 0 ;
  }
  else if (!master.get_digital(DIGITAL_L2))
  {
    clawLock = 0 ;
  }

  pros::delay (20) ;
  }
}
