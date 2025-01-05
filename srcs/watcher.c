#include "../philo.h"

void *watcher_fct(void *raw_data)
{
	t_table	*table = (t_table *)raw_data;
	int		philo_count;

	pthread_mutex_lock(&table->philo_count_mutex);
	philo_count = table->philo_count;
	pthread_mutex_unlock(&table->philo_count_mutex);
	while (1)
	{
		pthread_mutex_lock(&table->sim_stop_mutex);
		pthread_mutex_lock(&table->eat_count_mutex);
		if (table->eat_count == philo_count * table->occurences)
		{
			table->sim_stop = 1;
			break;
		}
		pthread_mutex_unlock(&table->sim_stop_mutex);
	}
	return (NULL);
}
