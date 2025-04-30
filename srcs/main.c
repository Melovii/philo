#include "philo.h"

int	main(int argc, char **argv)
{
	// t_table	table;

	if (argc < MIN_ARGS || argc > MAX_ARGS)
	{
		printf(USAGE_MSG, argv[0]);
		return (EX_KO);
	}

	// if (!parse_args(argc, argv, &table))
	// {
    //     printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [must_eat]\n", argv[0]); // TODO: define a msg in header
	// 	return (EX_KO); // 1 // TODO: Define this in header
	// }
	// if (!init_table(&table))
	// 	return (EX_KO);

	// // launch and monitor the threads
	// cleanup_table(&table);
	return (0);
}
