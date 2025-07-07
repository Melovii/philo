#include "philo.h"

// * Get current time in milliseconds
unsigned long	get_timestamp(void)
{
	struct timeval	curr_time;

	if (gettimeofday(&curr_time, NULL) == -1)
	{
		write(2, "Error getting time\n", 20);
		return (0);
	}

	return (curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000);
}

// * Sleep for a specified number of milliseconds
void	delay(unsigned long ms)
{
	unsigned long	start;

	start = get_timestamp();

	while ((get_timestamp() - start) < ms)
		usleep(100); // Sleep for 100 microseconds to avoid busy waiting (consider 500 microseconds)
}
