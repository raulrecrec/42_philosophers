/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 03:07:05 by rexposit          #+#    #+#             */
/*   Updated: 2025/10/23 01:07:05 by rexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_forks(t_data *data)
{
	int	i;

	if (data->forks == NULL)
		return ;
	i = 0;
	while (i < data->total_philos)
	{
		if (pthread_mutex_destroy(&data->forks[i]) != 0)
			ph_error(data, ERR_MUTEX_DESTROY);
		i++;
	}
}

void	destroy_globals(t_data *data)
{
	if (pthread_mutex_destroy(&data->death) != 0)
		ph_error(data, ERR_MUTEX_DESTROY);
	if (pthread_mutex_destroy(&data->prints) != 0)
		ph_error(data, ERR_MUTEX_DESTROY);
	if (pthread_mutex_destroy(&data->m_last_meal_ms) != 0)
		ph_error(data, ERR_MUTEX_DESTROY);
}

void	free_arrays(t_data *data)
{
	free(data->philos);
	data->philos = NULL;
	free(data->forks);
	data->forks = NULL;
}

void	cleanup_after_sim(t_data *data, pthread_t *thread, pthread_t monitor)
{
	int	i;

	pthread_join(monitor, NULL);
	i = 0;
	if (thread != NULL)
	{
		while (i < data->total_philos)
		{
			pthread_join(thread[i], NULL);
			i++;
		}
	}
	destroy_forks(data);
	destroy_globals(data);
	free_arrays(data);
}
