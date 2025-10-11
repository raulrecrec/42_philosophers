/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:36:55 by rexposit          #+#    #+#             */
/*   Updated: 2025/10/11 04:07:08 by rexposit         ###   ########.fr       */
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
# include <stdbool.h>	// bool
# include <limits.h>		// INT_MAX

typedef struct philo t_philo;

typedef enum status_err
{
	ERR_OK = 0,
	ERR_ARGS,				// argumentos inválidos / faltan
	ERR_RANGE,				// valores fuera de rango (>0, etc.)
	ERR_MALLOC,				// fallo en malloc
	ERR_MUTEX_INIT,			// fallo al iniciar mutex
	ERR_THREAD_CREATE,		// fallo al crear hilos
	// Añadir más según necesite
}	t_err;

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
	t_err	err;
} t_data;

typedef struct philo
{
	int				id;
	int				index;
	pthread_t		thread;
	pthread_mutex_t	*left_hand;
	pthread_mutex_t	*right_hand;
	long long		last_meal_ms;
	int				times_eaten;
	int				target_meals;
	t_data			*data;
} t_philo;


// utils
void		*ph_malloc(t_data *data, size_t size);
long long	ph_atoll(t_data *data, const char *nptr);
int			ph_error(t_data *data, t_err error);
bool		ph_isdigit(char ch);
int			ph_strlen(const char *str);
long long	now_ms(void);
void		smart_usleep(long long ms);

#endif