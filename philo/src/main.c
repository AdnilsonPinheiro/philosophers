/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:43:54 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/28 18:45:37 by adpinhei         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5 && argc != 6)
	{
		printf("Invalid syntax.\n\n./philo\n\t[number of philosophers]\
\n\t[time to die]\n\t[time to eat]\n\t[time to sleep]\n\t\
[OPT number of meals]\n");
		return (1);
	}
	if (ft_check_args(argv))
		return (2);
	if (ft_init_table(&table, argv))
		return (ft_clean_table(&table, "Initialization failed"), 3);
	ft_summon_philo(&table);
	ft_clean_table(&table, NULL);
}
