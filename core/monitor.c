/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:38:00 by rexposit          #+#    #+#             */
/*   Updated: 2025/11/15 20:05:03 by rexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	scan_deaths(t_data *data, t_philo *philo, long long now)
{
	long long	last_meal;
	int			times_eaten;

	pthread_mutex_lock(&data->m_last_meal_ms);
	last_meal = philo->last_meal_ms;
	times_eaten = philo->times_eaten;
	pthread_mutex_unlock(&data->m_last_meal_ms);
	if ((data->must_eat == -1)
		|| (data->must_eat != -1 && times_eaten < data->must_eat))
	{
		if (now - last_meal > data->time_die)
		{
			print_status(philo, "died");
			set_dead(data, 1);
			return (-1);
		}
	}
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
		pthread_mutex_lock(&data->m_last_meal_ms);
		if (philo->times_eaten >= data->must_eat)
			count++;
		pthread_mutex_unlock(&data->m_last_meal_ms);
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
		smart_usleep(5);
	}
	return (NULL);
}
