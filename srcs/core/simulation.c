#include "philo.h"

// thread startup/shutdown
int	start_simulation(t_round_table *table);
void	wait_for_completion(t_round_table *table);

// (optional) a helper to check & broadcast death to all threads:
int	detect_and_signal_death(t_round_table *table);
