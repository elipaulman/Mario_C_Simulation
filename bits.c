

/* Copyright 2024, Neil Kirby.  Not for disclosure without permission */

// put system shared libraries first - they are unlikely to have bugs.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "debug.h"

// includes for header files based on our own C code goes here.
// Always include the header for the file itself
// THis validates the header declarations against the defninitions.
// We are spoiled by our automatically generated headers, but we still
// validate them.  We put the include for this file dead last.
#include "bits.h"



unsigned int get_color(unsigned short code)
{
	return ( code >> 12 & 0x7);
}

unsigned int get_jump_V(unsigned short code)
{
	return ( (code >> 8) & 0xF);
}

unsigned int get_VX(unsigned short code)
{
	return ( (code >> 4) & 0xF);
}

unsigned int get_coin_X(unsigned short code)
{
	return ( (code >> 8) & 0xF);
}

unsigned int get_coin_Y(unsigned short code)
{
	return ( (code >> 4) & 0xF);
}

bool is_brutus(unsigned short code)
{
	return ( code & 1);
}

bool is_coin(unsigned short code)
{
	return !( code & 1);
}

static bool good_parity(unsigned short code)
{

	// add the checksum/parity code here
	unsigned short x = 0;
	// depend on it being unsigned so we shift in 0 on the left end
	if(DEBUG)printf("    validating parity...\n");

	while(code)
	{
	     x = x ^ (code & 1);
	     code = code >> 1;
	}

	if(DEBUG)printf("    all done: parity wanted 0 got %d\n",x);
	return x ==0;
}

bool valid_coin(unsigned short code)
{
	if(DEBUG)printf("valid coin:\n    validating color...\n");
	if(get_color(code) == 0) return false;

	return good_parity(code);
}

bool valid_brutus(unsigned short code)
{
	if(DEBUG)printf("valid brutus:\n    validating color...\n");
	if(get_color(code) == 0) return false;

	if(DEBUG)printf("    validating jump V...\n");
	if(get_jump_V(code) == 0) return false;

	if(DEBUG)printf("    validating VX...\n");
	if(get_VX(code) == 0) return false;

	return good_parity(code);
}


