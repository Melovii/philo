#include "philo.h"

// * Pick up forks in a specific order based on philosopher ID parity
void	pick_up_forks(t_philo *philo)
{
	// Even ID: lock left fork first, then right
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo->table, philo->id, STATE_FORK);
		pthread_mutex_lock(philo->right_fork);
		print_state(philo->table, philo->id, STATE_FORK);
	}
	// Odd ID: lock right fork first, then left
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_state(philo->table, philo->id, STATE_FORK);
		pthread_mutex_lock(philo->left_fork);
		print_state(philo->table, philo->id, STATE_FORK);
	}
}

// * Release forks after eating
void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

// * Eating action
void	eat(t_philo *philo)
{
	print_state(philo->table, philo->id, STATE_EAT);

	delay(philo->table->time_to_eat);

	pthread_mutex_lock(&philo->table->meal_lock);
	philo->meals_eaten++;
	philo->last_meal = get_timestamp();
	pthread_mutex_unlock(&philo->table->meal_lock);
}

// * Resting action
void	rest(t_philo *philo)
{
	print_state(philo->table, philo->id, STATE_SLEEP);
	delay(philo->table->time_to_sleep);
}

// * Thinking action
void	think(t_philo *philo)
{
	print_state(philo->table, philo->id, STATE_THINK);
	usleep(100);
}
