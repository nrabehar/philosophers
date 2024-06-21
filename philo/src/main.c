/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:19:11 by nrabehar          #+#    #+#             */
/*   Updated: 2024/06/21 09:11:15 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_p_usage(void)
{
	ft_putstr_fd(STDERR_FILENO,
		C_RED "Usage: " C_RESET "./philo n1 n2 n3 n4 [n5]\n");
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ft_get_params(--ac, ++av, &data))
		return (ft_p_usage(), ft_putstr_fd(STDERR_FILENO,
				C_RED "Invalid Arguments\n" C_RESET));
	printf("philos numbers [%d]\n", data.p_nb);
	printf("time to die [%d]\n", data.t_die);
	printf("time to eat [%d]\n", data.t_eat);
	printf("time to sleep [%d]\n", data.t_sleep);
	printf("time must eat [%d]\n", data.t_m_eat);
	return (0);
}
