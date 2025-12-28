/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 17:41:15 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/28 20:14:54 by adpinhei         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/philo.h"

static void	ft_pickforks(t_philo *philo, int first_fork, int sec_fork);
static void	ft_releaseforks(t_philo *philo, int first_fork, int sec_fork);

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
		pthread_mutex_lock(&philo->table->death_lock);
		if (philo->table->death_flag)
		{
			pthread_mutex_unlock(&philo->table->death_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->table->death_lock);
		ft_print_status(philo, "is thinking.");
		if (philo->philo_id % 2 == 0)
			ft_pickforks(philo, left_fork, right_fork);
		else
			ft_pickforks(philo, right_fork, left_fork);
		ft_print_status(philo, "is eating.");
		pthread_mutex_lock(&philo->table->death_lock);
		philo->last_meal = ft_get_time();
		pthread_mutex_unlock(&philo->table->death_lock);
		philo->meals_eaten += 1;
		ft_sleep((long long)philo->table->time_to_eat, philo);
		if (philo->philo_id % 2 == 0)
			ft_releaseforks(philo, right_fork, left_fork);
		else
			ft_releaseforks(philo, left_fork, right_fork);
		if (philo->meals_eaten == philo->table->number_of_meals)
			break ;
		ft_print_status(philo, "is sleeping.");
		ft_sleep((long long)philo->table->time_to_sleep, philo);
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
	printf("%lldms\tphilosopher %d %s\n", timestamp, philo->philo_id, status);
	pthread_mutex_unlock(&philo->table->death_lock);
}

static void	ft_pickforks(t_philo *philo, int first_fork, int sec_fork)
{
	if (pthread_mutex_lock(&philo->table->forks[first_fork]))
		return ;
	ft_print_status(philo, "has taken a fork.");
	if (pthread_mutex_lock(&philo->table->forks[sec_fork]))
	{
		pthread_mutex_unlock(&philo->table->forks[first_fork]);
		return ;
	}
	ft_print_status(philo, "has taken a fork.");
}

static void	ft_releaseforks(t_philo *philo, int first_fork, int sec_fork)
{
	pthread_mutex_unlock(&philo->table->forks[first_fork]);
	ft_print_status(philo, "has released a fork.");
	pthread_mutex_unlock(&philo->table->forks[sec_fork]);
	ft_print_status(philo, "has released a fork.");
}
