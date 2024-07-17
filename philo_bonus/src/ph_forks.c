/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_forks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:41:03 by nrabehar          #+#    #+#             */
/*   Updated: 2024/07/17 14:07:12 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ph_take_fork(t_philo *philo)
{
	sem_wait(philo->data->forks);
	sem_wait(philo->data->forks);
	if (ph_print(philo, "has taken a fork", ph_can_continue) == -1)
		return ;
	if (ph_print(philo, "has taken a fork", ph_can_continue) == -1)
		return ;
}

void	ph_drop_fork(t_philo *philo)
{
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}
