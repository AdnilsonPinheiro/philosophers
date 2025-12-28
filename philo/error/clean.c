/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 17:09:47 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/28 18:46:47 by adpinhei         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/philo.h"

void	ft_clean_table(t_table *table, char *msg)
{
	int	i;

	if (!table)
		return ;
	if (table->forks)
	{
		i = 0;
		while (i < table->philo_number)
		{
			pthread_mutex_destroy(&table->forks[i]);
			i++;
		}
		free(table->forks);
	}
	pthread_mutex_destroy(&table->death_lock);
	if (msg)
		printf("Error: %s\n", msg);
}
