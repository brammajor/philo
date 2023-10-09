/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmajor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 10:29:49 by brmajor           #+#    #+#             */
/*   Updated: 2023/10/09 17:33:57 by brmajor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>
# include <pthread.h>

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
	int				n;
	int				dead;
	int				times_eaten;
	long int		start_time;
	long int		last_meal;
	pthread_t		thread_id;
	t_info			*info;
}	t_philo;

void	check_args(int ac, char **av);
void	error_handler(char *msg);

//behavior.c
void	eat(t_philo *p);
void	sleep_and_think(t_philo *p);
void	lock_forks(t_philo *p);
void	unlock_forks(t_philo *p);
int		observer(t_philo *p);

//philo.c
void	init_info(t_info *info, char **av);

//threading.c
void	start_threads(t_info *info);
void	*philo_behavior(void *arg);

//ft_atoi.c
int		ft_atoi(const char *str);

//utils.c
long	curr_time(void);
int		ft_strlen(char *str);
int		ft_isdigit(int i);

#endif
