/* Neil Kirby */

void clear_a_list(void *avp, char *name);
void clear_lists(struct Sim *world);
void collect_coins(struct Sim *world);
void deal_with_input(unsigned short code, struct Sim *world);
int get_score(struct Buckeye *brutus);
bool my_coin(void *data, void *helper);
void run_sim(struct Sim *world);
void sweep(void *data);
