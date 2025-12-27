/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:43:54 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/27 19:41:07 by adpinhei         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/philo.h"

/// @brief summons all philosophers threads
void	ft_summon_philo(t_table *table)
{
	int		i;
	t_philo	*philos;

	philos = malloc(sizeof(t_philo) * table->philo_number);
	if (!philos)
	{
		ft_clean_table(table, "Unable to allocate philos.");
		return ;
	}
	i = 0;
	while (i < table->philo_number)
	{
		philos[i].table = table;
		philos[i].last_meal = 0;
		philos[i].meals_eaten = 0;
		philos[i].philo_id = i + 1;
		if (pthread_create(&philos[i].th_id, NULL, &routine, (void*)&philos[i]))
		{
			ft_clean_philo(philos, i);
			ft_clean_table(table, "Unable to create thread.");
			free (philos);
			return ;
		}
		i++;
	}
	i = 0;
	while (i < table->philo_number)
	{
		pthread_join(philos[i].th_id, NULL);
		i++;
	}
	free(philos);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5 && argc != 6)
	{
		printf("Invalid syntax. ./philo [number of philosophers]\
[time to die][time to eat][time to sleep][OPT number of meals]\n");
		return (1);
	}
	if (ft_check_args(argv))
		return (2);
	if (ft_init_table(&table, argv))
		ft_clean_table(&table, "Initialization failed");
	if (!table.forks)
		return (ft_clean_table(&table, "Unable to alloc forks"), 3);
	ft_summon_philo(&table);
	ft_clean_table(&table, NULL);
}
