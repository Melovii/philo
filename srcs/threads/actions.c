#include "philo.h"

// * Picks up forks in a way that prevents deadlock and prevents circular wait
void	pick_up_forks(t_philo *philo)
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
		print_state(philo->table, philo->id, STATE_FORK);

		pthread_mutex_lock(philo->right_fork); // lock right fork
		print_state(philo->table, philo->id, STATE_FORK);
	}
	else // odd philosopher
	{
		pthread_mutex_lock(philo->right_fork); // lock right fork
		print_state(philo->table, philo->id, STATE_FORK);

		pthread_mutex_lock(philo->left_fork); // lock left fork
		print_state(philo->table, philo->id, STATE_FORK);
	}
}

// * Puts down forks after eating, unlocking them so other philosophers can use them
void	put_down_forks(t_philo *philo)
{
	// unlock the forks after eating

	pthread_mutex_unlock(philo->left_fork); // unlock left fork
	pthread_mutex_unlock(philo->right_fork); // unlock right fork
}

// * Simulates eating by updating last meal timestamp and meals eaten
void eat(t_philo *philo)
{
    print_state(philo->table, philo->id, STATE_EAT);

	// Simulate eating by delaying for the specified time
    delay(philo->table->time_to_eat);

	// Update last meal time and meals eaten count
    pthread_mutex_lock(&philo->table->meal_lock);
    philo->meals_eaten++;
    philo->last_meal = get_timestamp();

    pthread_mutex_unlock(&philo->table->meal_lock);
}


// * Simulates resting/sleeping by delaying for the specified time
void	rest(t_philo *philo)
{
	print_state(philo->table, philo->id, STATE_SLEEP);

	// delay for sleeping time
	delay(philo->table->time_to_sleep);
}

// * Simulates thinking to prevent starvation
void	think(t_philo *philo)
{
	print_state(philo->table, philo->id, STATE_THINK);
	usleep(100);
}
