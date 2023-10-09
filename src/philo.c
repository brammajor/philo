/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmajor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 10:57:37 by brmajor           #+#    #+#             */
/*   Updated: 2023/10/09 16:40:17 by brmajor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	destroy_mutex(t_info *info)
{
	int		i;

	i = 0;
	while (i < info->numofphilo)
	{
		pthread_mutex_destroy(&info->fork[i]);
		i++;
	}
	free(info);
}

void	init_info(t_info *info, char **av)
{
	info->numofphilo = ft_atoi(av[1]);
	info->ttdie = ft_atoi(av[2]);
	info->tteat = ft_atoi(av[3]);
	info->ttsleep = ft_atoi(av[4]);
	if (av[5])
		info->numofmeals = ft_atoi(av[5]);
	else
		info->numofmeals = -1;
	info->fork = malloc(sizeof(pthread_mutex_t) * info->numofphilo);
	if (!info->fork)
		error_handler("Error: malloc forks");
}

int	main(int ac, char **av)
{
	t_info	*info;

	info = (t_info *)malloc(sizeof(t_info *));
	if (!info)
		error_handler("Error: malloc info");
	check_args(ac, av);
	init_info(info, av);
	start_threads(info);
	destroy_mutex(info);
}
