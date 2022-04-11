/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjose <vjose@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 22:24:43 by vjose             #+#    #+#             */
/*   Updated: 2022/04/10 22:24:47 by vjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	get_time(struct timeval time)
{
	return (time.tv_sec * 1000000 + time.tv_usec);
}

void	delay(int time_in_state)
{
	struct timeval	start;
	struct timeval	time;

	gettimeofday(&start, NULL);
	gettimeofday(&time, NULL);
	while ((get_time(start) + time_in_state) > get_time(time))
	{
		usleep(500);
		gettimeofday(&time, NULL);
	}
}

long	time_diff(t_philosophers *philosophers)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((get_time(time) - philosophers->args->start_time) / 1000);
}
