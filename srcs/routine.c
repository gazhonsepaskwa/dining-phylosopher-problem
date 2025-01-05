# include "philo.h"

void	routine_eat(t_philo_data *data)
{
	int	time_tmp;

	pthread_mutex_lock(&data->table->forks[data->index]);
	status(data, "has taken a fork");
	pthread_mutex_lock(&data->table->forks[data->index + 1]);
	status(data, "has taken a fork");
	status(data, "is eating");
	pthread_mutex_lock(&data->table->eat_time_mutex);
	time_tmp = data->table->eat_time;
	pthread_mutex_unlock(&data->table->eat_time_mutex);
	usleep(time_tmp);
	pthread_mutex_unlock(&data->table->forks[data->index]);
	pthread_mutex_unlock(&data->table->forks[data->index + 1]);
}

void	routine_sleep(t_philo_data *data)
{
	int	time_tmp;

	status(data, "is sleeping");
	pthread_mutex_lock(&data->table->sleep_time_mutex);
	time_tmp = data->table->sleep_time;
	pthread_mutex_unlock(&data->table->sleep_time_mutex);
	usleep(time_tmp);
}

void	routine_think(t_philo_data *data)
{
	status(data, "is thinking");
}
