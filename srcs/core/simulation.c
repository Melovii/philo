#include "philo.h"

// * Thread startup/shutdown
int	start_threads(t_round_table *table)
{
	int				i;
	unsigned long	start_time;

	start_time = get_timestamp(); // Get simulation start time
	table->start_time = start_time; // Store in table for relative timestamps
	
	// Set initial meal time for all philosophers to prevent immediate death
	i = 0;
	while (i < table->num_philos)
	{
		table->philos[i].last_meal = start_time;
		i++;
	}

	i = 0;
	while (i < table->num_philos)
	{
		// stores thread ID, and passes routine to each philosopher
		if (pthread_create(&table->philos[i].thread, NULL, philo_routine, &table->philos[i]) != 0)
			return (0); // TODO: handle error
		
		// Small delay to stagger thread startup and prevent perfect synchronization
		usleep(500); // 0.5ms delay between thread creation
		i++;
	}
	return (1);
}

// * Wait for all philosopher threads to finish
static void	join_threads(t_round_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		// Wait for each philosopher thread to finish
		if (pthread_join(table->philos[i].thread, NULL) != 0)
		{
			print_state(table, table->philos[i].id, STATE_ERROR);
			return;
		}
		i++;
	}
}

// * Run the simulation: start threads, monitor, and join
void	run_sim(t_round_table *table)
{
	pthread_t	monitor_thread;

	if (!start_threads(table))
	{
		printf("Error: Failed to start threads\n");
		return;
	}
	if (pthread_create(&monitor_thread, NULL, monitor, table) != 0)
	{
		printf("Error: Failed to create monitor thread\n");
		return;
	}
	pthread_join(monitor_thread, NULL);
	join_threads(table);
}
