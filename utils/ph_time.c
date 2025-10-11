/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 21:42:05 by rexposit          #+#    #+#             */
/*   Updated: 2025/10/11 04:01:21 by rexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	now_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (-1);
	return ((time.tv_sec * 1000LL) + (time.tv_usec / 1000LL));
}

void	smart_usleep(long long ms)
{
	long long	start;
	long long	elapsed;
	long long	ms_left;

	elapsed = 0;
	start = now_ms();
	if (ms <= 0 || start == -1)
		return ;
	while (elapsed < ms)
	{
		elapsed = now_ms() - start;
		if (elapsed == -1)
			return ;
		ms_left = ms - elapsed;
		if (ms_left > 2)
			usleep(1000);
		else
			usleep(200);
	}
}
