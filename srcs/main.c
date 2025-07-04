#include "philo.h"

static void debug_print_table(t_round_table *table)
{
    printf("===== DEBUG: Round Table State =====\n");
    printf("Number of Philosophers: %d\n", table->num_philos);
    printf("Time to die (ms): %ld\n", table->time_to_die);
    printf("Time to eat (ms): %ld\n", table->time_to_eat);
    printf("Time to sleep (ms): %ld\n", table->time_to_sleep);
    printf("Must eat count: %d\n", table->must_eat_count);
    printf("Simulation halted flag: %d\n", table->sim_halted);
    printf("====================================\n");
}

int	main(int argc, char **argv)
{
	t_round_table	table;
	// t_philo			philos[MAX_PHILOS];
	// pthread_mutex_t	forks[MAX_PHILOS]; // one mutex per fork

	if (argc < MIN_ARGS || argc > MAX_ARGS)
	{
		printf(USAGE_MSG, argv[0]);
		return (0);
	}

	if (validate_args(argv))
		return (EX_KO);

	if (!parse_args(argc, argv, &table)) // Parse FIRST - sets table values
		return (EX_KO);

	if (!init_round_table(&table)) // Then initialize - uses table->num_philos
	{
		// consider freeing any allocated memory here
		return (EX_KO);
	}

	init_philosophers(&table); // set the IDs and fork pointers

	debug_print_table(&table); // debug print the table state

	// // launch and monitor the threads
	// create_threads(&table); // create philosopher threads
	// // cleanup after threads finish
	// cleanup_table(&table); // destroy mutexes, free arrays
	printf("Simulation finished successfully and no one has starved lol\n");
	return (0);
}
