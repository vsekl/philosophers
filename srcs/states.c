/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjose <vjose@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 20:52:46 by vjose             #+#    #+#             */
/*   Updated: 2022/04/10 21:25:27 by vjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	print_state(t_philosophers *philosophers, int state)
{
	long			time;

	pthread_mutex_lock(philosophers->std_out);
	if (philosophers->args->stop == 1)
	{
		pthread_mutex_unlock(philosophers->std_out);
		return (1);
	}
	time = time_diff(philosophers);
	if (state == TAKING_FORK)
		printf("%ld %d has taken a fork\n", time, philosophers->id);
	else if (state == EATING)
		printf("%ld %d is eating\n", time, philosophers->id);
	else if (state == SLEEPING)
		printf("%ld %d is sleeping\n", time, philosophers->id);
	else if (state == THINKING)
		printf("%ld %d is thinking\n", time, philosophers->id);
	else
	{
		printf("%ld %d died\n", time, philosophers->id);
		philosophers->args->stop = 1;
	}
	pthread_mutex_unlock(philosophers->std_out);
	return (0);
}

void	taking_forks(t_philosophers *philosophers)
{
	pthread_mutex_lock(philosophers->right_fork);
	if (print_state(philosophers, TAKING_FORK) == 1)
		return ;
	pthread_mutex_lock(philosophers->left_fork);
	print_state(philosophers, TAKING_FORK);
}

void	eating(t_philosophers *philosophers)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	if (print_state(philosophers, EATING) == 1)
		return ;
	pthread_mutex_lock(philosophers->death);
	philosophers->death_time = get_time(time) + \
										philosophers->args->time_to_die;
	pthread_mutex_unlock(philosophers->death);
	delay(philosophers->args->time_to_eat);
	pthread_mutex_lock(philosophers->death);
	if (philosophers->number_of_meals > 0)
		philosophers->number_of_meals--;
	pthread_mutex_unlock(philosophers->death);
	pthread_mutex_unlock(philosophers->left_fork);
	pthread_mutex_unlock(philosophers->right_fork);
}

void	sleeping(t_philosophers *philosophers)
{
	if (print_state(philosophers, SLEEPING) == 1)
		return ;
	delay(philosophers->args->time_to_sleep);
}

void	thinking(t_philosophers *philosophers)
{
	print_state(philosophers, THINKING);
}
