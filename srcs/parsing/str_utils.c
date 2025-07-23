// * Gets length of given string
int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

// * Checks if a character is a whitespace
int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\f' || c == '\v' || c == '\r');
}

// * Right trims argument of whitespaces
char	*arg_trim_r(char *str)
{
	int	len;

	len = ft_strlen(str) - 1;
	while (len > 0)
	{
		if (is_whitespace(str[len]))
			str[len] = '\0';
		else
			break ;
		len--;
	}
	return (str);
}

// * Compares two strings lexicographically
int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
