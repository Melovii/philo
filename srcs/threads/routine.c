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

/*
* Takes void *arg because pthread_create expects a function with this signature
* Function that runs in each philosopher thread and checks for death
* (think -> pickup -> eat -> putdown -> sleep cycle)
*/
void	*philo_routine(void *arg)
{
	t_round_table	*table;
	t_philo			*philo;

	philo = (t_philo *)arg; // cast the argument to t_philo pointer
	table = philo->table; // get the reference to the round table
	if (table->num_philos == 1)
	{
		print_state(table, philo->id, STATE_FORK);
		delay(table->time_to_die);
		return (NULL);
	}
	if (philo->id % 2 == 0)
	{
		// delay(table->time_to_eat); // TODO: Consider changing it to this	
		delay(10); // ! added to stagger even philosophers
	}

	// think
	while (1)
	{
		pthread_mutex_lock(&table->death_lock);
		if (table->sim_halted)
		{
			pthread_mutex_unlock(&table->death_lock);
			break;
		}
		pthread_mutex_unlock(&table->death_lock);
		perform_action_cycle(philo);
	}

	return (NULL); // exit the thread
}
