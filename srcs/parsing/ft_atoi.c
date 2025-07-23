#include "philo.h"

// * Skips whitespace characters in the string
static int	skip_whitespace(const char *str, int i)
{
	while (is_whitespace(str[i]))
		i++;
	return (i);
}

// * Returns index of first non-whitespace character
static int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

// * Gets the sign of the number and updates the index
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

// * Converts string to integer with overflow handling
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
	while (str[i])
	{
		if (!is_digit(str[i]))
			return (0);
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
