/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_setting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:41:13 by nrabehar          #+#    #+#             */
/*   Updated: 2024/07/23 12:57:58 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	validate_args(int ac, char **av)
{
	int	i;
	int	j;

	if (ac < 5 || ac > 6)
		return (-1);
	i = 1;
	while (i < ac && av[1][0] != '0')
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

static void	ph_init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->av[NB_PHILO])
	{
		data->philo[i].id = i + 1;
		data->philo[i].data = data;
		data->philo[i].nb_eat = 0;
		data->philo[i].is_eating = 0;
		data->philo[i].stop = 0;
		data->philo[i].last_eat = data->av[T_START];
	}
}

static int	ph_init_sems(t_data *data)
{
	sem_unlink(PH_SEM_FORKS);
	data->forks = sem_open(PH_SEM_FORKS, O_CREAT, 0644, data->av[NB_PHILO]);
	if (data->forks == SEM_FAILED)
		return (ph_error("Failed to open semaphore\n"), -1);
	sem_unlink(PH_SEM_ROUTINE);
	data->routine_sem = sem_open(PH_SEM_ROUTINE, O_CREAT, 0644, 1);
	if (data->routine_sem == SEM_FAILED)
		return (sem_close(data->forks), ph_error("Failed to open semaphore\n"),
			-1);
	sem_unlink(PH_SEM_PRINT);
	data->print_sem = sem_open(PH_SEM_PRINT, O_CREAT, 0644, 1);
	if (data->print_sem == SEM_FAILED)
		return (sem_close(data->forks), sem_close(data->routine_sem),
			ph_error("Failed to open semaphore\n"), -1);
	sem_unlink(PH_SEM_STOP);
	data->stop_sem = sem_open(PH_SEM_STOP, O_CREAT, 0644, 0);
	if (data->stop_sem == SEM_FAILED)
		return (sem_close(data->forks), sem_close(data->routine_sem),
			sem_close(data->stop_sem), ph_error("Failed to open semaphore\n"),
			-1);
	return (0);
}

/**
 * @brief Initialize `data` struct's properties
 */
int	ph_init_data(int ac, char **av, t_data *data)
{
	long	available_time;

	data->av[NB_PHILO] = ph_atol(av[0]);
	if (data->av[NB_PHILO] <= 0 || data->av[NB_PHILO] > 200)
		return (ph_error("Invalid number of philosophers\n"), -1);
	data->av[T_DIE] = ph_atol(av[1]);
	data->av[T_EAT] = ph_atol(av[2]);
	data->av[T_SLEEP] = ph_atol(av[3]);
	data->av[MUST_EAT] = -1;
	if (ac == 5)
		data->av[MUST_EAT] = (int)ph_atol(av[4]);
	if (data->av[MUST_EAT] == 0)
		return (1);
	if (ph_revalide_data(data) || ph_init_sems(data))
		return (-1);
	data->av[T_START] = ph_get_time() + (data->av[NB_PHILO] * 50);
	ph_init_philos(data);
	available_time = (data->av[T_DIE] - data->av[T_EAT] - data->av[T_SLEEP]);
	if (available_time <= 0)
		available_time = 1;
	if (available_time > data->av[T_EAT])
		available_time = data->av[T_EAT];
	data->av[T_THINK] = available_time;
	return (0);
}

void	ph_destroy(t_data *data)
{
	if (sem_close(data->forks))
		printf("Error closing semaphore\n");
	if (sem_close(data->routine_sem))
		printf("Error closing semaphore\n");
	if (sem_close(data->stop_sem))
		printf("Error closing semaphore\n");
	if (sem_close(data->print_sem))
		printf("Error closing semaphore\n");
	sem_unlink(PH_SEM_FORKS);
	sem_unlink(PH_SEM_ROUTINE);
	sem_unlink(PH_SEM_PRINT);
	sem_unlink(PH_SEM_STOP);
	return ;
}
