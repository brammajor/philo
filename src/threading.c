/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmajor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 13:05:14 by brmajor           #+#    #+#             */
/*   Updated: 2023/10/09 15:44:16 by brmajor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	detatch_all(t_philo *p)
{
	int		i;

	i = 0;
	while (i < p->info->numofphilo)
	{
		pthread_detach(p[i].thread_id);
		i++;
	}
}

void	init_philo(t_info *info, t_philo *p, int i, long int time)
{
		p[i].info = info;
		p[i].n = i + 1;
		p[i].dead = 0;
		p[i].times_eaten = 0;
		p[i].start_time = time;
		p[i].last_meal = time;
}

void	*philo_behavior(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	while (1)
	{
		if (p->n % 2 == 0)
			usleep(50);
		lock_forks(p);
		eat(p);
		unlock_forks(p);
		if (p->times_eaten == p->info->numofmeals || p->dead == 1)
			break ;
		sleep_and_think(p);
	}
	return (arg);
}

void	start_threads(t_info *info)
{
	int			i;
	long int	time;
	t_philo		p[info->numofphilo];
	int			status;

	i = 0;
	time = curr_time();
	while (i < info->numofphilo)
	{
		init_philo(info, p, i, time);
		if (pthread_create(&p[i].thread_id, NULL,
					philo_behavior, (void *)&p[i]) != 0)
			error_handler("Error: creating thread");
		i++;
		usleep(50);
	}
	while (1)
	{
		if (i >= info->numofphilo)
			i = 0;
		status = observer(&p[i]);
		if (status == 1)
		{
			detatch_all(p);
			printf("%ld %i died\n", (curr_time() - p[i].start_time), p[i].n);
			return ;
		}
		else if (status == 2)
		{
			pthread_join(p[i].thread_id, NULL);
			return ;
		}
		i++;
	}
}
