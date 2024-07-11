/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 08:58:36 by nrabehar          #+#    #+#             */
/*   Updated: 2024/07/11 10:38:08 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_eating_action(t_philo *philo)
{
	ph_take_fork(philo);
	pthread_mutex_lock(&philo->data->routine_lock);
	if (ph_print(philo, "is eating", ph_can_continue) == -1)
	{
		pthread_mutex_unlock(&philo->data->routine_lock);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return ;
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
	if (ph_print(philo, "is sleeping", ph_can_continue) == -1)
	{
		pthread_mutex_unlock(&philo->data->routine_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->data->routine_lock);
	ph_msleep(philo->data->t_sleep, philo->data);
}

void	ph_thinking_action(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->routine_lock);
	ph_print(philo, "is thinking", ph_can_continue);
	pthread_mutex_unlock(&philo->data->routine_lock);
}
