/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:41:18 by nrabehar          #+#    #+#             */
/*   Updated: 2024/07/17 16:36:31 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		sem_wait(data->routine_sem);
		if (data->dead || data->stop_sem->__align)
		{
			sem_post(data->routine_sem);
			break ;
		}
		sem_post(data->routine_sem);
		usleep(100);
	}
}

int	ph_print(t_philo *philo, char *state, int(can)(t_philo *))
{
	long	time;

	sem_wait(philo->data->routine_sem);
	if (can(philo) == 0)
	{
		time = ph_get_time() - philo->data->av[T_START];
		printf("%ld %d %s\n", time, philo->id, state);
		sem_post(philo->data->routine_sem);
		return (1);
	}
	sem_post(philo->data->routine_sem);
	return (0);
}
