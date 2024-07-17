/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 08:58:36 by nrabehar          #+#    #+#             */
/*   Updated: 2024/07/17 16:30:48 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_eat(t_philo *philo)
{
	ph_take_fork(philo);
	if (ph_print(philo, "is eating", ph_can_continue) == -1)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	pthread_mutex_lock(&philo->data->routine_lock);
	philo->nb_eat++;
	philo->last_eat = ph_get_time();
	philo->is_eating = 1;
	pthread_mutex_unlock(&philo->data->routine_lock);
	ph_msleep(philo->data->av[T_EAT], philo->data);
	pthread_mutex_lock(&philo->data->routine_lock);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->data->routine_lock);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	ph_sleep(t_philo *philo)
{
	if (ph_print(philo, "is sleeping", ph_can_continue) == -1)
		return ;
	ph_msleep(philo->data->av[T_SLEEP], philo->data);
}

void	ph_think(t_philo *philo)
{
	if (ph_print(philo, "is thinking", ph_can_continue) == -1)
		return ;
	usleep(philo->data->av[T_THINK]);
}
