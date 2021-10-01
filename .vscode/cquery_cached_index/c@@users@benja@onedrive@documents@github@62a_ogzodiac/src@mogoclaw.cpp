#include "main.h"

pros::ADIDigitalOut Claw (6);

void claw (bool position)
{
  Claw.set_value (position) ;
}

