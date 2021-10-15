#include "main.h"

const int MOGO_OUT  = 820;
const float MOGO_KP = 0.5;
//const int DELAY_TIME = 10;
// Driver Control Parameters
bool mogo_up = true;
//bool is_at_neut = false;
int mogo_lock   = 0;
int controller_mogo_timer = 0;
int mogo_out_timer = 0;

bool is_up = false;
//bool is_neut = false;
bool is_out = false;


pros::Motor mogo(6, MOTOR_GEARSET_36, false, MOTOR_ENCODER_DEGREES);
pros::ADIDigitalOut FLock(8);

//touch sensor
pros::ADIDigitalIn touchSense (5) ;

bool touch ()
{
  if (touchSense.get_value () == 1)
    return true ;
  return false ;
}


void set_mogo(int input)
{
  mogo = input;
}
void flock(bool position)
{
  FLock.set_value(position);
}
void zero_mogo()
 {
   mogo.tare_position();
 }
int  get_mogo()
{
  return mogo.get_position();
}
int  get_mogo_vel()
{
  return mogo.get_actual_velocity();
}

void
set_mogo_position(int target, int speed)
{
  mogo.move_absolute(target, speed);
}

///
// Mogo Control
///

// Mogo In
void
mogo_in ()
 {
   flock(false);
   pros::delay(300);
  if (get_mogo()<200)
  {
    if (get_mogo_vel()==0 || touch())
     {
      is_up = true;
      set_mogo(0);
    }
    else
    {
      set_mogo(is_up?0:-60);
    }
  }
  else
  {
    is_up = false;
    set_mogo(-127);
  }
}



// Mogo Out
void
mogo_out()
 {
  if (get_mogo() > (MOGO_OUT-100))
  {
    if (get_mogo_vel()==0)
    {
      set_mogo(0);
      is_out = true;
    }
    else
     {
      mogo_out_timer+=DELAY_TIME;
      if (mogo_out_timer<500)
      {
        set_mogo(20);
        is_out = false;
      }
      else
      {
        set_mogo(0);
        is_out = true;
      }
    }
  }
  else
  {
    set_mogo(127);
    mogo_out_timer = 0;
    is_out = false;
  }

//test
  pros::delay(500) ;
  flock(true) ;

}


///
// Driver Control
//  - when L1 is pressed, toggle between in and out.
//  - when L1 is held and the mogo lift is out, bring the mogo lift to neutral position
///
void
mogo_control(void*)
{
  while(true)
  {
  // Toggle for mogo
    if (master.get_digital(DIGITAL_R2) && mogo_lock==0)
    {
    // if (is_at_neut)
    //   mogo_up = false;
    // else
    flock(false);
    pros::delay(300);
    mogo_in();
    //
    // is_at_neut = false;
    mogo_lock = 1;


    }
    if (master.get_digital(DIGITAL_R2) && mogo_lock==1)
    {
    // if (is_at_neut)
    //   mogo_up = false;
    // else
    mogo_out();
    pros::delay (600) ;
    //flock(true);
    //
    // is_at_neut = false;
    mogo_lock = 0;


    }

    pros::delay(20);
  }
}
