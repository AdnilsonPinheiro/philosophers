/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 17:41:15 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/27 17:51:39 by adpinhei         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/philo.h"

/*
	routine consists of:
	1. grabbing 1st fork
	2. grabbing 2nd fork
	3. eating fot table->time_to_eat
	4. sleep for table->time_to_sleep
	5. check for table->time_to_die
*/

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
