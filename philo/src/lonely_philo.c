/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lonely_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 17:38:54 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/29 18:04:26 by adpinhei         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/philo.h"

void	ft_lonely_philo(t_table *table)
{
	long long	start;

	start = ft_get_time();
	printf("%lldms\tphilosopher %d has taken a fork.\n",\
ft_elapsed_time(&table->start_time), 1);
	while (ft_get_time() - start < table->time_to_die)
		usleep(1);
	printf("%lldms\tphilosopher %d has died.\n",\
ft_elapsed_time(&table->start_time), 1);
}
