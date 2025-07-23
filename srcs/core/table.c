#include "philo.h"

// * Initializes the round table and its synchronization primitives
int	init_round_table(t_round_table *table)
{
	int	i;

	table->sim_halted = 0; // Initialize simulation state

	// Allocate memory for philosophers
	table->philos = malloc(sizeof(t_philo) * table->num_philos);
	if (!table->philos)
		return (0);

	// Allocate memory for forks (mutexes)
	table->forks = malloc(sizeof(t_mtx) * table->num_philos);
	if (!table->forks)
		return (free(table->philos), 0);

	i = 0;
	while (i < table->num_philos) // Initialize a mutex for each fork
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (cleanup_table(table, -1, i), 0);
		i++;
	}

	// Initialize mutex for synchronized printing
	if (pthread_mutex_init(&table->print_lock, NULL) != 0)
		return (cleanup_table(table, -1, i), 0);

	// Mutex to control simulation state and death check
	if (pthread_mutex_init(&table->death_lock, NULL) != 0)
		return (cleanup_table(table, 0, i), 0);

	// Mutex for tracking meals
	if (pthread_mutex_init(&table->meal_lock, NULL) != 0)
		return (cleanup_table(table, 1, i), 0);

	return (1);
}

// * Initializes the philosopher structures and links them to their forks
void	init_philosophers(t_round_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		table->philos[i].id = i + 1; // ID starts from 1
		table->philos[i].left_fork = &table->forks[i]; // Left fork is the current fork
		table->philos[i].right_fork = &table->forks[
			(i + 1) % table->num_philos]; // Circular reference for forks
		table->philos[i].last_meal = 0;
		table->philos[i].meals_eaten = 0;
		table->philos[i].table = table; // Reference to the round table
		i++;
	}
}

// * Prints the philosopher's state with timestamp, ensuring thread-safe output
void	print_state(t_round_table *table, int id, char *state)
{
	unsigned long	relative_time;

	pthread_mutex_lock(&table->death_lock);
	if (!table->sim_halted) // Only print if simulation is running
	{
		if (ft_strcmp(state, STATE_DEAD) == 0)
			table->sim_halted = 1; // Mark simulation as halted on death

		pthread_mutex_lock(&table->print_lock);
		relative_time = get_timestamp() - table->start_time;
		printf("%lu %d %s\n", relative_time, id, state);
		pthread_mutex_unlock(&table->print_lock);
	}
	pthread_mutex_unlock(&table->death_lock);
}
