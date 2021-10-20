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
  RMogo.set_value(position) ;
  LMogo.set_value(position) ;
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
  mogo_lift(false);
  pros::delay(500);
  flock(false);


// test to make sure value



  // if (get_mogo()<200)
  // {
  //   if (get_mogo_vel()==0 || touch())
  //    {
  //     is_up = true;
  //     set_mogo(0);
  //   }
  //   else
  //   {
  //     set_mogo(is_up?0:-60);
  //   }
  // }
  // else
  // {
  //   is_up = false;
  //   set_mogo(-127);
  // }

}



// Mogo Out
void
mogo_out()
 {
  // if (get_mogo() > (MOGO_OUT-100))
  // {
  //   if (get_mogo_vel()==0)
  //   {
  //     set_mogo(0);
  //     is_out = true;
  //   }
  //   else
  //    {
  //     mogo_out_timer+=DELAY_TIME;
  //     if (mogo_out_timer<500)
  //     {
  //       set_mogo(20);
  //       is_out = false;
  //     }
  //     else
  //     {
  //       set_mogo(0);
  //       is_out = true;
  //     }
  //   }
  // }
  // else
  // {
  //   set_mogo(127);
  //   mogo_out_timer = 0;
  //   is_out = false;
  // }




  flock(true) ; // test make sure correct
  pros::delay(500) ;
  mogo_lift (true) ;


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
