/* Copyright 2024 Neil Kirby */
// Not for disclosure without permission

struct Sim
{
	void *mascots;
	void *coins;
	double elapsed;
};

struct Coin
{
	int color;
	double x_position, y_position;
};

struct Buckeye 
{
	int color, loot;
	double x_position, y_position, x_velocity, y_velocity, jump_velocity;
	struct Sim *world;
};

