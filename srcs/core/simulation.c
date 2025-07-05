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
	// I should maybe check all philos simultaneously for meals_eaten flag? (must_eat_count)
	// dunno
	return (1);
}

// * Check if all philosophers have eaten enough times
static int	full_check(t_round_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		// If any philosopher has not eaten enough times, return false
		if (table->philos[i].meals_eaten < table->must_eat_count)
			return (0);
		i++;
	}
	return (1);
}

// * Monitor simulation until death or completion
static void	monitor(t_round_table *table)
{
	int				i;
	unsigned long	current_time;

	while (!table->sim_halted)
	{
		// Check each philosopher for death
		i = 0;
		while (i < table->num_philos)
		{
			pthread_mutex_lock(&table->meal_lock); // Protect last_meal access
			current_time = get_timestamp();
			
			// Check if this philosopher has died
			if (current_time - table->philos[i].last_meal > table->time_to_die)
			{
				pthread_mutex_unlock(&table->meal_lock);
				print_state(table, table->philos[i].id, STATE_DEAD);
				table->sim_halted = true;
				return;
			}
			pthread_mutex_unlock(&table->meal_lock);
			i++;
		}
		
		// Only check for meal completion if must_eat_count is specified (not -1)
		if (table->must_eat_count != -1 && full_check(table))
		{
			// If all philosophers have eaten enough, signal completion
			table->sim_halted = true;
			break;
		}
		
		delay(1); // Check very frequently for death detection (1ms)
	}
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
	if (!start_threads(table))
	{
		printf("Error: Failed to start threads\n");
		return;
	}
	monitor(table);
	join_threads(table);
}
