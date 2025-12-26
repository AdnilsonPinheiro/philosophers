/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:43:54 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/26 18:57:15 by adpinhei         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/philo.h"

int	ft_init_table(t_table *table, char **argv)
{
	int	i;

	table->death_flag = 0;
	table->philo_number = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		table->number_of_meals = ft_atol(argv[5]);
	else
		table->number_of_meals = -1;
	gettimeofday(&table->start_time, NULL);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_number);
	if (pthread_mutex_init(&table->death_lock, NULL))
		return (1);
	i = 0;
	while (i < table->philo_number)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			return (2);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
		return (1);
	if (ft_check_args(argv))
		return (2);
	if (ft_init_table(&table, argv))
		ft_clean_table(&table, "Initialization failed");
	if (!table.forks)
		return (ft_clean_table(&table, "Unable to alloc forks"), 3);
	ft_clean_table(&table, NULL);
}
