/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argscheck.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmajor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 12:05:08 by brmajor           #+#    #+#             */
/*   Updated: 2023/10/09 15:43:58 by brmajor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	error_handler(char *msg)
{
	printf("%s\n", msg);
	exit(1);
}

int	check_int(int ac, char **av)
{
	int		i;
	int		num;

	(void)ac;
	i = 1;
	while (av[i])
	{
		num = ft_atoi(av[i]);
		if (num == 0 && ft_strlen(av[i]) > 2)
			return (1);
		i++;
	}
	return (0);
}

int	check_digit(int ac, char **av)
{
	int	i;
	int	j;

	j = 1;
	while (j < ac)
	{
		i = 0;
		if (av[j][i] == '-' || av[j][i] == '+')
			i++;
		if (av[j][i] == '\0')
			return (1);
		while (av[j][i] != '\0')
		{
			if (!ft_isdigit(av[j][i]))
				return (1);
			i++;
		}
		j++;
	}
	return (0);
}

void	check_args(int ac, char **av)
{
	if (ac != 5 && ac != 6)
		error_handler("Error: number of arguments");
	if (check_int(ac, av) || check_digit(ac, av))
		error_handler("Error: arguments");
	if (ft_atoi(av[1]) == 1)
	{
		printf("0 1 has taken a fork\n%i 1 died\n", ft_atoi(av[2]));
		exit(0);
	}
}
