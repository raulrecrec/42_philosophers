/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:55:15 by rexposit          #+#    #+#             */
/*   Updated: 2025/10/17 21:24:24 by rexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void
	*one_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_hand);
	print_status(philo, "has taken a fork");
	while (get_dead(philo->data) == 0)
		smart_usleep(2);
	pthread_mutex_unlock(philo->left_hand);
	return (NULL);
}

static void
	get_min_max_fork(t_philo *ph, pthread_mutex_t **min, pthread_mutex_t **max)
{
	if (ph->left_hand < ph->right_hand)
	{
		*min = ph->left_hand;
		*max = ph->right_hand;
	}
	else
	{
		*min = ph->right_hand;
		*max = ph->left_hand;
	}
}

static int
	philo_eating(t_philo *ph, pthread_mutex_t *min, pthread_mutex_t *max)
{
	pthread_mutex_lock(min);
	print_status(ph, "has taken a fork");
	if (get_dead(ph->data) == 1)
	{
		pthread_mutex_unlock(min);
		return (-1);
	}
	pthread_mutex_lock(max);
	if (get_dead(ph->data) == 1)
	{
		pthread_mutex_unlock(max);
		pthread_mutex_unlock(min);
		return (-1);
	}
	print_status(ph, "has taken a fork");
	pthread_mutex_lock(&ph->data->death);
	ph->last_meal_ms = now_ms();
	pthread_mutex_unlock(&ph->data->death);
	print_status(ph, "is eating");
	ph->times_eaten++;
	smart_usleep(ph->data->time_eat);
	pthread_mutex_unlock(max);
	pthread_mutex_unlock(min);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo			*philo;
	pthread_mutex_t	*min;
	pthread_mutex_t	*max;

	philo = (t_philo *)arg;
	if (philo->data->total_philos == 1)
		return (one_fork(philo));
	get_min_max_fork(philo, &min, &max);
	if (philo->id % 2 == 0)
		smart_usleep(2);
	while (get_dead(philo->data) == 0)
	{
		print_status(philo, "is thinking");
		if (philo_eating(philo, min, max) == -1)
			break ;
		if (philo->data->must_eat != -1
			&& philo->times_eaten >= philo->data->must_eat)
			break ;
		print_status(philo, "is sleeping");
		smart_usleep(philo->data->time_sleep);
	}
	return (NULL);
}
