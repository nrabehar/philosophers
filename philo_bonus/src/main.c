/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:40:57 by nrabehar          #+#    #+#             */
/*   Updated: 2024/07/23 12:37:45 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ph_usage(void)
{
	printf("Usage: ./philo n1 n2 n3 n4 [n5]\n");
	printf("\t\tn1: number_of_philosophers > 0\n");
	printf("\t\tn2: time_to_die >= 0\n");
	printf("\t\tn3: time_to_eat >= 0\n");
	printf("\t\tn4: time_to_sleep >= 0\n");
	printf("\t\tn5: number_of_times_each_philosopher_must_eat >= 0\n");
}

static void	ph_take_one(t_philo *philo)
{
	if (philo->data->av[NB_PHILO] > 1)
		return ;
	sem_wait(philo->data->forks);
	if (ph_can_continue(philo))
		ph_print(philo, "has taken a fork");
	sem_post(philo->data->forks);
	ph_msleep(philo->data->av[T_DIE]);
	ph_print(philo, "died");
	exit(0);
}

static void	ph_routine(t_philo *philo)
{
	while (ph_get_time() < philo->data->av[T_START])
		usleep(1);
	ph_take_one(philo);
	if (pthread_create(&philo->observer, NULL, ph_observe, philo))
		exit(1);
	pthread_detach(philo->observer);
	if (philo->id % 2 == 0)
		ph_msleep(philo->data->av[T_THINK]);
	while (ph_can_continue(philo))
	{
		ph_eat(philo);
		ph_sleep(philo);
		ph_think(philo);
	}
	ph_destroy(philo->data);
	exit(0);
}

void	ph_run(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->av[NB_PHILO])
	{
		data->philo[i].self = fork();
		if (data->philo[i].self == 0)
			ph_routine(&data->philo[i]);
	}
	i = -1;
	while (++i < data->av[NB_PHILO])
		waitpid(-1, NULL, 0);
	ph_destroy(data);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		is_initialized;

	if (validate_args(ac, av) != 0)
	{
		ph_error(C_RED "Invalid Arguments\n" C_RESET);
		ph_usage();
		return (1);
	}
	is_initialized = ph_init_data(--ac, ++av, &data);
	if (is_initialized == 1)
		return (0);
	else if (is_initialized == -1)
		return (1);
	ph_run(&data);
	return (0);
}
