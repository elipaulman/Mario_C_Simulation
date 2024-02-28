/* Copyright 2023 Neil Kirby, all rights reserved. */
/* Do not publish this code without written permission */
#include <stdbool.h>
/* Neil Kirby */

double btp_X_adjustment(double X, double Y);
double btp_Y_adjustment(double X, double Y);
void btp_beep();
int btp_brutus(int score, int color, double X, double Y, bool faces_right);
void btp_clear();
int btp_coin(int color, double X, double Y);
void btp_flash();
int btp_getch();
int btp_initialize(int debug);
void btp_refresh();
void btp_status(const char *statstr);
void btp_teardown();
void btp_time(int milliseconds);
