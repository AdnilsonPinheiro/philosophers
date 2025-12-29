/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 18:57:34 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/28 20:38:45 by adpinhei         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/philo.h"

/// @brief gets current time in miliseconds
long long	ft_get_time(void)
{
	struct timeval	tv;
	long long		time;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

/// @brief calculates the elapsed time in msec
/// @param start_time struct timeval pointed to by t_table
/// @return the elapsed time in msec
long long	ft_elapsed_time(struct timeval *start_time)
{
	struct timeval	*current;
	long long		start_ms;
	long long		current_ms;

	current = malloc(sizeof(struct timeval));
	if (!current)
		return (-1);
	if (gettimeofday(current, NULL) != 0)
		return (-1);
	start_ms = (start_time->tv_sec * 1000) + (start_time->tv_usec / 1000);
	current_ms = (current->tv_sec * 1000) + (current->tv_usec / 1000);
	return (current_ms - start_ms);
}

/// @brief waits for an amount of miliseconds
/// @param interval miliseconds to be awaited
void	ft_sleep(long long interval, t_philo *philo)
{
	long long	start;

	start = ft_get_time();
	while (ft_get_time() - start < interval)
	{
		pthread_mutex_lock(&philo->table->death_lock);
		if (philo->table->death_flag)
		{
			pthread_mutex_unlock(&philo->table->death_lock);
			return ;
		}
		pthread_mutex_unlock(&philo->table->death_lock);
		usleep(1);
	}
}
