/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:45:05 by itulgar           #+#    #+#             */
/*   Updated: 2024/09/03 18:12:05 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_need_eat(t_philo *philo)
{
	int	i;
	int	check_num;

	check_num = 0;
	i = 0;
	if (philo->need_to_eat == -1)
		return (1);
	while (i < philo[0].data->philo_num)
	{
		pthread_mutex_lock(&philo[i].data->eat_lock);
		if (philo[i].need_to_eat <= philo[i].eat_count)
			check_num++;
		pthread_mutex_unlock(&philo[i].data->eat_lock);
		i++;
	}
	if (check_num == philo[0].data->philo_num)
	{
		pthread_mutex_lock(&philo[0].data->need_lock);
		philo[0].eat_done = 1;
		pthread_mutex_unlock(&philo[0].data->need_lock);
		return (0);
	}
	return (1);
}

int	i_dieorlife(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_lock);
	pthread_mutex_lock(&philo->data->need_lock);
	if (philo->data->is_dead == 1 || philo->data->philo[0].eat_done == 1)
	{
		pthread_mutex_unlock(&philo->data->dead_lock);
		pthread_mutex_unlock(&philo->data->need_lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->need_lock);
	pthread_mutex_unlock(&philo->data->dead_lock);
	return (1);
}

static int	check_eat(t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->eat_lock);
	time = timenow();
	if (time - philo->last_eat_time >= philo->time_to_die)
	{
		pthread_mutex_unlock(&philo->data->eat_lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->eat_lock);
	return (1);
}

static int	is_died(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].data->philo_num)
	{
		if (!check_eat(&philo[i]))
		{
			pthread_mutex_lock(&philo->data->dead_lock);
			philo->data->is_dead = 1;
			pthread_mutex_unlock(&philo->data->dead_lock);
			print_message(philo, philo->id, "died");
			return (0);
		}
		i++;
	}
	return (1);
}

void	*check_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (!is_died(philo) || !is_need_eat(philo))
			break ;
	}
	return (arg);
}
