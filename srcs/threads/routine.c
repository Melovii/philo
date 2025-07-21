#include "philo.h"

static void	perform_action_cycle(t_philo *philo)
{
	print_state(philo->table, philo->id, STATE_THINK);
	pick_up_forks(philo);
	eat(philo);
	put_down_forks(philo);
	rest(philo);
	think(philo);
}

void	*philo_routine(void *arg)
{
	t_round_table	*table;
	t_philo			*philo;

	philo = (t_philo *)arg;
	table = philo->table;
	if (table->num_philos == 1)
	{
		print_state(table, philo->id, STATE_FORK);
		delay(table->time_to_die);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		delay(10);
	while (1)
	{
		pthread_mutex_lock(&table->death_lock);
		if (table->sim_halted)
		{
			pthread_mutex_unlock(&table->death_lock);
			break ;
		}
		pthread_mutex_unlock(&table->death_lock);
		perform_action_cycle(philo);
	}
	return (NULL);
}
