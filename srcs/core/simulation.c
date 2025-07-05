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

// * Check if all philosophers have eaten enough times
static int	full_check(t_round_table *table)
{
	int	i;

	if (table->must_eat_count == -1)
		return (0);
	i = 0;
	pthread_mutex_lock(&table->meal_lock);
	while (i < table->num_philos)
	{
		// If any philosopher has not eaten enough times, return false
		if (table->must_eat_count != -1
			&& table->philos[i].meals_eaten < table->must_eat_count)
		{
			pthread_mutex_unlock(&table->meal_lock);
			return (0);
		}
		i++;
	}
	pthread_mutex_unlock(&table->meal_lock);
	return (1);
}

// * Monitor simulation until death or completion
static void	*monitor(void *data)
{
	t_round_table	*table;
	int				i;

	table = (t_round_table *)data;
	while (1)
	{
		i = 0;
		while (i < table->num_philos)
		{
			pthread_mutex_lock(&table->meal_lock);
			if (get_timestamp() - table->philos[i].last_meal > table->time_to_die)
			{
				print_state(table, table->philos[i].id, STATE_DEAD);
				pthread_mutex_lock(&table->death_lock);
				table->sim_halted = true;
				pthread_mutex_unlock(&table->death_lock);
				pthread_mutex_unlock(&table->meal_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&table->meal_lock);
			i++;
		}
		if (full_check(table))
		{
			pthread_mutex_lock(&table->death_lock);
			table->sim_halted = true;
			pthread_mutex_unlock(&table->death_lock);
			return (NULL);
		}
		delay(1);
	}
	return (NULL);
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
