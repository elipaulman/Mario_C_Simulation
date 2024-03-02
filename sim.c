// Copyright 2024 Neil Kirby
/* Edited by Elijah Paulman */
// Not for distribution without permission

// list < > style headers first
#include <stdio.h>
#include <stdlib.h>

// includ3 constants and structs next
#include "structs.h"
#include "constants.h"
#include "debug.h"

// library headers that don't have bugs
#include "btp.h"
#include "libll.h"

// include function declarations after that
#include "n2.h"

#include "bits.h"
#include "callbacks.h"
#include "output.h"
#include "physics.h"
#include "memory.h"

// include our own file last
#include "sim.h"

// returns true if coin color matches mascot color
bool my_coin(void *data, void *helper)
{
	struct Coin *cp = data;
	struct Buckeye *brutus = helper;

	return( (brutus->color == cp->color) && 
		(close_enough(brutus->x_position, brutus->y_position,
				cp->x_position, cp->y_position)
		)
	    );

}

// sweeps coins
void sweep(void *data)
{
	struct Buckeye *brutus = data;
	int winnings;

	winnings = deleteSome(&brutus->world->coins, my_coin, brutus, 
			free_struct, TEXT);
	if(winnings > 0)
	{
	    brutus->loot += winnings;
	    loot_message(brutus);
	}
}

// collects coins
void collect_coins(struct Sim *world)
{
	iterate(world->mascots, sweep);
}

// gets score for mascot
int get_score(struct Buckeye *brutus)
{
	int score = brutus->loot;
	if(is_left_of_flag(brutus, NULL))
	{
	    score += (int) brutus->x_position;
	}
	else
	{
	    score += (int)  (brutus->x_position + brutus->y_position);
	}
	return score;
}

// keeps game on if any mascot left of flag
static bool game_on(struct Sim *world)
{
	return( any(world->mascots, is_left_of_flag, NULL));
}

// clears a list
void clear_a_list(void *avp, char *name)
{
	int d = 0;
	// output belongs in output.c
	if(TEXT)printf("Clearing %s list...\n", name);
	d = deleteSome(avp, always_true, NULL, free_struct, TEXT);
	if(TEXT)printf("     %d %s deleted.\n", d, name);
}

// clears masscot and coins list
void clear_lists(struct Sim *world)
{
	clear_a_list(&world->mascots, "mascots");
	clear_a_list(&world->coins, "coins");
}

// runs simulation
void run_sim(struct Sim *world)
{
	while(game_on(world))
	{
	    sort(world->mascots, brutus_Y_order);
	    master_output(world);

	    world->elapsed += DELTA_TIME;
	    move_everyone(world);
	    collect_coins(world);
	}
	sort(world->mascots, brutus_score_order);
	final_output(world);
	clear_lists(world);
}

// fills coin list
static void fill_coin(unsigned short code, struct Coin *cash)
{
	cash->x_position = 0.5 + get_coin_X(code);
	cash->y_position = 0.5 + get_coin_Y(code);
	cash->color = get_color(code);
}

// fills brutus list
static void fill_brutus(struct Sim *world, unsigned short code, struct Buckeye *brutus)
{
	// start at (0.5, 0.5)
	brutus->x_position = 0.5;
	brutus->y_position = 0.5;
	brutus->x_velocity = get_VX(code);
	// we aren't falling at the moment
	brutus->y_velocity = 0.0;
	brutus->jump_velocity = get_jump_V(code);
	brutus->color = get_color(code);
	brutus->world = world;
}

// deals with coin 
static void deal_with_coin(unsigned short code, struct Sim *world)
{
	struct Coin *cash;

	if( cash = allocate_struct(sizeof(struct Coin)))
	{
	    fill_coin(code, cash);
	    if(!insert(&world->coins, cash, coin_color_order, TEXT))
	    {
	    	// I need to free that 
	    }
	}

}

// deals with brutus
static void deal_with_brutus(unsigned short code, struct Sim *world)
{
	struct Buckeye *brutus;

	if( brutus = allocate_struct(sizeof(struct Buckeye)))
	{
	    fill_brutus(world, code, brutus);
	    if(!insert(&world->mascots, brutus, brutus_Y_order, TEXT))
	    {
	    	// I need to free that 
	    }
	}

}

// deals with input
void deal_with_input(unsigned short code, struct Sim *world)
{
	if(is_coin(code)) deal_with_coin(code, world);
	if(is_brutus(code)) deal_with_brutus(code, world);
}



