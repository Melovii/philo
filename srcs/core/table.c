#include "philo.h"

int	init_round_table(t_round_table *table)
{
	int	i;

	table->sim_halted = 0;
	table->philos = malloc(sizeof(t_philo) * table->num_philos);
	if (!table->philos)
		return (0);
	table->forks = malloc(sizeof(t_mtx) * table->num_philos);
	if (!table->forks)
	{
		free(table->philos);
		return (0);
	}
	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&table->print_lock, NULL);
	pthread_mutex_init(&table->death_lock, NULL);
	pthread_mutex_init(&table->meal_lock, NULL);
	return (1);
}

void	init_philosophers(t_round_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[
			(i + 1) % table->num_philos];
		table->philos[i].last_meal = 0;
		table->philos[i].meals_eaten = 0;
		table->philos[i].table = table;
		i++;
	}
}

void	print_state(t_round_table *table, int id, char *state)
{
	unsigned long	relative_time;

	pthread_mutex_lock(&table->death_lock);
	if (!table->sim_halted)
	{
		if (ft_strcmp(state, STATE_DEAD) == 0)
			table->sim_halted = 1;
		pthread_mutex_lock(&table->print_lock);
		relative_time = get_timestamp() - table->start_time;
		printf("%lu %d %s\n", relative_time, id, state);
		pthread_mutex_unlock(&table->print_lock);
	}
	pthread_mutex_unlock(&table->death_lock);
}
