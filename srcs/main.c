/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjose <vjose@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 21:01:01 by vjose             #+#    #+#             */
/*   Updated: 2022/04/10 21:22:26 by vjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	*simulation(void *args)
{
	t_philosophers	*philosophers;

	philosophers = (t_philosophers *)args;
	if (philosophers->id % 2 == 1)
	{
		taking_forks(philosophers);
		eating(philosophers);
	}
	pthread_mutex_lock(philosophers->std_out);
	while (philosophers->args->stop == 0)
	{
		pthread_mutex_unlock(philosophers->std_out);
		sleeping(philosophers);
		thinking(philosophers);
		taking_forks(philosophers);
		eating(philosophers);
		pthread_mutex_lock(philosophers->std_out);
	}
	pthread_mutex_unlock(philosophers->std_out);
	return (NULL);
}

static int	create_threads(t_params *params)
{
	int				i;
	struct timeval	start_time;

	i = 1;
	gettimeofday(&start_time, NULL);
	params->args->start_time = get_time(start_time);
	while (i <= params->args->number_of_philosophers)
	{
		if (pthread_create(&params->philosophers[i].thread, \
						NULL, simulation, &params->philosophers[i]) != 0)
		{
			pthread_mutex_lock(&params->forks[0]);
			printf("Thread creation error\n");
			return (1);
		}
		pthread_mutex_lock(params->philosophers[i].death);
		params->philosophers[i].death_time = params->args->start_time \
						+ params->philosophers[i].args->time_to_die;
		pthread_mutex_unlock(params->philosophers[i].death);
		i++;
	}
	return (0);
}

static int	check_philo(t_params *params, int i, int *counter)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	pthread_mutex_lock(params->philosophers[i].death);
	if (get_time(time) > params->philosophers[i].death_time)
	{
		print_state(&params->philosophers[i], DYING);
		pthread_mutex_unlock(params->philosophers[i].right_fork);
		return (1);
	}
	if (params->philosophers[i].number_of_meals == 0)
		(*counter)++;
	pthread_mutex_unlock(params->philosophers[i].death);
	return (0);
}

static int	checker(t_params *params)
{
	int				i;
	int				counter;

	i = 1;
	counter = 0;
	while (i <= params->args->number_of_philosophers)
	{
		if (check_philo(params, i, &counter) == 1)
			return (1);
		i++;
	}
	if (counter == params->args->number_of_philosophers)
	{
		pthread_mutex_lock(params->philosophers[1].std_out);
		params->args->stop = 1;
		pthread_mutex_unlock(params->philosophers[1].std_out);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_params	params;
	int			i;

	i = 1;
	if (init_params(&params, argc, argv) == 0)
	{
		if (create_threads(&params) == 0)
		{
			while (checker(&params) == 0)
			{
			}
		}
		while (i <= params.args->number_of_philosophers)
			pthread_join(params.philosophers[i++].thread, NULL);
		free_resources(&params);
	}
	return (0);
}
