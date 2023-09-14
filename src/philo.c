/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmajor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 10:57:37 by brmajor           #+#    #+#             */
/*   Updated: 2023/09/13 16:14:40 by brmajor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_info	init_info(char **av)
{
	int		i;
	t_info	info;
	
	info.numofphilo = ft_atoi(av[1]);
	info.ttdie = ft_atoi(av[2]);
	info.tteat = ft_atoi(av[3]);
	info.ttsleep = ft_atoi(av[4]);
	if (av[5])
		info.numofmeals = ft_atoi(av[5]);
	else
		info.numofmeals = 0;
	i = 0;
	info.fork = malloc(sizeof(pthread_mutex_t) * info.numofphilo);
	if (!info.fork)
		error_handler("Error: forks malloc");
	while (i++ < info.numofphilo)
	{
		if (pthread_mutex_init(&info.fork[i - 1], NULL) != 0)
			error_handler("Error: mutex init");
	}
	return (info);
}

t_philo init_philo(t_info *info)
{
	t_philo philo;

	philo.dead = 0;
	philo.time_left = info->ttdie;
	philo.times_eaten = 0;
	philo.info = info;
	return (philo);
}

void	destroy_mutex(t_info *info)
{
	int		i;

	i = 0;
	while (i++ < info->numofphilo)
	{
		if (pthread_mutex_destroy(&info->fork[i - 1]) != 0)
			error_handler("Error: mutex destroy");
	}
}

int	main(int ac, char **av)
{
	t_info	info;
	t_philo philo;

	check_args(ac, av);
	info = init_info(av);
	philo = init_philo(&info);
	start_threads(&info, &philo);
	destroy_mutex(&info);
}
