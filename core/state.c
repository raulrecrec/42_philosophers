/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 23:07:37 by rexposit          #+#    #+#             */
/*   Updated: 2025/10/15 00:05:39 by rexposit         ###   ########.fr       */
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

	if (get_dead(philo->data) == 1)
		return ;
	ms = now_ms() - philo->data->time_start;
	if (ms == -1)
		return ;
	pthread_mutex_lock(&philo->data->prints);
	printf("%lld %d %s\n", ms, philo->id, msg);
	pthread_mutex_unlock(&philo->data->prints);
}
