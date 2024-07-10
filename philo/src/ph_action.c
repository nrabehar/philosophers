/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 08:58:36 by nrabehar          #+#    #+#             */
/*   Updated: 2024/07/10 17:16:24 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_eating_action(t_philo *philo)
{
	ph_take_fork(philo);
	pthread_mutex_lock(&philo->data->routine_lock);
	if (!philo->data->dead)
	{
		pthread_mutex_lock(&philo->data->print_lock);
		printf("%ld %d is eating\n", ph_get_time() - philo->t_start, philo->id);
		pthread_mutex_unlock(&philo->data->print_lock);
	}
	philo->nb_eat++;
	philo->last_eat = ph_get_time();
	pthread_mutex_unlock(&philo->data->routine_lock);
	ph_msleep(philo->data->t_eat, philo->data);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	ph_sleeping_action(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->routine_lock);
	if (!philo->data->dead)
	{
		pthread_mutex_lock(&philo->data->print_lock);
		printf("%ld %d is sleeping\n", ph_get_time() - philo->t_start,
			philo->id);
		pthread_mutex_unlock(&philo->data->print_lock);
	}
	pthread_mutex_unlock(&philo->data->routine_lock);
	ph_msleep(philo->data->t_sleep, philo->data);
}

void	ph_thinking_action(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->routine_lock);
	if (!philo->data->dead)
	{
		pthread_mutex_lock(&philo->data->print_lock);
		printf("%ld %d is thinking\n", ph_get_time() - philo->t_start,
			philo->id);
		pthread_mutex_unlock(&philo->data->print_lock);
	}
	pthread_mutex_unlock(&philo->data->routine_lock);
}
