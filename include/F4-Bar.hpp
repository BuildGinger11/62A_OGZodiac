#pragma once

extern bool mogo_up;

void set_mogo(int input);
void zero_mogo();
int get_mogo();
int get_mogo_vel();
void set_mogo_position(int target, int speed);
void flock(bool position);
void mogo_in  ();
void mogo_neut();
void mogo_out ();

void mogo_control(void*);
