
// Copyright 2024 Neil Kirby
/* Edtied by Elijah Paulman */
// Not for distribution without permission

// list < > style headers first
#include <stdio.h>
#include <math.h>

// includ3 constants and structs next
#include "structs.h"
#include "btp.h"
#include "libll.h"

// defines 
#include "constants.h"

// include function declarations after that
#include "output.h"

// include our own file last
#include "physics.h"

// stuff only we should know about
#define FLAG_LIMIT (13.25)
#define G ( -10.0 )

// true if close enough to collect
bool close_enough( double x1, double y1, double x2, double y2)
{
	double dx = x1-x2;
	double dy = y1-y2;
	double dist = sqrt( (dx*dx) + (dy*dy));
	return (dist <= 0.5);

}

// true if the mascot is left of the flag
bool is_left_of_flag(void *data, void *helper)
{
	struct Buckeye *brutus = data;
	return( brutus->x_position < FLAG_LIMIT);

}

// basic motion of brutus
static void basic_motion(struct Buckeye *brutus)
{

	brutus->x_position += DELTA_TIME * brutus->x_velocity;
	brutus->y_position += brutus->y_velocity * DELTA_TIME + 
		0.5* G * DELTA_TIME * DELTA_TIME;
	brutus->y_velocity += G * DELTA_TIME;
}

// adjusts brutus position
static void make_adjustments(struct Buckeye *brutus)
{
	double XA = btp_X_adjustment(brutus->x_position, brutus->y_position);
	brutus->x_position += XA;
	double YA = btp_Y_adjustment(brutus->x_position, brutus->y_position);
	brutus->y_position += YA;

	if(YA != 0.0) brutus->y_velocity = 0.0;
}

// checks for floor and ceiling
static void floor_and_ceiling(double oldVY, struct Buckeye *brutus)
{
	if((oldVY != 0.0) && (brutus->y_velocity == 0.0))
	{
		// if I was moving in Y and now I am not, I hit
		// the floor (or maybe a ceiling)
		if(oldVY < 0.0)floor_message(brutus);
		if(oldVY > 0.0)ceiling_message(brutus);
	}

}

// jumps brutus if needed
static void maybe_jump(double oldX, double oldY, struct Buckeye*brutus)
{
	// I didn't move, I have to jump.
	if(oldX == brutus->x_position && oldY == brutus->y_position) 
	{
	    brutus->y_velocity = brutus->jump_velocity;
	    jump_message(brutus);
	}

}

// moves brutus
static void move_brutus(void * data)
{
	struct Buckeye *brutus = data;

	if(is_left_of_flag(brutus, NULL))
	{

	    double oldX = brutus->x_position, oldY = brutus->y_position;
	    double oldVY = brutus->y_velocity;

	    basic_motion(brutus);
	    make_adjustments(brutus);
	    floor_and_ceiling(oldVY, brutus);
	    maybe_jump(oldX, oldY, brutus);
	    if(!is_left_of_flag(brutus, NULL))flag_message(brutus);

	}
}
	
// moves all mascots
void move_everyone(struct Sim *world)
{
	iterate(world->mascots, move_brutus);
}


