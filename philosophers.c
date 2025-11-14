/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:48:18 by rexposit          #+#    #+#             */
/*   Updated: 2025/11/14 21:55:53 by rexposit         ###   ########.fr       */
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

static int	init_program(t_data *data, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Invalid arguments.\nCorrect format "
			"(last one is optional and only positive integers > 0): "
			"<number_of_philosophers> <time_to_die> <time_to_eat> "
			"<time_to_sleep> [number_of_times_each_philosopher_must_eat]\n");
		data->err = ERR_ARGS;
		return (data->err);
	}
	data_init(data);
	parser_and_validate_arguments(data, argc, argv);
	if (data->err != ERR_OK)
		return (data->err);
	if (setup_alloc(data) != ERR_OK)
		return (data->err);
	if (init_mutexes(data) != ERR_OK)
	{
		free_arrays(data);
		return (data->err);
	}
	init_philos(data);
	data->time_start = now_ms();
	return (data->err);
}

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	*threads;
	pthread_t	monitor;

	if (init_program(&data, argc, argv) != ERR_OK)
		return (data.err);
	if (create_threads_and_monitor(&data, &threads, &monitor) != ERR_OK)
		return (data.err);
	cleanup_after_sim(&data, threads, monitor);
	free(threads);
	return (data.err);
}
