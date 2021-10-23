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

bool is_down = false ;

// pros::Motor mogo(6, MOTOR_GEARSET_36, false, MOTOR_ENCODER_DEGREES);
pros::ADIDigitalOut FLock(8);

pros::ADIDigitalOut RMogo (2) ;
pros::ADIDigitalOut LMogo (5) ;




// void set_mogo(int input)
// {
//   mogo = input;
// }
void flock(bool position)
{
  FLock.set_value(position);
}

void mogo_lift (bool position)
{
  RMogo.set_value(!position) ;
  LMogo.set_value(!position) ;
}
// void zero_mogo()
//  {
//    mogo.tare_position();
//  }
// int  get_mogo()
// {
//   return mogo.get_position();
// }
// int  get_mogo_vel()
// {
//   return mogo.get_actual_velocity();
// }
//
// void
// set_mogo_position(int target, int speed)
// {
//   mogo.move_absolute(target, speed);
// }

///
// Mogo Control
///

// Mogo In
void
mogo_in ()
{
  flock(true);
  pros::delay(500);
  mogo_lift(false);

}



// Mogo Out
void
mogo_out()
{
   // test make sure correct
   mogo_lift (true) ;
   pros::delay(500) ;
   flock(false) ;

}
void
Auton_mogo_out()
{
   // test make sure correct
   mogo_lift (true) ;
   flock(false) ;

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
    printf("f1 \n") ;

      if (!is_down)
      {
        mogo_in();
      }
      else if (is_down)
      {
        mogo_out();
      }
      is_down = !is_down ;
      mogo_lock = 1;

    }

    else if (!master.get_digital(DIGITAL_R2))
    {
      mogo_lock = 0 ;
    }

    pros::delay(20);
  }
}
