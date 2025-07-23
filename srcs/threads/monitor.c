#include "philo.h"

// * Check if any philosopher has died
static int	death_check(t_round_table *table)
{
	int				i;
	unsigned long	now;
	unsigned long	time_since_meal;
	unsigned long	death_threshold;

	death_threshold = table->time_to_die;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_lock(&table->meal_lock);
		now = get_timestamp();
		time_since_meal = now - table->philos[i].last_meal;

		// Check if time since last meal exceeds the death threshold
		if (time_since_meal >= death_threshold)
		{
			print_state(table, table->philos[i].id, STATE_DEAD);
			pthread_mutex_unlock(&table->meal_lock);
			return (1);
		}
		pthread_mutex_unlock(&table->meal_lock);
		i++;
	}
	return (0);
}

// * Check if all philosophers have eaten the required number of meals
static int	full_check(t_round_table *table)
{
	int	i;

	// If must_eat_count is -1, it means no limit on meals
	if (table->must_eat_count == -1)
		return (0);

	i = 0;
	pthread_mutex_lock(&table->meal_lock);
	while (i < table->num_philos)
	{
		// Check if the philosopher has eaten less than the required meals
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

// * Check if the simulation should halt due to full condition
static int	halt_on_full(t_round_table *table)
{
	if (full_check(table))
	{
		pthread_mutex_lock(&table->death_lock);
		table->sim_halted = 1;
		pthread_mutex_unlock(&table->death_lock);
		return (1);
	}
	return (0);
}

// * Monitor thread function which constantly checks for death and full conditions
void	*monitor(void *data)
{
	t_round_table	*table;

	table = (t_round_table *)data;
	while (1)
	{
		// Check if any philosopher has died or if all have eaten enough
		if (death_check(table) || halt_on_full(table))
			break ;

		delay(1); // Sleep for a short duration to avoid busy-waiting
	}
	return (NULL);
}
