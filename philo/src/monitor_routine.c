/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 16:50:37 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/29 17:27:29 by adpinhei         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/philo.h"

static void	ft_death_print(int i, t_table *table)
{
	long long	time_of_death;

	time_of_death = ft_elapsed_time(&table->start_time);
	printf("%llums\tphilosopher %d died.\n", time_of_death, i);
}


void	*monitor_routine(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table*)arg;
	while (1)
	{
		i = 0;
		while (i < table->philo_number)
		{
			pthread_mutex_lock(&table->death_lock);
			if ((ft_get_time() - table->philos[i].last_meal) > table->time_to_die)
			{
				table->death_flag = 1;
				pthread_mutex_unlock(&table->death_lock);
				ft_death_print(table->philos[i].philo_id, table);
				return (NULL) ;
			}
			pthread_mutex_unlock(&table->death_lock);
			i++;
		}
		usleep(1);
	}
	return (NULL);
}
