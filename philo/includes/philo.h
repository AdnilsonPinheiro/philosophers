/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:30:53 by adpinhei          #+#    #+#             */
/*   Updated: 2025/12/28 16:15:47 by adpinhei         ###   ########.fr       */
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
	struct timeval	start_time;
	pthread_t		monitor;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death_lock;
	int				philo_number;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	int				death_flag;
}	t_table;

typedef struct s_philo
{
	t_table		*table;
	pthread_t	th_id;
	long long	last_meal;
	int			philo_id;
	int			meals_eaten;
}	t_philo;

/******************************************************************************/
/*                                 Routine                                    */
/******************************************************************************/

void		*routine(void *args);
void		ft_print_status(t_philo *philo, char *status);

/******************************************************************************/
/*                              Time Functions                                */
/******************************************************************************/

long long	ft_get_time(void);
long long	ft_elapsed_time(struct timeval *start_time);
void		ft_sleep(long long interval, t_philo *philo);


/******************************************************************************/
/*                                  Utils                                     */
/******************************************************************************/

int			ft_atol(char *str);
int			ft_check_args(char **argv);
int			ft_init_table(t_table *table, char **argv);
void		ft_summon_philo(t_table *table);

/******************************************************************************/
/*                                  Error                                     */
/******************************************************************************/

void		ft_clean_table(t_table *table, char *msg);
void		ft_clean_philo(t_philo *philo, int philo_number);

#endif