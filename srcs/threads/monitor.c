#include "philo.h"

static int	full_check(t_round_table *table)
{
	int	i;

	if (table->must_eat_count == -1)
		return (0);
	i = 0;
	pthread_mutex_lock(&table->meal_lock);
	while (i < table->num_philos)
	{
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

static int	death_check(t_round_table *table)
{
	int				i;
	unsigned long	now;
	unsigned long	time_since_meal;
	unsigned long	death_threshold;

	death_threshold = table->time_to_die + 1;
	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_lock(&table->meal_lock);
		now = get_timestamp();
		time_since_meal = now - table->philos[i].last_meal;
		if (time_since_meal >= death_threshold)
		{
			print_state(table, table->philos[i].id, STATE_DEAD);
			pthread_mutex_lock(&table->death_lock);
			table->sim_halted = 1;
			pthread_mutex_unlock(&table->death_lock);
			pthread_mutex_unlock(&table->meal_lock);
			return (1);
		}
		pthread_mutex_unlock(&table->meal_lock);
		i++;
	}
	return (0);
}

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

void	*monitor(void *data)
{
	t_round_table	*table;

	table = (t_round_table *)data;
	while (1)
	{
		if (death_check(table) || halt_on_full(table))
			break ;
		delay(1);
	}
	return (NULL);
}
