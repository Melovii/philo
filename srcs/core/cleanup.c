#include "philo.h"

int	cleanup_threads(t_round_table *table, int count)
{
	int	i;

	if (!table->sim_halted)
	{
		pthread_mutex_lock(&table->death_lock);
		table->sim_halted = 1;
		pthread_mutex_unlock(&table->death_lock);
	}
	i = 0;
	while (i < count)
	{
		if (pthread_join(table->philos[i].thread, NULL) != 0)
		{
			print_state(table, table->philos[i].id, STATE_ERROR);
			return (0);
		}
		i++;
	}
	return (1);
}

void	cleanup_table(t_round_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->death_lock);
	pthread_mutex_destroy(&table->meal_lock);
	free(table->philos);
	free(table->forks);
}
