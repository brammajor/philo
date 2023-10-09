/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   behavior.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmajor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:39:28 by brmajor           #+#    #+#             */
/*   Updated: 2023/10/09 16:46:54 by brmajor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	eat(t_philo *p)
{
	if ((curr_time() - p->last_meal) >= p->info->ttdie)
		p->dead = 1;
	else
	{
		printf("%ld %i is eating\n", (curr_time() - p->start_time), p->n);
		p->last_meal = curr_time();
		usleep(p->info->tteat * 1000);
		p->times_eaten++;
	}
}

void	sleep_and_think(t_philo *p)
{
	printf("%ld %i is sleeping\n", (curr_time() - p->start_time), p->n);
	usleep(p->info->ttsleep * 1000);
	printf("%ld %i is thinking\n", (curr_time() - p->start_time), p->n);
}

void	lock_forks(t_philo *p)
{
	pthread_mutex_lock(&p->info->fork[p->n - 1]);
	printf("%ld %i has taken a fork\n", (curr_time() - p->start_time), p->n);
	if (p->n < p->info->numofphilo)
		pthread_mutex_lock(&p->info->fork[p->n]);
	else
		pthread_mutex_lock(&p->info->fork[0]);
	printf("%ld %i has taken a fork\n", (curr_time() - p->start_time), p->n);
}

void	unlock_forks(t_philo *p)
{
	pthread_mutex_unlock(&p->info->fork[p->n - 1]);
	if (p->n < p->info->numofphilo)
		pthread_mutex_unlock(&p->info->fork[p->n]);
	else
		pthread_mutex_unlock(&p->info->fork[0]);
}

int	observer(t_philo *p)
{
	if (p->dead == 1)
		return (1);
	if (p->times_eaten == p->info->numofmeals)
		return (2);
	return (0);
}
