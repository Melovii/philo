#include "philo.h"

static int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\f' || c == '\v' || c == '\r');
}

static int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	skip_whitespace(const char *str, int i)
{
	while (is_space(str[i]))
		i++;
	return (i);
}

static int	parse_sign(const char *str, int *index)
{
	int	sign;

	sign = 1;
	if (str[*index] == '-' || str[*index] == '+')
	{
		if (str[*index] == '-')
			sign = -1;
		(*index)++;
	}
	return (sign);
}

int	ft_atoi(const char *str)
{
	long	result;
	int		i;
	int		sign;
	int		digit;

	result = 0;
	i = 0;
	i = skip_whitespace(str, i);
	sign = parse_sign(str, &i);
	if (!is_digit(str[i]))
		return (0);
	while (is_digit(str[i]))
	{
		digit = str[i] - '0';
		if (result > (MAX_LONG - digit) / 10)
		{
			if (sign == 1)
				return (MAX_INT);
			else
				return (MIN_INT);
		}
		result = result * 10 + digit;
		i++;
	}
	return ((int)(result * sign));
}
