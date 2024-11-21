/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:23:33 by nrabehar          #+#    #+#             */
/*   Updated: 2024/07/23 11:01:23 by nrabehar         ###   ########.fr       */
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
	write(STDERR_FILENO, C_RED "Error: " C_RESET, 19);
	write(STDERR_FILENO, s, length);
}

long	ph_atol(char *s)
{
	long	res;
	long	sign;

	res = 0;
	sign = 1;
	while ((*s >= 9 && *s <= 13) || *s == 32)
		s++;
	if (*s == '-')
		sign = -1;
	if (*s == '-' || *s == '+')
		s++;
	while (*s >= 48 && *s <= 57)
	{
		res *= 10;
		res += *s - 48;
		s++;
	}
	return (res * sign);
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

void	ph_msleep(long ms)
{
	long	start;

	start = ph_get_time();
	while (ph_get_time() - start < ms)
		usleep(1);
}

void	ph_print(t_philo *philo, char *state)
{
	long	time;

	time = ph_get_time() - philo->data->av[T_START];
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%ld %d %s\n", time, philo->id, state);
	pthread_mutex_unlock(&philo->data->print_lock);
}
