/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 14:07:34 by itulgar           #+#    #+#             */
/*   Updated: 2024/09/03 18:11:55 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define PHILO_MAX 200

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int					id;
	int					need_to_eat;
	size_t				time_to_eat;
	size_t				time_to_die;
	size_t				time_to_sleep;
	size_t				start_time;
	size_t				last_eat_time;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
	int					eat_count;
	pthread_t			thread;
	struct s_program	*data;
	int					eat_done;

}						t_philo;

typedef struct s_program
{
	int					philo_num;
	t_philo				*philo;
	pthread_mutex_t		eat_lock;
	pthread_mutex_t		check_lock;
	pthread_mutex_t		need_lock;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		write_lock;
	int					is_dead;
}						t_program;

int						error_message(char *str);
int						check_arg(char **argv);
int						ft_itatoi(char *str);
void					init_program(t_program *program, t_philo *philo,
							char **argv);
void					init_forks(pthread_mutex_t *forks, int p_count);
void					init_philo(t_philo *philo, t_program *program,
							pthread_mutex_t *forks, char **argv);
size_t					timenow(void);
int						thread_create(t_philo *philo);
void					print_message(t_philo *philo, int id, char *state);
void					i_sleep(t_philo *philo, size_t i_time);
void					destroy_program(t_program *program, t_philo *philo,
							pthread_mutex_t *forks);
int						i_dieorlife(t_philo *philo);
void					*check_thread(void *arg);

#endif