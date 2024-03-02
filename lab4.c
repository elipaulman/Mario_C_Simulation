// COpyright 2024 Neil Kirby
// Not for distribution without permission

// list < > style headers first
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// includ3 constants and structs next
#include "structs.h"
#include "constants.h"
#include "debug.h"

// library headers that don't have bugs
#include "btp.h"

// include function declarations after that
#include "n2.h"

#include "bits.h"
#include "input.h"
#include "output.h"
#include "sim.h"

// include our own file last
#include "lab4.h"



#define RVAL_BAD_INIT (1)
#define RVAL_BAD_INPUT (2)
#define RVAL_BAD_ARGS (3)


/* I own all inits.  In future labs, I might morph to master init and call
 * my init minions to do the various subtasks.  For now, I'm simple enough
 * to do it all easily myself.  I shield main for all details about
 * initializations */
bool init()
{
	/* we might take manual control over what we feed btp_init
	 * SO that we turn it off but still debug our code. */
	return(TEXT || ( GRAPHICS && btp_initialize(false)));

}

/* Put all of the toys away.  In future labs I will own more stuff and
 * call my minions to do those things. */
void teardown()
{
	if(GRAPHICS)btp_teardown();
}

// handles arg checks
bool handle_args(int argc, char *argv[], bool *bonus)
{
    if(argc < 2) 
    {
        printf("ERROR: insufficient args - no filename given\n");
        return false;
    }

    if(argc == 3) 
    {
        if(TEXT)
        {
            printf("ERROR: Bonus code is not present.\n");
            return false;
        }
        if(strcmp(argv[2], "bonus") == 0)
        {
            *bonus = true;
        }
        else 
        {
            printf("ERROR: Invalid argument '%s'.\n", argv[2]);
            return false;
        }
    }

    return true;
}

// handles file
bool handle_file(char *filename, struct Sim *world)
{
    FILE *file = fopen(filename, "r");
    if(file == NULL) 
    {
        printf("ERROR: Unable to open %s for reading.\n", filename);
        return false;
    }

    if(TEXT) printf("DIAGNOSTIC: Successfully opened %s for reading.\n", filename);

    unsigned short code;
    while(fscanf(file, "%hx", &code) == 1)
    {
        if(valid_input(code) == false)
        {
            output_bad_bits(code);
            fclose(file);
            if(TEXT) printf("DIAGNOSTIC: Input file closed.\n");
            return false;
        }
        deal_with_input(code, world);
    }

    fclose(file);
    if(TEXT) printf("DIAGNOSTIC: Input file closed.\n");

    return true;
}


/* Avoid details and call upon my minions to make it everything happen.  I own
 * those highest level things that I must own: performance timing and the
 * value we return to linux */
int main(int argc, char *argv[])
{
	int rval = EXIT_SUCCESS;
	double start, runtime;
	bool bonus = false;

	start = now();	// this is the very first executable statement

	if(!handle_args(argc, argv, &bonus))  
    {
        return RVAL_BAD_ARGS;
    }
	if( init())
	{
	    struct Sim ohio = {NULL, NULL, 0.0}, *world = &ohio;

		if(!handle_file(argv[1], world) || !good_input(world))         
		{
            rval = RVAL_BAD_INPUT;
        }
        else 
        {
            run_sim(world);
        }

	    teardown();
	}
	else
	{
	    rval = RVAL_BAD_INIT;	// non zero, indicates an error
	}
	
	/* at this point we are done, graphics has been torn down*/
	printf("Returning %d\n", rval);
	runtime = now() - start;
	/* after graphics has been torn down, we can freely print */
	printf("Total runtime is %.9lf seconds\n", runtime);

	return rval;
}

