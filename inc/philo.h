/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmajor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 10:29:49 by brmajor           #+#    #+#             */
/*   Updated: 2023/09/13 16:14:29 by brmajor          ###   ########.fr       */
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
	int		numofphilo;
	int		ttdie;
	int		tteat;
	int		ttsleep;
	int		numofmeals;
	pthread_mutex_t *fork;
}	t_info;

typedef struct s_philo
{
	int		n;
	int		dead;
	int		time_left;
	int		times_eaten;
	t_info	*info;
	pthread_t thread_id;
}	t_philo;



void	error_handler(char *msg);
void	start_threads(t_info *info, t_philo *philo);
int		ft_atoi(const char *str);
int		ft_strlen(char *str);
int		ft_isdigit(int i);
void	check_args(int ac, char **av);


#endif
