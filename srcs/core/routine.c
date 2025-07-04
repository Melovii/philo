#include "philo.h"

// * Picks up forks in a way that prevents deadlock and prevents circular wait
static void	pick_up_forks(t_philo *philo)
{
	/*
		! To prevent deadlock:
			odd philosophers pick up right fork first,
			even philosophers pick up left fork first.
		
		This stops neighboring philosophers from trying to lock the same two forks
			in the same order at the same time, which would cause circular wait.
	*/
	
	if (philo->id % 2 == 0) // even philosopher
	{
		pthread_mutex_lock(philo->left_fork); // lock left fork
		pthread_mutex_lock(philo->right_fork); // lock right fork
	}
	else // odd philosopher
	{
		pthread_mutex_lock(philo->right_fork); // lock right fork
		pthread_mutex_lock(philo->left_fork); // lock left fork
	}
}

// * Puts down forks after eating, unlocking them so other philosophers can use them
static void	put_down_forks(t_philo *philo)
{
	// unlock the forks after eating

	pthread_mutex_unlock(philo->left_fork); // unlock left fork
	pthread_mutex_unlock(philo->right_fork); // unlock right fork
}

// * Simulates eating by updating last meal timestamp and meals eaten
static void	eat(t_philo *philo)
{
	// simulate eating
	(void)philo;
}

static void	rest(t_philo *philo)
{
	// simulate resting/sleeping
	(void)philo;
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
	// if (!philo)
		// return NULL; // handle error if philo is NULL
	table = philo->table; // get the reference to the round table
	
	// think
	while (!table->sim_halted)
	{
		// Check for death - all unsigned long arithmetic
		if (get_timestamp() - philo->last_meal > table->time_to_die)
		{
			print_state(table, philo->id, STATE_DEAD);
			table->sim_halted = true; // signal end of simulation
			return (NULL); // exit the thread
		}
		
		// pickup forks
		pick_up_forks(philo);
		
		// eat
		eat(philo);
		
		// put down forks
		put_down_forks(philo);
		
		// sleep
		rest(philo);
	}

	return (NULL); // exit the thread
}
