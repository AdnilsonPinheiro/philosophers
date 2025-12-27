/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 17:41:15 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/27 19:54:04 by adpinhei         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/philo.h"

void	*routine(void *args)
{
	t_philo	*philo;
	int		left_fork;
	int		right_fork;

	philo = (t_philo*)args;
	left_fork = philo->philo_id - 1;
	right_fork = philo->philo_id % philo->table->philo_number;
	while (1)
	{
		
	}
	return (NULL);
}

/// @brief prints the philosopher status
/// @param philo the current thread
/// @param status what the philosopher is doing (e.g. eating, thinking or sleeping)
void	ft_print_status(t_philo *philo, char *status)
{
	long long	timestamp;

	if (pthread_mutex_lock(&philo->table->death_lock))
		return ;
	if (philo->table->death_flag)
	{
		pthread_mutex_unlock(&philo->table->death_lock);
		return ;
	}
	timestamp = ft_elapsed_time(&philo->table->start_time);
	printf("%lld %d %s\n", timestamp, philo->philo_id, status);
	pthread_mutex_unlock(&philo->table->death_lock);
}
