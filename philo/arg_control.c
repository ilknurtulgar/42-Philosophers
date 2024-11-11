/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:07:20 by itulgar           #+#    #+#             */
/*   Updated: 2024/09/04 16:56:25 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	isdigit(char str)
{
	return (str >= '0' && str <= '9');
}

static int	numeric_control(char **argv)
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!isdigit(argv[i][j]) && argv[i][j - 1] == '\0'
				&& argv[i][j] != '+')
				return (0);
			if (!isdigit(argv[i][j]) && (argv[i][j - 1] != '\0'
					|| !isdigit(argv[i][j + 1])))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_arg(char **argv)
{
	if (ft_itatoi(argv[1]) > 200 || ft_itatoi(argv[1]) <= 0
		|| ft_itatoi(argv[2]) <= 0 || ft_itatoi(argv[3]) <= 0
		|| ft_itatoi(argv[4]) <= 0 || (argv[5] && ft_itatoi(argv[5]) <= 0))
		return (0);
	if (!numeric_control(argv))
		return (0);
	return (1);
}
