/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 18:27:36 by rexposit          #+#    #+#             */
/*   Updated: 2025/10/23 01:06:04 by rexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_err	init_mutexes_prints_death_meals(t_data *data)
{
	if (pthread_mutex_init(&data->prints, NULL) != 0)
	{
		ph_error(data, ERR_MUTEX_INIT);
		return (data->err);
	}
	if (pthread_mutex_init(&data->death, NULL) != 0)
	{
		pthread_mutex_destroy(&data->prints);
		ph_error(data, ERR_MUTEX_INIT);
		return (data->err);
	}
	if (pthread_mutex_init(&data->m_last_meal_ms, NULL) != 0)
	{
		pthread_mutex_destroy(&data->m_last_meal_ms);
		ph_error(data, ERR_MUTEX_INIT);
		return (data->err);
	}
	return (ERR_OK);
}

t_err	init_mutexes(t_data *data)
{
	int	i;

	if (init_mutexes_prints_death_meals(data) != ERR_OK)
		return (data->err);
	i = 0;
	while (i < data->total_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			i--;
			while (i >= 0)
			{
				pthread_mutex_destroy(&data->forks[i]);
				i--;
			}
			pthread_mutex_destroy(&data->death);
			pthread_mutex_destroy(&data->prints);
			ph_error(data, ERR_MUTEX_INIT);
			return (data->err);
		}
		i++;
	}
	return (ERR_OK);
}
