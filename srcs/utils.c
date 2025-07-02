#include "philo.h"

// Alloc forks, philos array, init mutexes
void 	init_round_table(t_round_table *table)
{
	(void)table;
}

// Set philosopher IDs, fork pointers, last meal, meals eaten
void	init_philosophers(t_round_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		table->philos[i].id = i + 1; // IDs start from 1 lol
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[(i + 1) % table->num_philos]; // % to wrap around the array
		table->philos[i].last_meal = 0; // init last meal timestamp
		table->philos[i].meals_eaten = 0; // init meals eaten
		table->philos[i].table = table; // set reference back to the table
		i++;
	}
	// init print lock mutex?
	// init forks mutexes?
}

// Destroy mutexes, free arrays
void	cleanup_table(t_round_table *table);

// Return current time in ms
long	get_timestamp(void);

// Lock print_lock, printf timestamp/id/state, unlock
void	print_state(t_round_table *table, int id, char *state);
