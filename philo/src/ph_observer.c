/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_observer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:05:38 by nrabehar          #+#    #+#             */
/*   Updated: 2024/07/23 11:36:06 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ph_should_die(t_philo *philo)
{
	long	time;

	if (philo->data->dead)
		return (1);
	if (!philo->is_eating && ph_get_time()
		- philo->last_eat >= philo->data->av[T_DIE])
	{
		time = ph_get_time() - philo->data->av[T_START];
		pthread_mutex_lock(&philo->data->print_lock);
		printf("%ld %d died\n", time, philo->id);
		pthread_mutex_unlock(&philo->data->print_lock);
		philo->data->dead = 1;
		return (1);
	}
	return (0);
}

static int	ph_is_satisfied(t_philo *philo)
{
	if (!philo->stop && philo->nb_eat == philo->data->av[MUST_EAT])
	{
		philo->data->all_eat++;
		philo->stop = 1;
		return (1);
	}
	return (0);
}

static int	ph_is_all_eat(t_data *data)
{
	if (data->all_eat == data->av[NB_PHILO])
	{
		data->dead = 1;
		return (1);
	}
	return (0);
}

int	ph_can_continue(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->routine_lock);
	if (!philo->data->dead && !philo->stop)
	{
		pthread_mutex_unlock(&philo->data->routine_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->routine_lock);
	return (0);
}

int	ph_observe(t_data *data)
{
	long	i;

	while (ph_get_time() < data->av[T_START])
		usleep(1);
	while (42)
	{
		i = -1;
		while (++i < data->av[NB_PHILO])
		{
			pthread_mutex_lock(&data->routine_lock);
			if (ph_should_die(&data->philo[i]))
				return (pthread_mutex_unlock(&data->routine_lock));
			ph_is_satisfied(&data->philo[i]);
			if (ph_is_all_eat(data))
				return (pthread_mutex_unlock(&data->routine_lock));
			pthread_mutex_unlock(&data->routine_lock);
		}
		usleep(100);
	}
	return (0);
}
