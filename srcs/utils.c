#include "philo.h"

// Alloc forks, philos array, init mutexes
int 	init_round_table(t_round_table *table)
{
	int	i;

	table->end_simulation = false; // init simulation state
	
	table->philos = malloc(sizeof(t_philo) * table->num_philos); // allocate philosophers array
	if (!table->philos)
		return (0);
		
	table->forks = malloc(sizeof(t_mtx) * table->num_philos); // one mutex per fork
	if (!table->forks)
		return (0);

	// init fork mutexes
	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_init(&table->forks[i], NULL); // init each fork mutex
		i++;
	}
	
	pthread_mutex_init(&table->print_lock, NULL); // init print lock mutex
	pthread_mutex_init(&table->death_lock, NULL); // init death lock mutex
	pthread_mutex_init(&table->meal_lock, NULL); // init meal lock mutex
	return (1);
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
		table->philos[i].is_full = false; // init full state
		table->philos[i].table = table; // set reference back to the table
		i++;
	}
}

// Destroy mutexes, free arrays
void	cleanup_table(t_round_table *table)
{
	int	i;

	// destroy all forks (loop)
	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_destroy(&table->forks[i]); // destroy each fork mutex
		i++;
	}

	// destroy control mutexes (print_lock, death_lock, meal_lock)
	pthread_mutex_destroy(&table->print_lock); // destroy print lock mutex
	pthread_mutex_destroy(&table->death_lock); // destroy death lock mutex
	pthread_mutex_destroy(&table->meal_lock); // destroy meal lock mutex

	// free allocated memory (arrays)
	free(table->philos); // free philosophers array
	free(table->forks); // free forks array
}

// Lock print_lock, printf timestamp/id/state, unlock
void	print_state(t_round_table *table, int id, char *state)
{
	unsigned long	timestamp;
	
	timestamp = get_timestamp();
	pthread_mutex_lock(&table->print_lock); // lock print mutex
	printf("%lu %d %s\n", timestamp, id, state);
	pthread_mutex_unlock(&table->print_lock); // unlock print mutex
}
