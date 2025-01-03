#include "../philo.h"
void *philo(void *raw_data)
{
	t_philo_data *data = (t_philo_data *)raw_data;
	printf("Philo %d is thinking...\n", data->index);
	sleep(1);
	printf("Philo %d died...\n", data->index);
	return (NULL);
}

