/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmajor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 13:05:14 by brmajor           #+#    #+#             */
/*   Updated: 2023/10/04 15:26:47 by brmajor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	lock_forks(t_philo *p)
{
	t_info *info;

	info = p->info;
	pthread_mutex_lock(&info->fork[p->n - 1]);
	printf("%ld %i has taken a fork\n", (curr_time() - p->start_time), p->n);
	if (p->n < info->numofphilo)
		pthread_mutex_lock(&info->fork[p->n]);
	else
		pthread_mutex_lock(&info->fork[0]);
	printf("%ld %i has taken a fork\n", (curr_time() - p->start_time), p->n);
}

void	unlock_forks(t_philo *p)
{
	t_info	*info;

	info = p->info;
	pthread_mutex_unlock(&info->fork[p->n - 1]);
	if (p->n < info->numofphilo)
		pthread_mutex_unlock(&info->fork[p->n]);
	else
		pthread_mutex_unlock(&info->fork[0]);
}

void	*philo_behavior(void *arg)
{
	t_philo *p;

	p = (t_philo *)arg;
	while (1)
	{
		if (p->n % 2 == 0)
			usleep(10);
		lock_forks(p);		
		p = eat(p);
		unlock_forks(p);
		if (p->times_eaten == p->info->numofmeals)
			break ;
		p = sleep_and_think(p);
	}
	return (arg);
}

t_philo	*start_threads(t_info *info, t_philo *philo)
{
	int			i;
	long int	time;

	i = 0;
	philo = (t_philo *)malloc(sizeof(t_philo) * info->numofphilo);
	time = curr_time();
	while (i < info->numofphilo)
	{
		philo[i] = init_philo(info);
		philo[i].n = i + 1;
		philo[i].start_time = time;
		philo[i].last_meal = time;
		if (pthread_create(&philo[i].thread_id, NULL, philo_behavior, (void *)&philo[i]) != 0)
			error_handler("Error: creating thread");
		i++;
		usleep(50);
	}
	return (philo);
}
