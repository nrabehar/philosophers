/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_monitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:05:38 by nrabehar          #+#    #+#             */
/*   Updated: 2024/07/10 17:25:42 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ph_check_all(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->p_nb)
	{
		pthread_mutex_lock(&data->routine_lock);
		if (ph_get_time() - data->philo[i].last_eat >= data->t_die)
		{
			pthread_mutex_lock(&data->print_lock);
			printf("%ld %d died\n", ph_get_time() - data->philo[i].t_start, i
				+ 1);
			pthread_mutex_unlock(&data->print_lock);
			data->dead = 1;
			return (pthread_mutex_unlock(&data->routine_lock) == 0);
		}
		if (data->all_eat > 0 && data->all_eat >= data->p_nb)
		{
			data->dead = 1;
			return (pthread_mutex_unlock(&data->routine_lock) == 0);
		}
		if (data->philo[i].nb_eat == data->must_eat)
			data->all_eat++;
		pthread_mutex_unlock(&data->routine_lock);
	}
	return (0);
}

void	*ph_monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (ph_check_all(data))
			break ;
		usleep(500);
	}
	return (NULL);
}
