#include <unistd.h>
#include <sys/time.h>

unsigned long	get_timestamp(void)
{
	struct timeval	curr_time;

	if (gettimeofday(&curr_time, NULL) == -1)
	{
		write(2, "Error getting time\n", 20);
		return (0);
	}
	return ((curr_time.tv_sec * 1000UL) + (curr_time.tv_usec / 1000UL));
}

void	delay(unsigned long ms)
{
	unsigned long	start;

	start = get_timestamp();
	if (ms == 0)
		return ;
	while ((get_timestamp() - start) < ms)
		usleep(100);
}
