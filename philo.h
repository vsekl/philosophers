/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjose <vjose@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 20:59:10 by vjose             #+#    #+#             */
/*   Updated: 2022/04/10 21:22:06 by vjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

# define TAKING_FORK 0
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DYING 4

typedef struct s_args
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	long			start_time;
	int				stop;
}t_args;

typedef struct s_philosophers{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*std_out;
	pthread_mutex_t	*death;
	t_args			*args;
	int				number_of_meals;
	long			death_time;
}t_philosophers;

typedef struct s_params
{
	t_args			*args;
	t_philosophers	*philosophers;
	pthread_mutex_t	*forks;
	pthread_t		*threads;
}t_params;

//init
int		init_params(t_params *params, int argc, char **argv);

//states
void	taking_forks(t_philosophers *philosophers);
void	eating(t_philosophers *philosophers);
void	sleeping(t_philosophers *philosophers);
void	thinking(t_philosophers *philosophers);
int		print_state(t_philosophers *philosophers, int state);

//utils
long	get_time(struct timeval time);
void	delay(int time_in_state);
long	time_diff(t_philosophers *philosophers);
int		ft_atoi(const char *str);
int		check_args(t_params *params, char **argv);
void	free_resources(t_params *params);
void	mem_free(t_params *params);

#endif