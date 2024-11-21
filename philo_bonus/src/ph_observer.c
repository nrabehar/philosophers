/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_observer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:41:08 by nrabehar          #+#    #+#             */
/*   Updated: 2024/07/18 16:47:02 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ph_should_die(t_philo *philo)
{
	long	time;

	if (philo->stop || philo->data->stop_sem->__align)
	{
		philo->stop = 1;
		return (1);
	}
	if (!philo->is_eating && ph_get_time()
		- philo->last_eat >= philo->data->av[T_DIE])
	{
		time = ph_get_time() - philo->data->av[T_START];
		sem_wait(philo->data->print_sem);
		printf("%ld %d died\n", time, philo->id);
		sem_post(philo->data->print_sem);
		sem_post(philo->data->stop_sem);
		philo->stop = 1;
		return (1);
	}
	return (0);
}

int	ph_is_satisfied(t_philo *philo)
{
	if (!philo->stop && philo->nb_eat == philo->data->av[MUST_EAT])
	{
		philo->stop = 1;
		return (1);
	}
	return (0);
}

int	ph_can_continue(t_philo *philo)
{
	sem_wait(philo->data->routine_sem);
	if (!philo->stop && !philo->data->stop_sem->__align)
	{
		sem_post(philo->data->routine_sem);
		return (1);
	}
	sem_post(philo->data->routine_sem);
	return (0);
}

void	*ph_observe(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (ph_get_time() < philo->data->av[T_START])
		usleep(1);
	while (42)
	{
		sem_wait(philo->data->routine_sem);
		if (ph_should_die(philo) || ph_is_satisfied(philo))
		{
			sem_post(philo->data->routine_sem);
			return (NULL);
		}
		sem_post(philo->data->routine_sem);
		usleep(philo->data->av[T_THINK]);
	}
	return (NULL);
}
