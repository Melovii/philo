#include "philo.h"

// * Starts philosopher threads and initializes their last meal time
int	start_threads(t_round_table *table)
{
	int				i;
	unsigned long	start_time;

	i = 0;
	start_time = get_timestamp();          // Get the current timestamp
	table->start_time = start_time;        // Set simulation start time

	// Initialize last_meal time for each philosopher
	while (i < table->num_philos)
	{
		table->philos[i].last_meal = start_time;
		i++;
	}

	i = 0;
	// Create a thread for each philosopher
	while (i < table->num_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL, philo_routine,
				&table->philos[i]) != 0)
		{
			printf("Error: Failed to create philosopher thread %d\n", i + 1);
			cleanup_threads(table, i); // Cleanup previously created threads
			return (0);
		}
		i++;
	}
	return (1); // All threads created successfully
}

// * Runs the simulation by starting philosopher and monitor threads
void	run_sim(t_round_table *table)
{
	pthread_t	monitor_thread;

	if (!start_threads(table)) // Start philosopher threads
	{
		printf("Error: Failed to start threads\n");
		return ;
	}

	// Create the monitor thread to observe simulation state
	if (pthread_create(&monitor_thread, NULL, monitor, table) != 0)
	{
		printf("Error: Failed to create monitor thread\n");
		cleanup_threads(table, table->num_philos); // Cleanup all philosopher threads
		return ;
	}

	// Wait for monitor thread to finish
	if (pthread_join(monitor_thread, NULL) != 0)
		printf("Error: Failed to join monitor thread\n");

	// Cleanup all philosopher threads after simulation ends
	cleanup_threads(table, table->num_philos);
}
