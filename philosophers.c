/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:48:18 by rexposit          #+#    #+#             */
/*   Updated: 2025/10/23 01:03:01 by rexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	data_init(t_data *data)
{
	data->total_philos = 0;
	data->time_die = 0;
	data->time_eat = 0;
	data->time_sleep = 0;
	data->must_eat = -1;
	data->time_start = 0;
	data->dead = 0;
	data->forks = NULL;
	data->philos = NULL;
	data->err = ERR_OK;
}

static void	data_set(t_data *data, int index, long long value)
{
	if ((index == 1 || index == 5) && value > INT_MAX)
	{
		ph_error(data, ERR_RANGE);
		return ;
	}
	if (index == 1)
		data->total_philos = value;
	else if (index == 2)
		data->time_die = value;
	else if (index == 3)
		data->time_eat = value;
	else if (index == 4)
		data->time_sleep = value;
	else if (index == 5)
		data->must_eat = value;
}

static void
	parser_and_validate_arguments(t_data *data, int argc, char **argv)
{
	int			i;
	long long	value;

	i = 1;
	while (i < argc)
	{
		value = ph_atoll(data, argv[i]);
		if (data->err != ERR_OK)
			return ;
		if (value > 0)
			data_set(data, i, value);
		else
		{
			ph_error(data, ERR_RANGE);
			return ;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	*threads;
	pthread_t	monitor;
	int			i;
	int			j;

	if (argc < 5 || argc > 6)
	{
		printf("Invalid arguments.\nCorrect format "
			"(last one is optional and only positive integers > 0): "
			"<number_of_philosophers> <time_to_die> <time_to_eat> "
			"<time_to_sleep> [number_of_times_each_philosopher_must_eat]\n");
		return (ERR_ARGS);
	}
	data_init(&data);
	parser_and_validate_arguments(&data, argc, argv);
	if (data.err != ERR_OK)
		return (data.err);
	if (setup_alloc(&data) != ERR_OK)
		return (data.err);
	if (init_mutexes(&data) != ERR_OK)
	{
		free_arrays(&data);
		return (data.err);
	}
	init_philos(&data);
	data.time_start = now_ms();
	i = 0;
	while (i < data.total_philos)
	{
		pthread_mutex_lock(&data.m_last_meal_ms);
		data.philos[i].last_meal_ms = data.time_start;
		pthread_mutex_unlock(&data.m_last_meal_ms);
		i++;
	}
	threads = ph_malloc(&data, data.total_philos * sizeof(pthread_t));
	if (threads == NULL)
	{
		destroy_forks(&data);
		destroy_globals(&data);
		free_arrays(&data);
		return (data.err);
	}
	i = 0;
	while (i < data.total_philos)
	{
		if (pthread_create(&threads[i], NULL, philo_routine, &data.philos[i]) != 0)
		{
			ph_error(&data, ERR_THREAD_CREATE);
			set_dead(&data, 1);
			j = i - 1;
			while (j >= 0)
			{
				pthread_join(threads[j], NULL);
				j--;
			}
			destroy_forks(&data);
			destroy_globals(&data);
			free_arrays(&data);
			free(threads);
			return (data.err);
		}
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_routine, &data) != 0)
	{
		ph_error(&data, ERR_THREAD_CREATE);
		set_dead(&data, 1);
		i = 0;
		while (i < data.total_philos)
		{
			pthread_join(threads[i], NULL);
			i++;
		}
		destroy_forks(&data);
		destroy_globals(&data);
		free_arrays(&data);
		free(threads);
		return (data.err);
	}
	cleanup_after_sim(&data, threads, monitor);
	free(threads);
	return (data.err);
}
