/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 16:50:37 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/28 17:47:27 by adpinhei         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/philo.h"

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
				ft_print_status(&(*table).philos[i], "has died.");
				pthread_mutex_unlock(&table->death_lock);
				return (NULL) ;
			}
			pthread_mutex_unlock(&table->death_lock);
			i++;
		}
		usleep(100);
	}
	return (NULL);
}
