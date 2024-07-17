/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_observer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:05:38 by nrabehar          #+#    #+#             */
/*   Updated: 2024/07/17 16:31:45 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ph_is_dead(t_philo *philo)
{
	long	time;

	if (philo->data->dead)
		return (1);
	if (ph_get_time() - philo->last_eat >= philo->data->av[T_DIE]
		&& !philo->is_eating)
	{
		time = ph_get_time() - philo->data->av[T_START];
		printf("%ld %d died\n", time, philo->id);
		philo->data->dead = 1;
		return (1);
	}
	return (0);
}

static int	ph_is_satisfied(t_philo *philo)
{
	if (philo->data->av[MUST_EAT] >= 0
		&& philo->nb_eat >= philo->data->av[MUST_EAT])
		return (1);
	return (0);
}

static int	ph_is_all_eat(t_data *data)
{
	if (data->av[MUST_EAT] > 0 && data->all_eat >= data->av[NB_PHILO])
	{
		data->dead = 1;
		return (1);
	}
	return (0);
}

int	ph_can_continue(t_philo *philo)
{
	if (ph_is_dead(philo))
		return (0);
	if (ph_is_satisfied(philo))
		return (0);
	if (ph_is_all_eat(philo->data))
		return (0);
	return (1);
}

int	ph_observe(t_data *data)
{
	long	i;

	while (ph_get_time() < data->av[T_START])
		usleep(1);
	while (42)
	{
		i = -1;
		pthread_mutex_lock(&data->routine_lock);
		while (++i < data->av[NB_PHILO])
		{
			if (ph_is_dead(&data->philo[i]))
				return (pthread_mutex_unlock(&data->routine_lock));
			if (ph_is_all_eat(data))
				return (pthread_mutex_unlock(&data->routine_lock));
			if (data->av[MUST_EAT] >= 0
				&& data->philo[i].nb_eat == data->av[MUST_EAT])
			{
				data->philo[i].nb_eat++;
				data->all_eat++;
			}
		}
		pthread_mutex_unlock(&data->routine_lock);
		usleep(1000);
	}
	return (0);
}
