/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 23:07:37 by rexposit          #+#    #+#             */
/*   Updated: 2025/11/15 18:34:46 by rexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_dead(t_data *data)
{
	int	state;

	pthread_mutex_lock(&data->death);
	state = data->dead;
	pthread_mutex_unlock(&data->death);
	return (state);
}

void	set_dead(t_data *data, int value)
{
	pthread_mutex_lock(&data->death);
	data->dead = value;
	pthread_mutex_unlock(&data->death);
}

void	print_status(t_philo *philo, const char *msg)
{
	long long	ms;

	pthread_mutex_lock(&philo->data->prints);
	if (get_dead(philo->data) && msg[0] != 'd')
	{
		pthread_mutex_unlock(&philo->data->prints);
		return ;
	}
	ms = now_ms() - philo->data->time_start;
	if (ms != -1)
		printf("%lld %d %s\n", ms, philo->id, msg);
	pthread_mutex_unlock(&philo->data->prints);
}
