/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:38:00 by rexposit          #+#    #+#             */
/*   Updated: 2025/10/21 05:21:42 by rexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	scan_deaths(t_data *data, t_philo *philo, long long now)
{
	long long	last_meal;

	pthread_mutex_lock(&data->death);
	last_meal = philo->last_meal_ms;
	pthread_mutex_unlock(&data->death);
	if (now - last_meal >= data->time_die)
	{
		print_status(philo, "died");
		set_dead(data, 1);
		return (-1);
	}
	else
		return (0);
}

static int	check_all_full(t_data *data)
{
	int		count;
	int		i;
	t_philo	*philo;

	count = 0;
	i = 0;
	while (i < data->total_philos)
	{
		philo = &data->philos[i];
		if (philo->times_eaten >= data->must_eat)
			count++;
		i++;
	}
	if (count == data->total_philos)
	{
		set_dead(data, 1);
		return (-1);
	}
	else
		return (0);
}

void	*monitor_routine(void *arg)
{
	int			i;
	long long	now;
	t_data		*data;
	t_philo		*philo;

	data = (t_data *)arg;
	while (get_dead(data) == 0)
	{
		i = 0;
		now = now_ms();
		while (i < data->total_philos)
		{
			philo = &data->philos[i];
			if (scan_deaths(data, philo, now) == -1)
				return (NULL);
			i++;
		}
		if (data->must_eat != -1)
		{
			if (check_all_full(data) == -1)
				return (NULL);
		}
		smart_usleep(2);
	}
	return (NULL);
}
