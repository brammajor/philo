/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   behavior.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmajor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:39:28 by brmajor           #+#    #+#             */
/*   Updated: 2023/10/04 15:51:52 by brmajor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_philo	*eat(t_philo *p)
{
	p->eating = 1;
	p->times_eaten++;
	if ((curr_time() - p->last_meal) >= p->info->ttdie)
		p->dead = 1;
	else
	{
		printf("%ld %i is eating\n", (curr_time() - p->start_time), p->n);
		usleep(p->info->tteat * 1000);
		p->last_meal = curr_time();
	}
	p->eating = 0;
	return (p);
}

t_philo	*sleep_and_think(t_philo *p)
{
	printf("%ld %i is sleeping\n", (curr_time() - p->start_time), p->n);
	usleep(p->info->ttsleep * 1000);
	printf("%ld %i is thinking\n", (curr_time() - p->start_time), p->n);
	return (p);
}

void	observer(t_info *info, t_philo *p)
{
	int		i;
	int		done;

	i = 0;
	done = 0;
	while (1)
	{
		while (i < info->numofphilo && done < info->numofphilo)
		{
			if (p[i].dead == 1 && p[i].eating != 1)
			{
				i = 0;
				while (i < info->numofphilo)
				{
					pthread_detach(p[i].thread_id);
					i++;
				}
				printf("%ld %i died\n", (curr_time() - p[i].start_time), p[i].n);
				return ;
			}

			if (p[i].times_eaten == info->numofmeals)
			{
				pthread_join(p[i].thread_id, NULL);
				done++;
				if (done == info->numofphilo)
					return;
			}
			i++;
		}
		i = 0;
	}
}

