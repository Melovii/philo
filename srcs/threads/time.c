#include "philo.h"

// * Get current time in milliseconds with maximum precision
unsigned long	get_timestamp(void)
{
	struct timeval	curr_time;
	unsigned long	result;

	if (gettimeofday(&curr_time, NULL) == -1)
	{
		write(2, "Error getting time\n", 20);
		return (0);
	}

	// Calculate with explicit type promotion to avoid precision loss
	result = (unsigned long)curr_time.tv_sec * 1000UL;
	result += (unsigned long)curr_time.tv_usec / 1000UL;
	
	return (result);
}

// * Sleep for a specified number of milliseconds with high precision
void	delay(unsigned long ms)
{
	unsigned long	start;
	unsigned long	end;
	unsigned long	now;
	unsigned long	remaining;

	start = get_timestamp();
	end = start + ms;
	
	// For very short delays, use only busy waiting for precision
	if (ms <= 5)
	{
		while (get_timestamp() < end)
			usleep(100); // Small sleep to prevent 100% CPU usage
		return;
	}
	
	// For longer delays, use a hybrid approach
	while (1)
	{
		now = get_timestamp();
		if (now >= end)
			return;
			
		remaining = end - now;
		
		// If more than 3ms remaining, sleep for most of it
		if (remaining > 3)
		{
			usleep((remaining - 3) * 900); // Sleep for 90% of remaining time
		}
		else
		{
			// For final 3ms, use busy waiting for precision
			while (get_timestamp() < end)
				;
			return;
		}
	}
}