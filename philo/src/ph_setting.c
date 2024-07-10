/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_setting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:05:36 by nrabehar          #+#    #+#             */
/*   Updated: 2024/07/10 17:19:07 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Check arguments
 *  - arguments count should be only 5 or 6(optional must_eat number)
 *  - all arguments does only contains a positive number and great that 0
 * @param ac arguments count
 * @param av arguments value
 * @return 0 if all arguments is valid else -1 on error
 */
int	validate_args(int ac, char **av)
{
	int	i;
	int	j;

	if (ac < 5 || ac > 6)
		return (-1);
	i = 1;
	while (i < ac && av[i][0] != '0')
	{
		j = 0;
		while (av[i][j] >= 48 && av[i][j] <= 57)
			j++;
		if (av[i][j] != '\0')
			return (-1);
		i++;
	}
	if (i < ac)
		return (-1);
	return (0);
}

/**
 * @brief Initialize `data` struct's properties
 */
int	ph_init_data(int ac, char **av, t_data *data)
{
	int	i;

	data->p_nb = ph_atol(av[0]);
	data->t_die = ph_atol(av[1]);
	data->t_eat = ph_atol(av[2]);
	data->t_sleep = ph_atol(av[3]);
	data->must_eat = -1;
	if (ac == 5)
		data->must_eat = (int)ph_atol(av[4]);
	data->dead = 0;
	data->all_eat = 0;
	ph_init_mutex(data);
	i = -1;
	while (++i < data->p_nb)
	{
		data->philo[i].id = i;
		data->philo[i].data = data;
		data->philo[i].nb_eat = 0;
		data->philo[i].t_start = ph_get_time();
		data->philo[i].last_eat = data->philo[i].t_start;
		data->philo[i].l_fork = &data->forks[i];
		data->philo[i].r_fork = &data->forks[(i + 1) % data->p_nb];
	}
	return (0);
}

int	ph_init_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i <= data->p_nb)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (-1);
	}
	if (pthread_mutex_init(&data->print_lock, NULL))
		return (-1);
	if (pthread_mutex_init(&data->routine_lock, NULL))
		return (-1);
	return (0);
}

/**
 * @brief Destroy mutexes
 */
void	ph_destroy_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->p_nb)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->routine_lock);
}
