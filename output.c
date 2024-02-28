// Copyright 2024 Neil Kirby
// Not for distribution without permission

// Include < > style headers first:
#include <stdio.h>

// include debug, subscripts, etc before functions
#include "debug.h"
#include "btp.h"
#include "structs.h"
#include "constants.h"
#include "libll.h"

// include any function headers now, other than our own.
#include "n2.h"

#include "sim.h"
#include "callbacks.h"

// include the header file for this file as the very last include
#include "output.h"



static void draw_coin(void * data)
{
	struct Coin *cash = data;
	btp_coin( cash->color, cash->x_position, cash->y_position);
}

static void draw_brutus(void * data)
{
	struct Buckeye *brutus = data;
	btp_brutus( get_score(brutus), brutus->color, 
		brutus->x_position, brutus->y_position, true);
}

static void master_draw(struct Sim *world)
{


	btp_clear();
	btp_time( (int) (1000 * world->elapsed));

	iterate(world->mascots, draw_brutus);
	iterate(world->coins, draw_coin);

	btp_refresh();
	microsleep( (unsigned int) (DELTA_TIME * 1000000));
}

static void print_coin (void * data)
{
	struct Coin *cash = data;

	printf("%d    (%8.5lf, %8.5lf)\n",
	    cash->color, cash->x_position, cash->y_position);

}

static void print_brutus (void * data)
{
	struct Buckeye *brutus = data;

	printf("%3d    %d    (%8.5lf, %8.5lf)    (%9.5lf, %9.5lf)\n",
	    get_score(brutus), brutus->color, 
	    brutus->x_position,
	    brutus->y_position,
	    brutus->x_velocity,
	    brutus->y_velocity);

}

static void master_print(struct Sim *world)
{
	// do the header, then brutus
	
printf(
    "\nPts    C    (__X_____, __Y_____)    (__VX_____, __VY_____) ET=%8.5lf\n",
    world->elapsed);
    	iterate(world->mascots, print_brutus);
	printf( "\nC    (__X_____, __Y_____)\n" );
	iterate(world->coins, print_coin);
}

static void final_draw (struct Sim *world)
{
	double delay = 0.0;
	while (delay < 4.0)
	{
	    master_draw(world);
	    delay += DELTA_TIME;
	}
}
	
void final_output(struct Sim *world)
{
	if(GRAPHICS)
	{
	    final_draw(world);
	}
	if(TEXT)
	{
	    master_print(world);
	}
}

void master_output(struct Sim *world)
{
	if(GRAPHICS)master_draw(world);
	if(TEXT)master_print(world);
}

// messages
void flag_message(struct Buckeye *brutus)
{
	if(GRAPHICS)
	{
	    btp_status("Brutus makes it to the flag");
	}
	if(TEXT)
	{
	    printf("\nBrutus makes it to the flag!\n");
	}
}
void loot_message(struct Buckeye *brutus)
{
	if(TEXT)printf("Brutus finds loot at %8.5lf, %8.5lf\n",
		brutus->x_position, brutus->y_position);
	if(GRAPHICS)btp_status("Brutus finds some loot");
}

void ceiling_message(struct Buckeye *brutus)
{
	if(TEXT)printf("Brutus hits the ceiling at %8.5lf, %8.5lf\n",
		brutus->x_position, brutus->y_position);
	if(GRAPHICS)btp_status("Brutus hits the ceiling");

}

void floor_message(struct Buckeye *brutus)
{
	if(TEXT)printf("Brutus hits the floor at %8.5lf, %8.5lf\n",
		brutus->x_position, brutus->y_position);
	if(GRAPHICS)btp_status("Brutus hits the floor");

}

void jump_message(struct Buckeye *brutus)
{
	if(TEXT)printf("Brutus jumps at %8.5lf, %8.5lf\n",
		brutus->x_position, brutus->y_position);
	if(GRAPHICS)btp_status("Brutus jumps");

}


void output_bad_bits(unsigned short code)
{
	if(TEXT)printf("ERROR: invalid input: hex %X\n", code);
}

void output_scanf(int tokens)
{
	if(TEXT)printf("scanf returned %d\n", tokens);
}


