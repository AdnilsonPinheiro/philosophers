/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 17:09:47 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/27 15:45:17 by adpinhei         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/philo.h"

void	ft_clean_table(t_table *table, char *msg)
{
	int	i;

	if (!table)
		return ;
	i = 0;
	while (i < table->philo_number)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
	pthread_mutex_destroy(&table->death_lock);
	if (msg)
		printf("%s\n", msg);
}

void	ft_clean_philo(t_philo *philo, int philo_number)
{
	int	i;

	if (!philo)
		return ;
	i = 0;
	while (i < philo_number)
	{
		if (philo[i].th_id != 0)
			pthread_join(philo[i].th_id, NULL);
		philo[i].table = NULL;
		i++;
	}
	free(philo);
}
