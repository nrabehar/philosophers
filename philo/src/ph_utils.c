/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:23:33 by nrabehar          #+#    #+#             */
/*   Updated: 2024/07/11 10:37:20 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr_fd(int fd, char *s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
		i++;
	write(fd, s, i);
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

/// @brief Get current time in milliseconds
/// add current time in seconds * 1000 to the microseconds divided by 1000
/// to get the current time in milliseconds
/// @return Current time in milliseconds
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
		if (data->dead == 1)
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
	int		id;

	pthread_mutex_lock(&philo->data->print_lock);
	time = ph_get_time() - philo->t_start;
	id = philo->id + 1;
	if (!can(philo))
	{
		pthread_mutex_unlock(&philo->data->print_lock);
		return (-1);
	}
	printf("%ld %d %s\n", time, id, state);
	pthread_mutex_unlock(&philo->data->print_lock);
	return (0);
}
