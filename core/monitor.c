/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:38:00 by rexposit          #+#    #+#             */
/*   Updated: 2025/10/18 18:42:48 by rexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor_routine(void *arg)
{
	int			i;
	int			j;
	int			count;
	long long	last_meal;
	long long	now;
	t_data		*data;
	t_philo		*philo;

	data = (t_data *)arg;
	while (get_dead(data) == 0)
	{
		i = 0;
		now = now_ms();
		while(i < data->total_philos)
		{
			philo = &data->philos[i];
			pthread_mutex_lock(&data->death);
			last_meal = philo->last_meal_ms;
			pthread_mutex_unlock(&data->death);
			if (now - last_meal >= data->time_die)
			{
				print_status(philo, "died");
				set_dead(data, 1);
				return (NULL);
			}
			i++;
		}
		if (data->must_eat != -1)
		{
			count = 0;
			j = 0;
			while (j < data->total_philos)
			{
				philo = &data->philos[j];
				if (philo->times_eaten >= data->must_eat)
					count++;
				j++;
			}
			if (count == data->total_philos)
			{
				set_dead(data, 1);
				return (NULL);
			}
		}
		smart_usleep(2);
	}
	return (NULL);
}
