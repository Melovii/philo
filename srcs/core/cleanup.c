#include "philo.h"

// * Cleanup threads after simulation on error
int	cleanup_threads(t_round_table *table, int count)
{
	int i;

	// If simulation is already halted, no need to set it again
	if (!table->sim_halted)
	{
		pthread_mutex_lock(&table->death_lock);
		table->sim_halted = true;
		pthread_mutex_unlock(&table->death_lock);
	}

	// Join all threads that were created before the error (up until the i'th philosopher)
	i = 0;
	while (i < count)
	{
		if (pthread_join(table->philos[i].thread, NULL) != 0)
		{
			print_state(table, table->philos[i].id, STATE_ERROR);
			return 0;
		}
		i++;
	}
	return (1);
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

	// TODO: check if mutex_destroy returns an error
	// destroy control mutexes (print_lock, death_lock, meal_lock)
	pthread_mutex_destroy(&table->print_lock); // destroy print lock mutex
	pthread_mutex_destroy(&table->death_lock); // destroy death lock mutex
	pthread_mutex_destroy(&table->meal_lock); // destroy meal lock mutex

	// free allocated memory (arrays)
	free(table->philos); // free philosophers array
	free(table->forks); // free forks array
}
