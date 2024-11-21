/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 08:58:36 by nrabehar          #+#    #+#             */
/*   Updated: 2024/07/23 12:34:44 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_eat(t_philo *philo)
{
	ph_take_fork(philo);
	if (!ph_can_continue(philo))
		return (ph_drop_fork(philo));
	ph_print(philo, "is eating");
	pthread_mutex_lock(&philo->data->routine_lock);
	philo->nb_eat++;
	philo->last_eat = ph_get_time();
	philo->is_eating = 1;
	pthread_mutex_unlock(&philo->data->routine_lock);
	ph_msleep(philo->data->av[T_EAT]);
	pthread_mutex_lock(&philo->data->routine_lock);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->data->routine_lock);
	ph_drop_fork(philo);
}

void	ph_sleep(t_philo *philo)
{
	if (!ph_can_continue(philo))
		return ;
	ph_print(philo, "is sleeping");
	ph_msleep(philo->data->av[T_SLEEP]);
}

void	ph_think(t_philo *philo)
{
	if (!ph_can_continue(philo))
		return ;
	ph_print(philo, "is thinking");
	usleep(philo->data->av[T_THINK]);
}

int	ph_revalide_data(t_data *data)
{
	int	pass;

	pass = 0;
	if (data->av[NB_PHILO] <= 0 || data->av[NB_PHILO] > 200)
	{
		ph_error("Invalid number of philosophers\n");
		pass = -1;
	}
	return (pass);
}
