
/* Copyright 2023, Neil Kirby.  Not for disclosure without permission */
/* Edited by Elijah Paulman*/

// put system shared libraries first - they are unlikely to have bugs.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// put our own header files next.
// Start with one that are #define and structs
#include "structs.h"
#include "debug.h"

// includes for header files based on our own C code goes here.
// Always include the header for the file itself
// THis validates the header declarations against the defninitions.
// We are spoiled by our automatically generated headers, but we still
// validate them.  We put the include for this file dead last.
#include "output.h"
#include "bits.h"
#include "physics.h"
#include "sim.h"

#include "input.h"

#define ERR (-1)

// checks for valid input
bool valid_input(unsigned short code)
{
	if(is_coin(code))return valid_coin(code);
	if(is_brutus(code))return valid_brutus(code);
    if(TEXT)printf("ERROR: Don't know what %hx is, can't validate\n", code);
	return false;
}

// deals with input
bool good_input(FILE* file, struct Sim *world)
{
    int tokens;
    unsigned short code;

    // Use fscanf to read from the file
    while( 1 ==(tokens = fscanf(file, "%hx", &code )))
    {
        if(valid_input(code)) 
        {
            deal_with_input(code, world);
        }
        else
        {
            output_bad_bits(code);
            return(false);
        }
    }
    output_scanf(tokens);
    return( tokens == EOF);
}

/* the lab 4 bonus code will have more input routines. */

