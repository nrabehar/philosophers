/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:19:11 by nrabehar          #+#    #+#             */
/*   Updated: 2024/07/10 17:24:58 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_p_usage(void)
{
	ft_putstr_fd(STDERR_FILENO,
		C_RED "Usage: " C_RESET "./philo n1 n2 n3 n4 [n5]\n");
}

void	ph_run(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->p_nb)
	{
		pthread_create(&data->philo[i].thread, NULL, ph_routine,
			&data->philo[i]);
	}
	pthread_create(&data->monitor, NULL, ph_monitor, data);
	i = -1;
	while (++i < data->p_nb)
		pthread_join(data->philo[i].thread, NULL);
	pthread_join(data->monitor, NULL);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (validate_args(ac, av) != 0)
		return (ft_p_usage(), ft_putstr_fd(STDERR_FILENO,
				C_RED "Invalid Arguments\n" C_RESET), 1);
	ph_init_data(--ac, ++av, &data);
	ph_run(&data);
	ph_destroy_mutex(&data);
	return (0);
}
