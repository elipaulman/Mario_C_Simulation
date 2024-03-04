
// Copyright 2024 Neil Kirby
// Not for distribution without permission
// Edited by Elijah Paulman

#include <stdbool.h>

#include "structs.h"

#include "sim.h"

// General home for list callback functions.  Two halves; coin related and
// brutus related.

// returns true alwasy
bool always_true(void *data, void *helper)
{
	// I don't care about parameters,
	return true;

}

//**************** brutus *************
bool brutus_score_order(void *data1, void * data2)
{
	struct Buckeye *b1 = data1, *b2 = data2;

	return( get_score(b1) > get_score(b2));
}


// sorts by y order
bool brutus_Y_order(void *data1, void * data2)
{
	struct Buckeye *b1 = data1, *b2 = data2;

	return( b1->y_position >= b2->y_position);
}



// ************** coin related ********
bool coin_color_order( void *data1, void * data2)
{
	struct Coin *c1 = data1, *c2 = data2;
	return (c1->color > c2->color);

}
