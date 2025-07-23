#include "philo.h"

// * Handles the cycle of actions for a philosopher
static void	perform_action_cycle(t_philo *philo)
{
	think(philo);
	pick_up_forks(philo);
	eat(philo);
	put_down_forks(philo);
	rest(philo);
}

// * The main routine for each philosopher thread
void	*philo_routine(void *arg)
{
	t_round_table	*table;
	t_philo			*philo;

	// Cast the argument to the correct type
	philo = (t_philo *)arg;
	table = philo->table;

	// One philosopher, one fork -> leads to starvation
	if (table->num_philos == 1)
	{
		print_state(table, philo->id, STATE_FORK);
		delay(table->time_to_die);
		return (NULL);
	}

	// Delay to stagger even philosophers (to avoid deadlock)
	if (philo->id % 2 == 0)
		delay(10);

	// Main loop for the philosopher's routine
	while (1)
	{
		pthread_mutex_lock(&table->death_lock);
		if (table->sim_halted) // Checks if simulation is halted within a mutex lock
		{
			pthread_mutex_unlock(&table->death_lock);
			break ;
		}
		pthread_mutex_unlock(&table->death_lock);

		perform_action_cycle(philo); // Perform the cycle of actions
	}
	return (NULL);
}
