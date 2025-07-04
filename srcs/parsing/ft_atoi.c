#include "philo.h"

// Checks if character is whitespace
static int is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' ||
			c == '\f' || c == '\v' || c == '\r');
}

// Checks if character is a digit
static int is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

// Skips whitespace and returns next index
static int skip_whitespace(const char *str, int i)
{
	while (is_space(str[i]))
		i++;
	return i;
}

// Parses sign and updates index, returns sign multiplier
static int parse_sign(const char *str, int *index)
{
	int sign = 1;

	if (str[*index] == '-' || str[*index] == '+')
	{
		if (str[*index] == '-')
			sign = -1;
		(*index)++;
	}
	return sign;
}

// Converts string to int with overflow and error checking
int	ft_atoi(const char *str)
{
	long	result;
	int		i;
	int		sign;

	result = 0;
	i = 0;
	i = skip_whitespace(str, i);
	sign = parse_sign(str, &i);

	// No digits after optional sign -> return 0 or error
	if (!is_digit(str[i]))
		return (0);

	while (is_digit(str[i]))
	{
		int digit = str[i] - '0';

		// Check for overflow before multiplying and adding digit
		if (result > (LONG_MAX - digit) / 10)
			return (sign == 1) ? INT_MAX : INT_MIN;

		result = result * 10 + digit;
		i++;
	}
	return ((int)(result * sign));
}
