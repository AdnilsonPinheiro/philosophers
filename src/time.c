/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 18:57:34 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/27 19:49:42 by adpinhei         ###   ########.fr       */
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

	if (gettimeofday(&current, NULL) != 0)
		return (-1);
	start_ms = (start_time->tv_sec * 1000) + (start_time->tv_usec / 1000);
	current_ms = (current->tv_sec * 1000) + (current->tv_usec / 1000);
	return (current_ms - start_ms);
}

/// @brief waits for an amount of miliseconds
/// @param interval miliseconds to be awaited
void	ft_sleep(long long interval)
{
	long long	start;

	start = ft_get_time();
	while (ft_get_time() - start < interval)
		usleep(200);
}
