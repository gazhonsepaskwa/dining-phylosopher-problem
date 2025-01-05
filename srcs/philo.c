#include "../philo.h"
#include "utils/utils.h"
#include <sys/time.h>
#include <time.h>

void status(t_philo_data *data, char *message)
{
	struct timeval	tv;
	long long		timestamp_in_ms;

    gettimeofday(&tv, NULL);
	timestamp_in_ms = (long long)(tv.tv_sec) * 1000 + (tv.tv_usec / 1000);
	pthread_mutex_lock(&data->table->print_mutex);
	printf("%lld %d %s\n", timestamp_in_ms, data->index, message);
	pthread_mutex_unlock(&data->table->print_mutex);
}

void _even(t_philo_data *data)
{
	int	tmp_time;
	int sim_stop;

	while (1)
	{
		if (data->index % 2 != 0)
			routine_eat(data);
		else
		{
			pthread_mutex_lock(&data->table->eat_time_mutex);
			tmp_time = data->table->eat_time;
			pthread_mutex_unlock(&data->table->eat_time_mutex);
			usleep(tmp_time / 2);
			routine_eat(data);
		}
		routine_sleep(data);
		routine_think(data);
		pthread_mutex_lock(&data->table->sim_stop_mutex);
		sim_stop = data->table->sim_stop;
		pthread_mutex_unlock(&data->table->sim_stop_mutex);
		if (sim_stop)
			break;
	}
}

void *philo(void *raw_data)
{
	t_philo_data	*data = (t_philo_data *)raw_data;
	// int				even;

	// pthread_mutex_lock(&data->table->philo_count_mutex);
	// even = 0;
	// if (data->table->philo_count % 2 == 0)
		// even = 1;
	// pthread_mutex_unlock(&data->table->philo_count_mutex);
	// if (even == 1)
		_even(data);
	// else
		// _odd(data);
	return (NULL);
}
