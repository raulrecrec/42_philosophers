/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:30:03 by rexposit          #+#    #+#             */
/*   Updated: 2025/10/21 05:21:20 by rexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	ph_atoll(t_data *data, const char *nptr)
{
	long long	res;

	res = 0;
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\n'
		|| *nptr == '\v' || *nptr == '\f' || *nptr == '\r')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			return (ph_error(data, ERR_ARGS));
		nptr++;
	}
	while (*nptr == '0')
		nptr++;
	if (ph_strlen(nptr) > 20)
		return (ph_error(data, ERR_RANGE));
	while (ph_isdigit(*nptr))
	{
		res = res * 10 + (*nptr - '0');
		nptr++;
	}
	if (*nptr != '\0')
		return (ph_error(data, ERR_ARGS));
	return (res);
}
