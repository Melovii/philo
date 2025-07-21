#include "philo.h"

int	start_threads(t_round_table *table)
{
	int				i;
	unsigned long	start_time;

	i = 0;
	start_time = get_timestamp();
	table->start_time = start_time;
	while (i < table->num_philos)
	{
		table->philos[i].last_meal = start_time;
		i++;
	}
	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL, philo_routine,
				&table->philos[i]) != 0)
		{
			printf("Error: Failed to create philosopher thread %d\n", i + 1);
			cleanup_threads(table, i);
			return (0);
		}
		i++;
	}
	return (1);
}

static void	join_threads(t_round_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_join(table->philos[i].thread, NULL) != 0)
		{
			print_state(table, table->philos[i].id, STATE_ERROR);
			return ;
		}
		i++;
	}
}

void	run_sim(t_round_table *table)
{
	pthread_t	monitor_thread;

	if (!start_threads(table))
	{
		printf("Error: Failed to start threads\n");
		return ;
	}
	if (pthread_create(&monitor_thread, NULL, monitor, table) != 0)
	{
		printf("Error: Failed to create monitor thread\n");
		return ;
	}
	pthread_join(monitor_thread, NULL);
	join_threads(table);
}
