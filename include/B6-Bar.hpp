#pragma once

void set_lift(int input);
void zero_lift();
int get_lift();
int get_lift_vel();

void set_lift_position(int target, int speed);

void claw (bool position) ;

void lift_control(void*);

bool limit_switch () ;
