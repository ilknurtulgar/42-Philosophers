/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 14:56:09 by itulgar           #+#    #+#             */
/*   Updated: 2024/09/04 16:56:44 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	i_sleep(t_philo *philo, size_t i_time)
{
	size_t	start_time;

	start_time = timenow();
	while ((timenow() - start_time) < i_time)
	{
		if (!i_dieorlife(philo))
			return ;
		usleep(500);
	}
}

void	print_message(t_philo *philo, int id, char *state)
{
	size_t		time;
	static int	i = 0;

	pthread_mutex_lock(&philo->data->need_lock);
	if (philo->data->philo[0].eat_done == 1)
	{
		pthread_mutex_unlock(&philo->data->need_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->data->need_lock);
	pthread_mutex_lock(&philo->data->write_lock);
	time = (timenow() - philo->start_time);
	if (i_dieorlife(philo))
	{
		printf("%zu %d %s\n", time, id, state);
		pthread_mutex_unlock(&philo->data->write_lock);
		return ;
	}
	else if (!i)
	{
		printf("%zu %d %s\n", time, id, state);
		i = 1;
	}
	pthread_mutex_unlock(&philo->data->write_lock);
}

int	error_message(char *str)
{
	return (printf("<< Error: %s honey>>\n", str));
}

size_t	timenow(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		error_message("gettime");
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_itatoi(char *str)
{
	int		i;
	long	result;

	result = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result);
}
