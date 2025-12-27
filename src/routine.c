/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 17:41:15 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/27 19:48:45 by adpinhei         ###   ########.fr       */
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
	if (philo->philo_id % 2 != 0)
	{
		pthread_mutex_lock(&philo->table->forks[right_fork]);
		printf("Philosopher %d has taken fork %d.\n", philo->philo_id, right_fork);
		pthread_mutex_lock(&philo->table->forks[left_fork]);
		printf("Philosopher %d has taken fork %d.\n", philo->philo_id, left_fork);
		printf("Philosopher %d is eating.\n", philo->philo_id);
		usleep(philo->table->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->table->forks[left_fork]);
		pthread_mutex_unlock(&philo->table->forks[right_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->table->forks[left_fork]);
		printf("Philosopher %d has taken fork %d.\n", philo->philo_id, left_fork);
		pthread_mutex_lock(&philo->table->forks[right_fork]);
		printf("Philosopher %d has taken fork %d.\n", philo->philo_id, right_fork);
		printf("Philosopher %d is eating.\n", philo->philo_id);
		usleep(philo->table->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->table->forks[right_fork]);
		pthread_mutex_unlock(&philo->table->forks[left_fork]);
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
