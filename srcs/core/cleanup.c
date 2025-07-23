#include "philo.h"

// * Gracefully halts the simulation and joins all running philosopher threads
void	cleanup_threads(t_round_table *table, int count)
{
	int	i;

	// Ensure simulation is marked as halted (thread-safe)
	if (!table->sim_halted)
	{
		pthread_mutex_lock(&table->death_lock);
		table->sim_halted = 1;
		pthread_mutex_unlock(&table->death_lock);
	}

	i = 0;
	// Join all philosopher threads up to given count
	while (i < count)
	{
		if (pthread_join(table->philos[i].thread, NULL) != 0)
			print_state(table, table->philos[i].id, STATE_ERROR); // Log join failure
		i++;
	}
}

// * Frees memory and destroys mutexes during failure or shutdown
int	cleanup_table(t_round_table *table, int fail_i, int fork_count)
{
	int	i;

	i = 0;
	// Destroy all initialized fork mutexes
	while (i < fork_count)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}

	// Destroy print_lock if initialized
	if (fail_i >= 0)
		pthread_mutex_destroy(&table->print_lock);

	// Destroy death_lock if initialized
	if (fail_i >= 1)
		pthread_mutex_destroy(&table->death_lock);

	// Destroy meal_lock if initialized
	if (fail_i >= 2)
		pthread_mutex_destroy(&table->meal_lock);

	// Free allocated resources
	free(table->forks);
	free(table->philos);

	return (0); // Indicate failure for the caller
}
