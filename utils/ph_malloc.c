/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:29:50 by rexposit          #+#    #+#             */
/*   Updated: 2025/10/07 18:22:35 by rexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ph_malloc(size_t size, t_data *data)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
	{
		data->err = ERR_MALLOC;
		return (NULL);
	}
	return (ptr);
}
