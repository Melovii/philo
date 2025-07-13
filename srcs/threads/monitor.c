#include "philo.h"

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

// * Check if a philosopher has died with timing tolerance
static int	death_check(t_round_table *table)
{
	int				i;
	unsigned long	now;
	unsigned long	time_since_meal;
	unsigned long	death_threshold;

	i = 0;
	// Add small tolerance (1ms) to account for timing variations
	death_threshold = table->time_to_die + 1;

	while (i < table->num_philos)
	{
		pthread_mutex_lock(&table->meal_lock);
		now = get_timestamp(); // ! moved here for accuracy

		// Calculate time since last meal
		time_since_meal = now - table->philos[i].last_meal;
		
		// printf("[DEBUG] Philosopher %d: last meal at %lu ms, now at %lu ms, time_since_meal = %lu ms\n",
			// table->philos[i].id, table->philos[i].last_meal, now, time_since_meal);
			
		if (time_since_meal >= death_threshold)
		{
			// printf("[DEBUG] Philosopher %d died! time_since_meal=%lu >= %lu\n",
			// 	table->philos[i].id, time_since_meal, death_threshold);

			print_state(table, table->philos[i].id, STATE_DEAD);
			pthread_mutex_lock(&table->death_lock);
			table->sim_halted = true;
			pthread_mutex_unlock(&table->death_lock);
			pthread_mutex_unlock(&table->meal_lock);
			return (1);
		}
		pthread_mutex_unlock(&table->meal_lock);
		i++;
	}
	return (0);
}

// * Check if all philosophers are full and halt simulation
static int	halt_on_full(t_round_table *table)
{
	if (full_check(table))
	{
		pthread_mutex_lock(&table->death_lock);
		table->sim_halted = true;
		pthread_mutex_unlock(&table->death_lock);
		return (1);
	}
	return (0);
}

// * Monitor simulation until death or completion
void	*monitor(void *data)
{
	t_round_table	*table;

	table = (t_round_table *)data;
	while (1)
	{
		if (death_check(table) || halt_on_full(table))
			break;
		delay(1); // TODO: Consider changing to this
		// usleep(500);
	}
	return (NULL);
}
