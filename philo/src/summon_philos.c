/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   summon_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 18:46:56 by adpinhei          #+#    #+#             */
/*   Updated: 2026/01/02 16:14:01 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	init_philo(t_table *table);
static void	thread_launch(t_table *table);
static void	monitor_launch(pthread_t *monitor, t_table *table);

/// @brief summons all philosophers threads
void	ft_summon_philo(t_table *table)
{
	pthread_t	monitor;
	int			i;

	table->philos = malloc(sizeof(t_philo) * table->philo_number);
	if (!table->philos)
	{
		printf("Unable to allocate philosophers\n");
		return ;
	}
	if (init_philo(table))
		return (free(table->philos));
	thread_launch(table);
	monitor_launch(&monitor, table);
	pthread_join(monitor, NULL);
	i = 0;
	while (i < table->philo_number)
	{
		pthread_join(table->philos[i].th_id, NULL);
		i++;
	}
	free(table->philos);
}

static int	init_philo(t_table *table)
{
	int			i;
	long long	utime;

	i = 0;
	utime = (table->start_time.tv_sec * 1000) + \
(table->start_time.tv_usec / 1000);
	while (i < table->philo_number)
	{
		table->philos[i].table = table;
		table->philos[i].last_meal = utime;
		table->philos[i].philo_id = i + 1;
		table->philos[i].meals_eaten = 0;
		i++;
	}
	if (table->philo_number == 1)
	{
		ft_lonely_philo(table);
		return (1);
	}
	return (0);
}

static void	thread_launch(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_number)
	{
		if (pthread_create(&table->philos[i].th_id, NULL, &routine, \
(void *)&table->philos[i]))
		{
			printf("Unable to create thread %d\n", i + 1);
			table->death_flag = 1;
			while (--i >= 0)
				pthread_join(table->philos[i].th_id, NULL);
			free(table->philos);
			return ;
		}
		i++;
	}
}

static void	monitor_launch(pthread_t *monitor, t_table *table)
{
	int	i;

	if (pthread_create(monitor, NULL, &monitor_routine, (void *)table))
	{
		printf("Unable to create monitor thread\n");
		table->death_flag = 1;
		i = 0;
		while (i < table->philo_number)
		{
			pthread_join(table->philos[i].th_id, NULL);
			i++;
		}
		free(table->philos);
		return ;
	}
}
