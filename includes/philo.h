#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define EX_OK			0
# define EX_KO			1

# define MIN_ARGS		5
# define MAX_ARGS		6

# define MAX_LONG		9223372036854775807L
# define MAX_INT		2147483647
# define MIN_INT		-2147483648

# define STATE_FORK		"has taken a fork"
# define STATE_SLEEP	"is sleeping"
# define STATE_EAT		"is eating"
# define STATE_DEAD		"died"
# define STATE_THINK	"is thinking"
# define STATE_ERROR	"Error in simulation"

typedef pthread_mutex_t			t_mtx;

typedef struct s_round_table	t_round_table;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	unsigned long	last_meal;
	pthread_t		thread;
	t_mtx			*left_fork;
	t_mtx			*right_fork;
	t_round_table	*table;
}				t_philo;

typedef struct s_round_table
{
	int				num_philos;
	int				sim_halted;
	int				must_eat_count;
	unsigned long	time_to_sleep;
	unsigned long	time_to_eat;
	unsigned long	time_to_die;
	unsigned long	start_time;
	t_mtx			*forks;
	t_mtx			print_lock;
	t_mtx			death_lock;
	t_mtx			meal_lock;
	t_philo			*philos;
}				t_round_table;

int				validate_args(char **argv);
int				parse_args(int argc, char **argv, t_round_table *table);

int				ft_atoi(const char *str);
int				ft_strcmp(const char *s1, const char *s2);

unsigned long	get_timestamp(void);
void			delay(unsigned long ms);
void			ft_usleep(unsigned long ms);

int				init_round_table(t_round_table *table);
void			init_philosophers(t_round_table *table);

void			print_state(t_round_table *table, int id, char *state);

int				start_threads(t_round_table *table);
int				cleanup_threads(t_round_table *table, int count);
void			run_sim(t_round_table *table);

void			*philo_routine(void *arg);
void			*monitor(void *data);

void			pick_up_forks(t_philo *philo);
void			put_down_forks(t_philo *philo);
void			eat(t_philo *philo);
void			rest(t_philo *philo);
void			think(t_philo *philo);

void			cleanup_table(t_round_table *table);

#endif
