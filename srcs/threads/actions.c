#include "philo.h"

void	pick_up_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo->table, philo->id, STATE_FORK);
		pthread_mutex_lock(philo->right_fork);
		print_state(philo->table, philo->id, STATE_FORK);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_state(philo->table, philo->id, STATE_FORK);
		pthread_mutex_lock(philo->left_fork);
		print_state(philo->table, philo->id, STATE_FORK);
	}
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	eat(t_philo *philo)
{
	print_state(philo->table, philo->id, STATE_EAT);
	delay(philo->table->time_to_eat);
	pthread_mutex_lock(&philo->table->meal_lock);
	philo->meals_eaten++;
	philo->last_meal = get_timestamp();
	pthread_mutex_unlock(&philo->table->meal_lock);
}

void	rest(t_philo *philo)
{
	print_state(philo->table, philo->id, STATE_SLEEP);
	delay(philo->table->time_to_sleep);
}

// * Simulates thinking to prevent starvation
void	think(t_philo *philo)
{
	print_state(philo->table, philo->id, STATE_THINK);
	usleep(100);
}
