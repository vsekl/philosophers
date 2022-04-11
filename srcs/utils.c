/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjose <vjose@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 20:51:24 by vjose             #+#    #+#             */
/*   Updated: 2022/04/08 16:02:35 by vjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi(const char *str)
{
	long		result;
	int			i;

	result = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (result > INT_MAX || result < INT_MIN)
		return (-1);
	return (result);
}

int	check_args(t_params *params, char **argv)
{
	if (params->args->number_of_philosophers < 1 \
	|| params->args->time_to_die < 0 \
	|| params->args->time_to_eat < 0 \
	|| params->args->time_to_sleep < 0 \
	|| (argv[5] != NULL && params->args->number_of_meals < 0))
	{
		printf("Invalid arguments\n");
		mem_free(params);
		return (1);
	}
	return (0);
}

void	free_resources(t_params *params)
{
	int	i;
	int	n;

	i = 1;
	n = params->args->number_of_philosophers;
	while (i < n)
	{
		pthread_mutex_unlock(params->philosophers[i].left_fork);
		pthread_mutex_destroy(params->philosophers[i].left_fork);
		pthread_mutex_unlock(params->philosophers[i].death);
		pthread_mutex_destroy(params->philosophers[i].death);
		i++;
	}
	pthread_mutex_unlock(params->philosophers[1].std_out);
	pthread_mutex_destroy(params->philosophers[1].std_out);
	mem_free(params);
}

void	mem_free(t_params *params)
{
	if (params->args != NULL)
		free(params->args);
	if (params->forks != NULL)
		free(params->forks);
	if (params->philosophers != NULL)
		free(params->philosophers);
	if (params->threads != NULL)
		free(params->threads);
}
