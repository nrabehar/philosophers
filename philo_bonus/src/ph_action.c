/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:40:45 by nrabehar          #+#    #+#             */
/*   Updated: 2024/07/17 16:33:53 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ph_eat(t_philo *philo)
{
	ph_take_fork(philo);
	if (ph_print(philo, "is eating", ph_can_continue) == -1)
		return (ph_drop_fork(philo));
	sem_wait(philo->data->routine_sem);
	philo->nb_eat++;
	philo->last_eat = ph_get_time();
	philo->is_eating = 1;
	sem_post(philo->data->routine_sem);
	ph_msleep(philo->data->av[T_EAT], philo->data);
	sem_wait(philo->data->routine_sem);
	philo->is_eating = 0;
	sem_post(philo->data->routine_sem);
	ph_drop_fork(philo);
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
