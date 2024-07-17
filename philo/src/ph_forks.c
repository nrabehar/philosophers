/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_forks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 08:58:36 by nrabehar          #+#    #+#             */
/*   Updated: 2024/07/16 10:34:40 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ph_take_left_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	if (ph_print(philo, "has taken a fork", ph_can_continue) == -1)
		return ;
}

static void	ph_take_right_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	if (ph_print(philo, "has taken a fork", ph_can_continue) == -1)
		return ;
}

void	ph_take_fork(t_philo *philo)
{
	if ((philo->id) % 2 == 0)
	{
		ph_take_right_fork(philo);
		ph_take_left_fork(philo);
	}
	else
	{
		ph_take_left_fork(philo);
		ph_take_right_fork(philo);
	}
}

void	ph_drop_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
}

void	ph_destroy_forks(t_data *data, int limit)
{
	int	i;

	i = -1;
	while (++i < limit)
		pthread_mutex_destroy(&data->forks[i]);
	free(data->forks);
}
