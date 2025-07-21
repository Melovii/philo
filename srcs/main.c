#include "philo.h"

int	main(int argc, char **argv)
{
	t_round_table	table;

	if (argc < MIN_ARGS || argc > MAX_ARGS)
	{
		printf("Usage: %s number_of_philosophers time_to_die "
			"time_to_eat time_to_sleep [must_eat]\n", argv[0]);
		return (0);
	}
	if (validate_args(argv))
		return (EX_KO);
	if (!parse_args(argc, argv, &table))
		return (EX_KO);
	if (!init_round_table(&table))
		return (EX_KO);
	init_philosophers(&table);
	run_sim(&table);
	cleanup_table(&table);
	return (0);
}
