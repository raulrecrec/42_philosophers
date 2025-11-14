/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 22:00:18 by rexposit          #+#    #+#             */
/*   Updated: 2025/11/14 22:07:33 by rexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_last_meal_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->total_philos)
	{
		pthread_mutex_lock(&data->m_last_meal_ms);
		data->philos[i].last_meal_ms = data->time_start;
		pthread_mutex_unlock(&data->m_last_meal_ms);
		i++;
	}
}

static int	create_philo_threads(t_data *data, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < data->total_philos)
	{
		if (pthread_create(&threads[i], NULL, philo_routine,
				&data->philos[i]) != 0)
		{
			ph_error(data, ERR_THREAD_CREATE);
			set_dead(data, 1);
			i--;
			while (i >= 0)
			{
				pthread_join(threads[i], NULL);
				i--;
			}
			destroy_forks(data);
			destroy_globals(data);
			free_arrays(data);
			free(threads);
			return (data->err);
		}
		i++;
	}
	return (ERR_OK);
}

static int	create_monitor_thread(t_data *data, pthread_t *threads,
	pthread_t *monitor)
{
	int	i;

	if (pthread_create(monitor, NULL, monitor_routine, data) != 0)
	{
		ph_error(data, ERR_THREAD_CREATE);
		set_dead(data, 1);
		i = 0;
		while (i < data->total_philos)
		{
			pthread_join(threads[i], NULL);
			i++;
		}
		destroy_forks(data);
		destroy_globals(data);
		free_arrays(data);
		free(threads);
		return (data->err);
	}
	return (ERR_OK);
}

int	create_threads_and_monitor(t_data *data, pthread_t **threads,
	pthread_t *monitor)
{
	*threads = NULL;
	init_last_meal_all(data);
	*threads = ph_malloc(data,
			data->total_philos * sizeof(pthread_t));
	if (*threads == NULL)
	{
		destroy_forks(data);
		destroy_globals(data);
		free_arrays(data);
		return (data->err);
	}
	if (create_philo_threads(data, *threads) != ERR_OK)
		return (data->err);
	if (create_monitor_thread(data, *threads, monitor) != ERR_OK)
		return (data->err);
	return (ERR_OK);
}
