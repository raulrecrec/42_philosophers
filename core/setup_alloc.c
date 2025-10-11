/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_alloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 04:11:02 by rexposit          #+#    #+#             */
/*   Updated: 2025/10/11 16:43:04 by rexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_err	setup_alloc(t_data *data)
{
	size_t	aux;

	aux = (size_t)data->total_philos;
	data->forks = ph_malloc(data, (aux * sizeof(pthread_mutex_t)));
	if (data->forks == NULL)
		return (data->err);
	data->philos = ph_malloc(data, (aux * sizeof(t_philo)));
	if (data->philos == NULL)
	{
		free(data->forks);
		data->forks = NULL;
		return (data->err);
	}
	return (ERR_OK);
}
