/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:43:54 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/27 20:05:41 by adpinhei         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5 && argc != 6)
	{
		printf("Invalid syntax. ./philo [number of philosophers]\
[time to die][time to eat][time to sleep][OPT number of meals]\n");
		return (1);
	}
	if (ft_check_args(argv))
		return (2);
	if (ft_init_table(&table, argv))
		ft_clean_table(&table, "Initialization failed");
	if (!table.forks)
		return (ft_clean_table(&table, "Unable to alloc forks"), 3);
	ft_summon_philo(&table);
	ft_clean_table(&table, NULL);
}
