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
}					t_table;

int check_ok(int ac, char **av);
void *philo(void *raw_data);

#endif
