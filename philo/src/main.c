/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:19:11 by nrabehar          #+#    #+#             */
/*   Updated: 2024/07/23 12:37:52 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ph_usage(void)
{
	printf("Usage: ./philo n1 n2 n3 n4 [n5]\n");
	printf("\t\tn1: number_of_philosophers > 0\n");
	printf("\t\tn2: time_to_die >= 0\n");
	printf("\t\tn3: time_to_eat >= 0\n");
	printf("\t\tn4: time_to_sleep >= 0\n");
	printf("\t\tn5: number_of_times_each_philosopher_must_eat >= 0\n");
}

static void	*ph_take_one(t_philo *philo)
{
	while (ph_get_time() < philo->data->av[T_START])
		usleep(1);
	pthread_mutex_lock(philo->l_fork);
	if (ph_can_continue(philo))
		ph_print(philo, "has taken a fork");
	pthread_mutex_unlock(philo->l_fork);
	return (NULL);
}

static void	*ph_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->av[NB_PHILO] == 1)
		return (ph_take_one(philo));
	while (ph_get_time() < philo->data->av[T_START])
		usleep(1);
	if (philo->id % 2 == 0)
		ph_msleep(philo->data->av[T_THINK]);
	while (ph_can_continue(philo))
	{
		ph_eat(philo);
		ph_sleep(philo);
		ph_think(philo);
	}
	return (NULL);
}

void	ph_run(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->av[NB_PHILO])
	{
		pthread_create(&data->philo[i].thread, NULL, ph_routine,
			&data->philo[i]);
	}
	ph_observe(data);
	i = -1;
	while (++i < data->av[NB_PHILO])
		pthread_join(data->philo[i].thread, NULL);
	ph_destroy(data);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		is_initialized;

	if (validate_args(ac, av) != 0)
	{
		ph_error("Invalid Arguments\n");
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
