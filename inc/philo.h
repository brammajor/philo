/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmajor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 10:29:49 by brmajor           #+#    #+#             */
/*   Updated: 2023/10/04 13:52:24 by brmajor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_info
{
	int				numofphilo;
	int				ttdie;
	int				tteat;
	int				ttsleep;
	int				numofmeals;
	pthread_mutex_t	*fork;
}	t_info;

typedef struct s_philo
{
	int			n;
	int			dead;
	int			eating;
	int			times_eaten;
	long int	start_time;
	long int	last_meal;
	t_info		*info;
	pthread_t	thread_id;
}	t_philo;


t_philo		init_philo(t_info *info);
void		error_handler(char *msg);
t_philo		*start_threads(t_info *info, t_philo *philo);
int			ft_atoi(const char *str);
int			ft_strlen(char *str);
int			ft_isdigit(int i);
void		check_args(int ac, char **av);
t_philo		*eat(t_philo *p);
t_philo		*sleep_and_think(t_philo *p);
long int	curr_time(void);
void		observer(t_info *info, t_philo *philo);

#endif
