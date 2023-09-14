/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmajor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 13:05:14 by brmajor           #+#    #+#             */
/*   Updated: 2023/09/13 16:26:45 by brmajor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long int	curr_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	*philo_behavior(void *philo)
{
	t_philo	*p;

	p = philo;

	pthread_mutex_lock(&p->info->fork[p->n]);
	pthread_mutex_lock(&p->info->fork[p->n - 1]);

	eating(p);

	pthread_mutex_unlock(&p->info->fork[p->n]);
	pthread_mutex_unlock(&p->info->fork[p->n - 1]);

	sleep_and_think(p);

	return (philo);
}

void	start_threads(t_info *info, t_philo *philo)
{
	int		i;
	pthread_t	curr_thread[info->numofphilo];

	i = 0;
	while (i++ < info->numofphilo)
	{
		printf("%i\n", i);
		philo->n = i;
		philo->thread_id = curr_thread[i];
		if (pthread_create(&curr_thread[i], NULL, philo_behavior, philo) != 0)
			error_handler("Error: creating thread");
	}
	i = 0;
	while (i++ < info->numofphilo)
		pthread_join(curr_thread[i], NULL);
}
