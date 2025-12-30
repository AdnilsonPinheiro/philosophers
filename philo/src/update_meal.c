/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_meal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 18:46:21 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/30 19:06:52 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	update_meal(t_philo *philo)
{
	if (!philo)
		return (0);
	pthread_mutex_lock(&philo->table->death_lock);
	if (philo->table->death_flag)
	{
		pthread_mutex_unlock(&philo->table->death_lock);
		return (1);
	}
	philo->last_meal = ft_get_time();
	pthread_mutex_unlock(&philo->table->death_lock);
	philo->meals_eaten += 1;
	return (0);
}
