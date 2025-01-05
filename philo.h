#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct s_philo_data
{
	int				index;
	struct s_table	*table;
}					t_philo_data;

typedef struct s_table
{
	pthread_t		*philos;
	t_philo_data	*philos_data;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	int				philo_count;
	pthread_mutex_t	philo_count_mutex;
	int				die_time;
	int				eat_time;
	pthread_mutex_t	eat_time_mutex;
	int				eat_count;
	pthread_mutex_t	eat_count_mutex;
	int				sleep_time;
	pthread_mutex_t	sleep_time_mutex;
	int				sim_stop;
	pthread_mutex_t	sim_stop_mutex;
	int				occurences;
}					t_table;

int check_ok(int ac, char **av);
void *philo(void *raw_data);

// routine
void	routine_think(t_philo_data *data);
void	routine_sleep(t_philo_data *data);
void	routine_eat(t_philo_data *data);

// philo
void status(t_philo_data *data, char *message);
void *watcher_fct(void *raw_data);


#endif
