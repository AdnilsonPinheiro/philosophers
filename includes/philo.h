/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:30:53 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/26 18:57:32 by adpinhei         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef PHILO
# define PHILO

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_table
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	death_lock;
	int				philo_number;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	struct timeval	start_time;
	int				death_flag;
}	t_table;

typedef struct s_philo
{
	pthread_t	id;
	t_table		*table;
	long long	last_meal;
}	t_philo;

/******************************************************************************/
/*                                  Utils                                     */
/******************************************************************************/

int		ft_atol(char *str);
int		ft_check_args(char **argv);

/******************************************************************************/
/*                                  Error                                     */
/******************************************************************************/

void	ft_clean_table(t_table *table, char *msg);

#endif