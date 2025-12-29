/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:13:57 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/29 17:57:35 by adpinhei         ###   ########.fr       */
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

	c = 0;
	while (str[c] && (str[c] == ' ' || str[c] == '\t'))
		c++;
	if (str[c] == '+' || str[c] == '-')
	{
		if (str[c] == '-')
			return (-1);
		c++;
	}
	if (str[c] < '0' || str[c] > '9')
		return (0);
	i = 0;
	while (str[c] && (str[c] >= '0' && str[c] <= '9'))
	{
		i = i * 10 + (str[c] - 48);
		c++;
	}
	if (str[c] != '\0')
		return (0);
	if (i > INT_MAX)
		return (-2);
	return ((int)i);
}

/// @brief check the validity of passed arguments
/// @param argv the arguments passed from CLI
/// @return 0 on success, greater than 0 on failure
int	ft_check_args(char **argv)
{
	int	i;
	int	num;

	i = 1;
	while (argv[i])
	{
		num = ft_atol(argv[i]);
		if (num == 0)
		{
			printf("Must be a valid number.\n");
			return (1);
		}
		else if (num == -1)
		{
			printf("Number cannot be negative.\n");
			return (2);
		}
		else if (num == -2)
		{
			printf("Number should not be greater than INT_MAX.\n");
			return (3);
		}
		i++;
	}
	return (0);
}

/// @brief initialize the table struct
/// @param table the main struct
/// @return 0 on success, greater than 0 on failure
int	ft_init_table(t_table *table, char **argv)
{
	int	i;

	table->death_flag = 0;
	table->philo_number = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	table->philos = NULL;
	table->forks = NULL;
	if (argv[5])
		table->number_of_meals = ft_atol(argv[5]);
	else
		table->number_of_meals = -1;
	gettimeofday(&table->start_time, NULL);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_number);
	if (!table->forks)
		return (1);
	if (pthread_mutex_init(&table->death_lock, NULL))
	{
		free(table->forks);
		return (2);
	}
	i = 0;
	while (i < table->philo_number)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&table->forks[i]);
			pthread_mutex_destroy(&table->death_lock);
			free(table->forks);
			return (3);
		}
		i++;
	}
	return (0);
}

/// @brief summons all philosophers threads
void	ft_summon_philo(t_table *table)
{
	pthread_t	monitor;
	int			i;
	long long	utime;

	table->philos = malloc(sizeof(t_philo) * table->philo_number);
	if (!table->philos)
	{
		printf("Unable to allocate philosophers\n");
		return ;
	}
	i = 0;
	utime = ft_get_time();
	while (i < table->philo_number)
	{
		table->philos[i].table = table;
		table->philos[i].last_meal = utime;
		table->philos[i].philo_id = i + 1;
		table->philos[i].meals_eaten = 0;
		i++;
	}
	if (table->philo_number == 1)
	{
		ft_lonely_philo(table);
		return ;
	}
	i = 0;
	while (i < table->philo_number)
	{
		if (pthread_create(&table->philos[i].th_id, NULL, &routine,\
(void*)&table->philos[i]))
		{
			printf("Unable to create thread %d\n", i + 1);
			table->death_flag = 1;
			while (--i >= 0)
				pthread_join(table->philos[i].th_id, NULL);
			free(table->philos);
			return ;
		}
		i++;
	}
	if (pthread_create(&monitor, NULL, &monitor_routine, (void*)table))
	{
		printf("Unable to create monitor thread\n");
		table->death_flag = 1;
		i = 0;
		while (i < table->philo_number)
		{
			pthread_join(table->philos[i].th_id, NULL);
			i++;
		}
		free(table->philos);
		return ;
	}
	pthread_join(monitor, NULL);
	i = 0;
	while (i < table->philo_number)
	{
		pthread_join(table->philos[i].th_id, NULL);
		i++;
	}
	free(table->philos);
}
