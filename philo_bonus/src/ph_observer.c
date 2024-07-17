/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_observer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:41:08 by nrabehar          #+#    #+#             */
/*   Updated: 2024/07/17 16:39:57 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ph_is_dead(t_philo *philo)
{
	long	time;

	if (philo->data->dead || philo->data->stop_sem->__align)
		return (1);
	if (ph_get_time() - philo->last_eat >= philo->data->av[T_DIE]
		&& !philo->is_eating)
	{
		time = ph_get_time() - philo->data->av[T_START];
		printf("%ld %d died\n", time, philo->id);
		sem_post(philo->data->stop_sem);
		philo->data->dead = 1;
		return (1);
	}
	return (0);
}

int	ph_is_satisfied(t_philo *philo)
{
	if (philo->data->av[MUST_EAT] >= 0
		&& philo->nb_eat >= philo->data->av[MUST_EAT])
	{
		philo->data->dead = 1;
		return (1);
	}
	return (0);
}

int	ph_can_continue(t_philo *philo)
{
	if (ph_is_dead(philo))
		return (1);
	if (ph_is_satisfied(philo))
		return (1);
	return (0);
}

void	*ph_observe(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (42)
	{
		sem_wait(philo->data->routine_sem);
		if (ph_is_dead(philo))
		{
			sem_post(philo->data->routine_sem);
			return (NULL);
		}
		if (philo->data->av[MUST_EAT] >= 0
			&& philo->nb_eat == philo->data->av[MUST_EAT])
			philo->nb_eat++;
		sem_post(philo->data->routine_sem);
		usleep(1000);
	}
	return (NULL);
}
