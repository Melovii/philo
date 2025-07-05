#include "philo.h"

int	main(int argc, char **argv)
{
	t_round_table	table;

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

	// Launch and monitor the simulation
	run_sim(&table);

	// Cleanup after threads finish
	cleanup_table(&table); // destroy mutexes, free arrays
	
	return (0);
}
