/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:13:57 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/26 16:40:22 by adpinhei         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/philo.h"

/// @brief turns char* into int, through long so program can check for overhead
/// @param str char* to be turned into int
/// @return 0 if there's no str or there are no digits in the str,
///			 -1 if negative, -2 if > INT_MAX, (int)i on success.
int	ft_atol(char *str)
{
	long	i;
	int		c;

	if (!str)
		return (0);
	c = 0;
	while (str[c] && str[c] < '0' || str[c] > '9')
	{
		if (str[c] == '-')
			return (-1);
		c++;
	}
	if (str[c] == '\0')
		return (0);
	while (str[c] && str[c] >= '0' && str[c] <= '9')
	{
		i = i * 10 + (str[c] - 48);
		c++;
	}
	if (i > INT_MAX)
		return (-2);
	return ((int)i);
}

int	ft_check_args(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (ft_atol(argv[i]) == 0)
		{
			printf("Number cannot be 0\n");
			return (1);
		}
		else if (ft_atol(argv[i]) == -1)
		{
			printf("Number cannot be negative\n");
			return (2);
		}
		else if (ft_atol(argv[i]) == -2)
		{
			printf("Number should not be greater than INT_MAX, c'mon\n");
			return (3);
		}
		i++;
	}
	return (0);
}
