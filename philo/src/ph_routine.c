/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:04:55 by nrabehar          #+#    #+#             */
/*   Updated: 2024/07/10 17:07:35 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ph_run_condition(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->routine_lock);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->routine_lock);
		return (0);
	}
	else if (philo->data->p_nb == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(&philo->data->print_lock);
		printf("%ld %d has taken a fork\n", ph_get_time() - philo->t_start,
			philo->id);
		pthread_mutex_unlock(&philo->data->print_lock);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(&philo->data->routine_lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->routine_lock);
	return (1);
}

void	*ph_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->routine_lock);
	philo->t_start = ph_get_time();
	philo->last_eat = ph_get_time();
	pthread_mutex_unlock(&philo->data->routine_lock);
	if ((philo->id + 1) % 2 == 0)
		usleep(1500);
	while (ph_run_condition(philo))
	{
		ph_eating_action(philo);
		ph_sleeping_action(philo);
		ph_thinking_action(philo);
	}
	return (NULL);
}
