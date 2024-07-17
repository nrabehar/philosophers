/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:23:33 by nrabehar          #+#    #+#             */
/*   Updated: 2024/07/16 10:46:37 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_error(char *s)
{
	size_t	length;

	length = 0;
	if (!s || !*s)
		return ;
	while (s[length])
		length++;
	write(STDERR_FILENO, s, length);
}

long	ph_atol(char *s)
{
	long	res;

	res = 0;
	while (*s >= 48 && *s <= 57)
	{
		res *= 10;
		res += *s - 48;
		s++;
	}
	return (res);
}

long	ph_get_time(void)
{
	struct timeval	time;
	long			sec_to_ms;
	long			usec_to_ms;

	gettimeofday(&time, NULL);
	sec_to_ms = time.tv_sec * 1000;
	usec_to_ms = time.tv_usec / 1000;
	return (sec_to_ms + usec_to_ms);
}

void	ph_msleep(long ms, t_data *data)
{
	long	start;

	start = ph_get_time();
	while (ph_get_time() - start < ms)
	{
		pthread_mutex_lock(&data->routine_lock);
		if (data->dead)
		{
			pthread_mutex_unlock(&data->routine_lock);
			break ;
		}
		pthread_mutex_unlock(&data->routine_lock);
		usleep(100);
	}
}

int	ph_print(t_philo *philo, char *state, int(can)(t_philo *))
{
	long	time;

	pthread_mutex_lock(&philo->data->routine_lock);
	time = ph_get_time() - philo->data->av[T_START];
	if (!can(philo))
	{
		pthread_mutex_unlock(&philo->data->routine_lock);
		return (-1);
	}
	printf("%ld %d %s\n", time, philo->id, state);
	pthread_mutex_unlock(&philo->data->routine_lock);
	return (0);
}
