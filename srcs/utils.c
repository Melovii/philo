#include "philo.h"

// parse_args: read & validate argv into table
int 	parse_args(int argc, char **argv, t_round_table *table);

// init_round_table: alloc forks, philos array, init mutexes
int 	init_round_table(t_round_table *table);

// cleanup_table: destroy mutexes, free arrays
void	cleanup_table(t_round_table *table);

// get_timestamp: return current time in ms
long	get_timestamp(void);

// print_state: lock print_lock, printf timestamp/id/state, unlock
void	print_state(t_round_table *table, int id, char *state);
