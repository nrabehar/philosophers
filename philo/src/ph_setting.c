/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_setting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:05:36 by nrabehar          #+#    #+#             */
/*   Updated: 2024/07/23 12:57:50 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	validate_args(int ac, char **av)
{
	int	i;
	int	j;

	if (ac < 5 || ac > 6)
		return (-1);
	i = 1;
	while (i < ac)
	{
		j = 0;
		while ((av[i][j] >= 48 && av[i][j] <= 57))
			j++;
		if (av[i][j] != '\0')
			return (-1);
		i++;
	}
	if (i < ac)
		return (-1);
	return (0);
}

static int	ph_init_philos(t_data *data)
{
	int	i;

	data->philo = (t_philo *)malloc(sizeof(t_philo) * data->av[NB_PHILO]);
	if (!data->philo)
		return (ph_error("Failed to allocate memory for philos\n"), -1);
	i = -1;
	while (++i < data->av[NB_PHILO])
	{
		data->philo[i].id = i + 1;
		data->philo[i].data = data;
		data->philo[i].nb_eat = 0;
		data->philo[i].is_eating = 0;
		data->philo[i].stop = 0;
		data->philo[i].last_eat = data->av[T_START];
		data->philo[i].l_fork = &data->forks[i];
		data->philo[i].r_fork = &data->forks[(i + 1) % data->av[NB_PHILO]];
	}
	return (0);
}

static int	ph_init_mutex(t_data *data)
{
	int	i;

	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->av[NB_PHILO]);
	if (!data->forks)
		return (-1);
	i = -1;
	while (++i < data->av[NB_PHILO])
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (ph_destroy_forks(data, i),
				ph_error("Failed to initialize mutexs\n"), -1);
	}
	if (pthread_mutex_init(&data->routine_lock, NULL))
		return (ph_destroy_forks(data, i),
			ph_error("Failed to initialize mutexs\n"), -1);
	if (pthread_mutex_init(&data->print_lock, NULL))
		return (ph_destroy_forks(data, i),
			pthread_mutex_destroy(&data->routine_lock),
			ph_error("Failed to initialize mutexs\n"), -1);
	return (0);
}

int	ph_init_data(int ac, char **av, t_data *data)
{
	long	available_time;

	data->av[NB_PHILO] = ph_atol(av[0]);
	data->av[T_DIE] = ph_atol(av[1]);
	data->av[T_EAT] = ph_atol(av[2]);
	data->av[T_SLEEP] = ph_atol(av[3]);
	data->av[MUST_EAT] = -1;
	if (ac == 5)
		data->av[MUST_EAT] = (int)ph_atol(av[4]);
	if (data->av[MUST_EAT] == 0)
		return (1);
	data->dead = 0;
	data->all_eat = 0;
	if (ph_revalide_data(data) || ph_init_mutex(data))
		return (-1);
	data->av[T_START] = ph_get_time() + (data->av[NB_PHILO] * 50);
	if (ph_init_philos(data) == -1)
		return (ph_destroy_forks(data, data->av[NB_PHILO]), -1);
	available_time = (data->av[T_DIE] - (data->av[T_EAT] + data->av[T_SLEEP]));
	if (available_time <= 0)
		available_time = 1;
	if (available_time > data->av[T_EAT])
		available_time = data->av[T_EAT];
	data->av[T_THINK] = available_time;
	return (0);
}

void	ph_destroy(t_data *data)
{
	ph_destroy_forks(data, data->av[NB_PHILO]);
	pthread_mutex_destroy(&data->routine_lock);
	pthread_mutex_destroy(&data->print_lock);
	if (data->philo)
		free(data->philo);
}
