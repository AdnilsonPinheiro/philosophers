/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 18:39:58 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/29 18:40:55 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
	pthread_mutex_unlock(&philo->table->death_lock);
	printf("%lldms\tphilosopher %d %s\n", timestamp, philo->philo_id, status);
}
