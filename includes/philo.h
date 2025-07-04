#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>	// for pthreads
# include <unistd.h>	// for usleep, write
# include <stdlib.h>	// for malloc, free
# include <stdbool.h>	// for bool				// TODO: Check if permissable by the subject.pdf
# include <stdio.h>		// for printf			// TODO: Remove if only necessary in main.c
# include <sys/time.h>	// for gettimeofday

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-		// * Definitions

// * Exit codes
# define EX_OK			0
# define EX_KO			1

// * Bounds
# define MIN_ARGS		5
# define MAX_ARGS		6
# define MAX_PHILOS		200

// * Time conversion
# define MS_TO_US(x)	((x) * 1000L)	// millisecond to microsecond conversion for usleep // TODO: CHECK IF I CAN USE MACROS

// * Philo state msgs
# define STATE_FORK		"has taken a fork"
# define STATE_SLEEP	"is sleeping"
# define STATE_EAT		"is eating"
# define STATE_THINK	"is thinking"
# define STATE_DEAD		"died"

#define USAGE_MSG  \
	"Usage: %s number_of_philosophers time_to_die time_to_eat " \
	"time_to_sleep [must_eat]\n"	// TODO: check if this is ok lol

typedef pthread_mutex_t t_mtx; // convenient lol

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-		// * Structs

typedef struct s_round_table	t_round_table;

// * Per-philosopher state
typedef struct	s_philo
{
	int				id;				// starts from 1, ok? lol
	unsigned long	last_meal;		// timestamp of last meal eaten - use to detect death (if current time - last_meal > time_to_die)
	int				meals_eaten;	// use for optional stopping condition // !TODO: Consider changing to size_t
	bool			is_full;		// true if the philo has eaten enough times // ! uhm do I keep this lol
	pthread_t		thread;			// the ACTUAL thread the philo runs on
	t_mtx			*left_fork;		// pointer to the left fork (mutex 1)
	t_mtx			*right_fork;	// pointer to the right fork (mutex 1)
	t_round_table	*table;			// reference back to the table
}				t_philo;

// * Global simulation parameters and resources
typedef struct	s_round_table
{
	int				num_philos;		// philosopher AND fork count 
	unsigned long	time_to_sleep;	// ms to stimulate mimimi 
	unsigned long	time_to_eat;	// ms to stimulate nomnom
	unsigned long	time_to_die;	// ms allowed between "end of last meal" and strarvation (check condition)
	int				must_eat_count;	// end simulation when every philo eats this many times
	bool			end_simulation;	// true when all philos are full or dead
	t_philo			*philos;		// holds each philosopher's state
	t_mtx			*forks;			// one per fork (lock two adjacent forks before eating)
	t_mtx			print_lock;		// use this to prevent printf calls from different threads
	t_mtx			death_lock;		// use this to prevent multiple death signals
	t_mtx			meal_lock;		// use this to prevent multiple meal count updates
}				t_round_table;

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-		// * Function Prototypes

/* --- parse.c --- */
// * Parse and validate CLI arguments into table; returns 1 on success
int 	parse_args(int argc, char **argv, t_round_table *table);

// * Checks if the argumentt consist of numbers and are within range
int		validate_args(char **argv);



/* --- time.c --- */
// * Return current time in milliseconds
unsigned long	get_timestamp(void);

// * Sleep for a specified number of milliseconds
void	delay(unsigned long ms);



/* --- utils.c --- */
// * Allocate & initialize table resources; return 1 on success
int     init_round_table(t_round_table *table);

// * Initialize philosopher IDs and fork pointers; set last meal and meals eaten to 0
void	init_philosophers(t_round_table *table);

// * Destroy mutexes & free all dynamic allocations
void    cleanup_table(t_round_table *table);

// * Thread-safe print of a philosopher’s state
void    print_state(t_round_table *table, int id, char *state);



/* --- simulation.c --- */
// * Spawn philosopher threads and any monitor(s); return 1 on success
int     start_simulation(t_round_table *table);

// * Join threads or otherwise wait until simulation ends
void    wait_for_completion(t_round_table *table);

// * (Optional) Centralized death detection and signaling
int     detect_and_signal_death(t_round_table *table);



/* --- philosophers.c --- */
// * Entry point for each philosopher thread’s routine
void    *philo_routine(void *arg);


/* temp */

#endif
