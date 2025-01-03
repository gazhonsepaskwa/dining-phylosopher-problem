#include "../philo.h"
#include "utils/utils.h"

int	init(t_table *table)
{
	int	i;

	table->philos = malloc(sizeof(pthread_t *) * table->philo_count);
	table->philos_data = malloc(sizeof(t_philo_data) * table->philo_count);
	table->forks = malloc(sizeof(pthread_mutex_t *) * table->philo_count);
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
		return (0);
	i = 0;
	while (i < table->philo_count)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			return (0);
		table->philos_data[i].index = i + 1;
		table->philos_data[i].table = table;
		pthread_create(&table->philos[i], NULL, philo, &table->philos_data[i]);
		i++;
	}
	return (1);
}

void	free_table_r(t_table *table)
{
	int	i;
	free(table->philos_data);
	i = 0;
	while (i < table->philo_count)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
	free(table->philos);
}

int main(int ac, char **av)
{
	t_table table;

	if (!check_ok(ac, av))
		return (1);
	table.philo_count = ft_atoi(av[1]);
	init(&table);
	{
		free_table_r(&table);
		return (1);
	}
	// loop to join back all the thread (aka wait theme to finish before ending the main thread)
	free_table_r(&table);
	return (0);
}
