/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 14:12:21 by itulgar           #+#    #+#             */
/*   Updated: 2024/09/04 16:56:36 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_program		*program;
	pthread_mutex_t	forks[PHILO_MAX];
	t_philo			philo[PHILO_MAX];

	if (!(argc == 5 || argc == 6))
		return (error_message("Unvalid argc"));
	if (!check_arg(argv))
		return (error_message("Unvalid arg"));
	if (argv[5] != NULL && ft_itatoi(argv[5]) == 0)
		return (0);
	program = malloc(sizeof(t_program));
	init_program(program, philo, argv);
	init_forks(forks, ft_itatoi(argv[1]));
	program->philo = malloc(sizeof(t_philo) * (program->philo_num));
	init_philo(program->philo, program, forks, argv);
	thread_create(program->philo);
	destroy_program(program, program->philo, forks);
	return (0);
}
