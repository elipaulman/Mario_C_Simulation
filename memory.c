
// COpyright 2024 Neil Kirby
// Not for distribution without permission

// list < > style headers first
#include <stdio.h>
#include <stdlib.h>

// includ3 constants and structs next
#include "debug.h"


// include our own file last
#include "memory.h"

void *allocate_struct(int size)
{
	static int objects = 0;
	void *ptr;

	if( ptr = malloc(size))
	{
	    objects++;
	    if(TEXT)
	    {
    printf("DIAGNOSTIC: allocation #%d allocated %d bytes\n", objects, size);
	    }

	}
	else
	{
	    if(TEXT)printf("ERROR: failed to allocate %d bytes.\n", size);
	}
	return ptr;

}

void free_struct(void *thing)
{
	static int count = 0;

	free(thing);
	count++;
	if(TEXT)printf("DIAGNOSTIC: %d objects freed\n", count);
}

