#include "philo.h"

int	validate_args(char **argv)
{
	int	val;
	int	i;

	val = ft_atoi(arg_trim_r(argv[1]));
	i = 2;
	while (i <= 4)
	{
		val = ft_atoi(arg_trim_r(argv[i]));
		if (val <= 0)
			return (write(2, "Error: Invalid time argument.\n", 31));
		i++;
	}
	if (argv[5])
	{
		val = ft_atoi(arg_trim_r(argv[5]));
		if (val <= 0)
			return (write(2, "Error: Invalid must eat count argument.\n", 41));
	}
	return (0);
}

void	parse_args(int argc, char **argv, t_round_table *table)
{
	table->num_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == MAX_ARGS)
		table->must_eat_count = ft_atoi(argv[5]);
	else
		table->must_eat_count = -1;
}
