/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:35:50 by itulgar           #+#    #+#             */
/*   Updated: 2024/09/03 18:12:23 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	iii_sleeping(t_philo *philo)
{
	print_message(philo, philo->id, "is sleeping");
	i_sleep(philo, philo->time_to_sleep);
	return ;
}

static void	thinking(t_philo *philo)
{
	print_message(philo, philo->id, "is thinking");
	return ;
}

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_message(philo, philo->id, "has taken a fork");
	pthread_mutex_lock(philo->l_fork);
	print_message(philo, philo->id, "has taken a fork");
	print_message(philo, philo->id, "is eating");
	pthread_mutex_lock(&philo->data->eat_lock);
	philo->last_eat_time = timenow();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->data->eat_lock);
	i_sleep(philo, philo->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

static void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo[0].data->philo_num == 1)
	{
		pthread_mutex_lock(philo->r_fork);
		print_message(philo, philo->id, "has taken a fork");
		pthread_mutex_unlock(philo->r_fork);
		philo->data->is_dead = 1;
		i_dieorlife(philo);
		return (arg);
	}
	if (philo->id % 2 == 0)
		i_sleep(philo, 1);
	while (i_dieorlife(philo))
	{
		eating(philo);
		iii_sleeping(philo);
		thinking(philo);
	}
	return (arg);
}

int	thread_create(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].data->philo_num)
	{
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]) != 0)
			return (-1);
		i++;
	}
	check_thread(philo);
	i = 0;
	while (i < philo->data->philo_num)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (-1);
		i++;
	}
	return (1);
}
