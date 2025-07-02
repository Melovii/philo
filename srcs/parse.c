#include "philo.h"

// check this shit
static int	arg_is_num(char *arg)
{
    int	i;

    i = 0;
	// ?is this necessary?
    if (arg[i] == '-' || arg[i] == '+')
        i++;

    while (arg[i])
    {
        if (arg[i] < '0' || arg[i] > '9')
            return (1);
        i++;
    }
    return (0);
}

// change this implementation
static int	ft_atoi(char *str)
{
    unsigned long long	nb;
    int					sign;
    int					i;

    nb = 0;
    sign = 1;
    i = 0;
    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
        || str[i] == '\f' || str[i] == '\r')
        i++;
    if (str[i] == '-')
        sign = -1;
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i] >= '0' && str[i] <= '9')
    {
        nb = nb * 10 + (str[i] - '0');
        i++;
    }
    return (nb * sign);
}

int	validate_args(char **argv)
{
    if (ft_atoi(argv[1]) > MAX_PHILOS || ft_atoi(argv[1]) <= 0
        || arg_is_num(argv[1]) == 1)
        return (write(2, "Error: Invalid number of philosophers.\n", 40));
        
    if (ft_atoi(argv[2]) <= 0 || arg_is_num(argv[2]) == 1)
        return (write(2, "Error: Invalid time to die argument.\n", 38));
        
    if (ft_atoi(argv[3]) <= 0 || arg_is_num(argv[3]) == 1)
        return (write(2, "Error: Invalid time to eat argument.\n", 38));
        
    if (ft_atoi(argv[4]) <= 0 || arg_is_num(argv[4]) == 1)
        return (write(2, "Error: Invalid time to sleep argument.\n", 40));
        
    if (argv[5] && (ft_atoi(argv[5]) <= 0 || arg_is_num(argv[5]) == 1))
        return (write(2, "Error: Invalid must eat count argument.\n", 41));
        
    return (0);
}

// Read & validate argv into table
int 	parse_args(int argc, char **argv, t_round_table *table)
{	
    // Convert arguments to appropriate types
    table->num_philos = ft_atoi(argv[1]);
    table->time_to_die = ft_atoi(argv[2]);
    table->time_to_eat = ft_atoi(argv[3]);
    table->time_to_sleep = ft_atoi(argv[4]);

    if (argc == MAX_ARGS)
        table->must_eat_count = ft_atoi(argv[5]);
    else
        table->must_eat_count = -1; // No must eat condition

    return (1);
}
