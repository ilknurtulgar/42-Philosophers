/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:45:38 by itulgar           #+#    #+#             */
/*   Updated: 2024/09/03 20:19:00 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	include_input(t_philo *philo, char **argv)
{
	philo->time_to_die = ft_itatoi(argv[2]);
	philo->time_to_eat = ft_itatoi(argv[3]);
	philo->time_to_sleep = ft_itatoi(argv[4]);
	if (argv[5])
		philo->need_to_eat = ft_itatoi(argv[5]);
	else
		philo->need_to_eat = -1;
}

void	init_philo(t_philo *philo, t_program *program, pthread_mutex_t *forks,
		char **argv)
{
	int	i;

	i = 0;
	while (i < ft_itatoi(argv[1]))
	{
		philo[i].id = i + 1;
		include_input(&philo[i], argv);
		philo[i].eat_count = 0;
		philo[i].start_time = timenow();
		philo[i].last_eat_time = timenow();
		philo[i].l_fork = &forks[i];
		philo[i].eat_done = 0;
		philo[i].data = program;
		if (i == 0)
			philo[i].r_fork = &forks[philo[i].data->philo_num - 1];
		else
			philo[i].r_fork = &forks[i - 1];
		i++;
	}
}

void	init_forks(pthread_mutex_t *forks, int p_count)
{
	int	i;

	i = 0;
	while (i < p_count)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_program(t_program *program, t_philo *philo, char **argv)
{
	program->philo = philo;
	program->is_dead = 0;
	program->philo_num = ft_itatoi(argv[1]);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->eat_lock, NULL);
	pthread_mutex_init(&program->check_lock, NULL);
	pthread_mutex_init(&program->need_lock, NULL);
}
