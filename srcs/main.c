#include "../philo.h"
#include "utils/utils.h"

void set_from_args(t_table *table, int ac, char **av)
{
	table->philo_count = ft_atoi(av[1]);
	table->die_time = ft_atoi(av[2]) * 1000;
	table->eat_time = ft_atoi(av[3]) * 1000;
	table->sleep_time = ft_atoi(av[4]) * 1000;
	if (ac == 6)
		table->occurences = ft_atoi(av[5]);
	else
		table->occurences = -1;
}

int	init(t_table *table, int ac, char **av)
{
	int	i;
	set_from_args(table, ac, av);
	table->sim_stop = 0;
	table->philos = malloc(sizeof(pthread_t *) * table->philo_count);
	table->philos_data = malloc(sizeof(t_philo_data) * table->philo_count);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_count);
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
	pthread_mutex_destroy(&table->print_mutex);
	free(table->forks);
	free(table->philos);
}

int main(int ac, char **av)
{
	int			i;
	t_table		table;
	pthread_t	watcher;

	if (!check_ok(ac, av))
		return (1);
	pthread_create(&watcher, NULL, watcher_fct, &table);
	if (!init(&table, ac, av))
	{
		free_table_r(&table);
		return (1);
	}
	i = 0;
	while (i < table.philo_count)
	{
		pthread_join(table.philos[i], NULL);
		i++;
	}
	pthread_join(watcher, NULL);
	free_table_r(&table);
	return (0);
}
