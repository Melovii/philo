#include <unistd.h>
#include <sys/time.h>

// * Get the current timestamp in milliseconds
unsigned long	get_timestamp(void)
{
	struct timeval	curr_time;

	// Get the current time
	if (gettimeofday(&curr_time, NULL) == -1)
	{
		write(2, "Error getting time\n", 20);
		return (0);
	}

	// Convert given time to milliseconds
	return ((curr_time.tv_sec * 1000UL) + (curr_time.tv_usec / 1000UL));
}

// * Sleep for a specified number of milliseconds
void	delay(unsigned long ms)
{
	unsigned long	start;

	// Get the current timestamp
	start = get_timestamp();
	if (ms == 0)
		return ;

	// Loop until the specified time has passed
	while ((get_timestamp() - start) < ms)
		usleep(10);
}
