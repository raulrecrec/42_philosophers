/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:36:55 by rexposit          #+#    #+#             */
/*   Updated: 2025/09/25 19:43:46 by rexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>		// printf
# include <stdlib.h>	// malloc, free
# include <unistd.h>	// write, usleep
# include <string.h>	// memset
# include <sys/time.h>	// gettimeofday
# include <pthread.h>	// threads & mutex

typedef struct philo t_philo;

typedef struct data
{
	int				total_philos;
	long long		time_die;
	long long		time_eat;
	long long		time_sleep;
	int				must_eat;
	long long		time_start;
	int				dead;
	pthread_mutex_t	death;
	pthread_mutex_t	*forks;
	pthread_mutex_t	prints;
	pthread_mutex_t	etc;
	t_philo	*philos;
} t_data;

typedef struct philo
{
	int				id;
	pthread_mutex_t	*left_hand;
	pthread_mutex_t	*right_hand;
	int		times_eaten;
	t_data	*data;
} t_philo;

#endif