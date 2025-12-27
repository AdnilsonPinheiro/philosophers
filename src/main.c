/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:43:54 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/27 15:48:30 by adpinhei         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/philo.h"

/// @brief initialize the table struct
/// @param table the main struct
/// @return 0 on success, greater than 0 on failure
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

void	ft_summon_philo(t_table *table)
{
	int		i;
	t_philo	philo[table->philo_number];

	i = 0;
	while (i < table->philo_number)
	{
		philo[i].table = table;
		philo[i].last_meal = -1;
		philo[i].philo_id = i + 1;
		if ((i + 1) % 2 == 0)
		{
			if (pthread_create(&philo[i].th_id, NULL, &routine, NULL))
			{
				ft_clean_table(table, "Unable to create thread.");
				ft_clean_philo(philo, table->philo_number);
				return ;
			}
		}
		else
		{
			if (pthread_create(&philo[i].th_id, NULL, &routine, NULL))
			{
				ft_clean_table(table, "Unable to create thread.");
				ft_clean_philo(philo, table->philo_number);
				return ;
			}
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5 && argc != 6)
		return (1);
	if (ft_check_args(argv))
		return (2);
	if (ft_init_table(&table, argv))
		ft_clean_table(&table, "Initialization failed");
	if (!table.forks)
		return (ft_clean_table(&table, "Unable to alloc forks"), 3);
	ft_summon_philo(&table);
	ft_clean_table(&table, NULL);
}
