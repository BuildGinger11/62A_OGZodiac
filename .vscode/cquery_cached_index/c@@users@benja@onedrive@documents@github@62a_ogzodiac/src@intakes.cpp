#include "main.h"

pros::Motor Conveyor(10) ; //<-- reversed

void intake(int power)
  {Conveyor.move(power);}
int getIntakePos ()
  {return Conveyor.get_position() ;}

int crossThreshold = 0;
bool lockedMogo ()
{
  if (getIntakePos() > 3000)
  {
    crossThreshold = 1 ;
  }
  if (crossThreshold == 1)
    return true ;
  else
    return false ;
}

void Intake_Control(void*)
{
  while(true)
  {
    //printf("master: %d\n", master.get_digital(DIGITAL_L1));
    if(master.get_digital(DIGITAL_L1))
    {
      intake(80); // max: 127
    }
    else if(master.get_digital(DIGITAL_DOWN))
    {
      intake(-127);
    }
    else
    {
      intake(0);
    }
  pros::delay(20);
  }
}
