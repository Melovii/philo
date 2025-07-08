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
	unsigned long	end;
	unsigned long	now;

	start = get_timestamp();
	end = start + ms;
	now = start;
	while (end > now + 5)
	{
		usleep(1000 * (end - now - 5));
		now = get_timestamp();
	}
	// busy wait for last few milliseconds for accuracy
	while (end > now)
		now = get_timestamp();
}