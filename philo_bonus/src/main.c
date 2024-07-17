/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:40:57 by nrabehar          #+#    #+#             */
/*   Updated: 2024/07/17 16:34:23 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ph_usage(void)
{
	printf("Usage: ./philo n1 n2 n3 n4 [n5]\n");
	printf("\t\tn1: number_of_philosophers\n");
	printf("\t\tn2: time_to_die\n");
	printf("\t\tn3: time_to_eat\n");
	printf("\t\tn4: time_to_sleep\n");
	printf("\t\tn5: number_of_times_each_philosopher_must_eat\n");
}

static void	ph_launch_observer(t_philo *philo)
{
	pthread_create(&philo->observer, NULL, ph_observe, philo);
}

static void	ph_routine(t_philo *philo)
{
	while (ph_get_time() < philo->data->av[T_START])
		usleep(1);
	if (philo->id % 2 == 0)
		usleep(philo->data->av[T_THINK]);
	ph_launch_observer(philo);
	while (1)
	{
		sem_wait(philo->data->routine_sem);
		if (ph_can_continue(philo) != 0)
			break ;
		sem_post(philo->data->routine_sem);
		ph_eat(philo);
		sem_wait(philo->data->routine_sem);
		if (ph_is_satisfied(philo))
			break ;
		sem_post(philo->data->routine_sem);
		ph_sleep(philo);
		ph_think(philo);
	}
	sem_post(philo->data->routine_sem);
	pthread_join(philo->observer, NULL);
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
		waitpid(data->philo[i].self, NULL, 0);
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
		return (ph_destroy(&data), 1);
	ph_run(&data);
	return (0);
}
