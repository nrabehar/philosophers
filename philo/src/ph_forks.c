/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_forks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 08:58:36 by nrabehar          #+#    #+#             */
/*   Updated: 2024/07/10 17:16:56 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ph_take_left_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(&philo->data->routine_lock);
	if (!philo->data->dead)
	{
		pthread_mutex_lock(&philo->data->print_lock);
		printf("%ld %d has taken a fork\n", ph_get_time() - philo->t_start,
			philo->id);
		pthread_mutex_unlock(&philo->data->print_lock);
	}
	pthread_mutex_unlock(&philo->data->routine_lock);
}

static void	ph_take_right_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(&philo->data->routine_lock);
	if (!philo->data->dead)
	{
		pthread_mutex_lock(&philo->data->print_lock);
		printf("%ld %d has taken a fork\n", ph_get_time() - philo->t_start,
			philo->id);
		pthread_mutex_unlock(&philo->data->print_lock);
	}
	pthread_mutex_unlock(&philo->data->routine_lock);
}

void	ph_take_fork(t_philo *philo)
{
	if (philo->id < (philo->id + 1) % philo->data->p_nb)
	{
		ph_take_left_fork(philo);
		ph_take_right_fork(philo);
	}
	else
	{
		ph_take_right_fork(philo);
		ph_take_left_fork(philo);
	}
}
