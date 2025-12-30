/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 18:42:09 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/30 19:13:07 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_mutex_init(t_table *table);

/// @brief initialize the table struct
/// @param table the main struct
/// @return 0 on success, greater than 0 on failure
int	ft_init_table(t_table *table, char **argv)
{
	table->death_flag = 0;
	table->philo_number = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	table->philos = NULL;
	table->forks = NULL;
	if (argv[5])
		table->number_of_meals = ft_atol(argv[5]);
	else
		table->number_of_meals = -1;
	gettimeofday(&table->start_time, NULL);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_number);
	if (!table->forks)
		return (1);
	if (pthread_mutex_init(&table->death_lock, NULL))
		return (free(table->forks), 2);
	if (pthread_mutex_init(&table->print_mutex, NULL))
		return (free(table->forks), 2);
	ft_mutex_init(table);
	return (0);
}

static int	ft_mutex_init(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_number)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&table->forks[i]);
			pthread_mutex_destroy(&table->death_lock);
			free(table->forks);
			return (1);
		}
		i++;
	}
	return (0);
}
