/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjose <vjose@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 21:12:15 by vjose             #+#    #+#             */
/*   Updated: 2022/04/09 21:23:35 by vjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	init_arguments(int argc, char **argv, t_params *params)
{
	if (argc > 6 || argc < 5)
	{
		printf("Wrong number of arguments\n");
		return (1);
	}
	params->args = malloc(sizeof(t_args));
	if (params->args == NULL)
	{
		printf("Memory allocation error\n");
		return (1);
	}
	params->args->number_of_philosophers = ft_atoi(argv[1]);
	params->args->time_to_die = ft_atoi(argv[2]) * 1000;
	params->args->time_to_eat = ft_atoi(argv[3]) * 1000;
	params->args->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argv[5] != NULL)
		params->args->number_of_meals = ft_atoi(argv[5]);
	else
		params->args->number_of_meals = -1;
	params->args->stop = 0;
	return (check_args(params, argv));
}

static int	init_forks(t_params *params)
{
	int	i;
	int	n;

	i = 0;
	n = params->args->number_of_philosophers * 2 + 1;
	params->forks = malloc(sizeof(pthread_mutex_t) * (n));
	if (params->forks == NULL)
	{
		printf("Memory allocation error\n");
		mem_free(params);
		return (1);
	}
	while (i < n)
	{
		if (pthread_mutex_init(&params->forks[i++], NULL) != 0)
		{
			printf("Mutex initialization error\n");
			mem_free(params);
			return (1);
		}
	}
	return (0);
}

static void	set_philosophers(t_params *params)
{
	int	i;
	int	n;

	i = 1;
	n = params->args->number_of_philosophers;
	while (i <= n)
	{
		params->philosophers[i].id = i;
		params->philosophers[i].thread = params->threads[i];
		params->philosophers[i].left_fork = &params->forks[i];
		params->philosophers[i].right_fork = &params->forks[i - 1];
		params->philosophers[i].std_out = &params->forks[0];
		params->philosophers[i].death = &params->forks[i + n];
		params->philosophers[i].args = params->args;
		params->philosophers[i].number_of_meals = params->args->number_of_meals;
		i++;
	}
	params->philosophers[1].right_fork = &params->forks[n];
}

static int	init_philosophers(t_params *params)
{
	int	n;

	n = params->args->number_of_philosophers;
	params->philosophers = malloc(sizeof(t_philosophers) * (n + 1));
	if (params->philosophers == NULL)
	{
		printf("Memory allocation error\n");
		mem_free(params);
		return (1);
	}
	params->threads = malloc(sizeof(pthread_t) * (n + 1));
	if (params->threads == NULL)
	{
		printf("Memory allocation error\n");
		mem_free(params);
		return (1);
	}
	set_philosophers(params);
	return (0);
}

int	init_params(t_params *params, int argc, char **argv)
{
	if (init_arguments(argc, argv, params) == 1)
		return (1);
	if (init_forks(params) == 1)
		return (1);
	if (init_philosophers(params) == 1)
		return (1);
	return (0);
}
