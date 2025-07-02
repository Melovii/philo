#include "philo.h"

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

	if (!parse_args(argc, argv, &table))
		return (EX_KO);

	if (!init_round_table(&table)) // allocate forks, philosophers array, init mutexes
		return (EX_KO);

	init_philosophers(&table); // set the IDs and fork pointers

	// // launch and monitor the threads
	// create_threads(&table); // create philosopher threads
	// // cleanup after threads finish
	// cleanup_table(&table); // destroy mutexes, free arrays
	return (0);
}
