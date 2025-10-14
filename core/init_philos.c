/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 22:09:18 by rexposit          #+#    #+#             */
/*   Updated: 2025/10/14 22:32:34 by rexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philos(t_data *data)
{
	int		i;
	int		n;
	t_philo	*philo;

	n = data->total_philos;
	i = 0;
	while (i < n)
	{
		philo = &data->philos[i];
		philo->id = i + 1;
		philo->left_hand = &data->forks[i];
		philo->right_hand = &data->forks[(i + 1) % n];
		philo->times_eaten = 0;
		philo->last_meal_ms = 0;
		philo->data = data;
		i++;
	}
}
