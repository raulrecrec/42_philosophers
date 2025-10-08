/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:48:18 by rexposit          #+#    #+#             */
/*   Updated: 2025/10/08 14:09:45 by rexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	data_init(t_data *data)
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

t_err	data_set(t_data *data, int index, long long value)
{
	if ((index == 1 || index == 5) && value > INT_MAX)
	{
		ph_error(data, ERR_RANGE);
		return (data->err);
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
	return (ERR_OK);
}

t_err	parser_and_validate_arguments(t_data *data, int argc, char **argv)
{
	int			i;
	long long	value;
	t_err		status;

	i = 1;
	while (i < argc)
	{
		value = ph_atoll(data, argv[i]);
		if (value > 0)
		{
			status = data_set(data, i, value);
			if (status != ERR_OK)
				return (status);
		}
		else
			return (data->err);
		i++;
	}
	return (ERR_OK);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		printf("Invalid arguments.\nCorrect format "
			"(last one is optional and only positive integers > 0): "
			"<number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> "
			"[number_of_times_each_philosopher_must_eat]\n");
		return (ERR_ARGS);
	}
	data_init(&data);
}
