/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:23:33 by nrabehar          #+#    #+#             */
/*   Updated: 2024/06/21 09:01:22 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigits(char *s)
{
	while (*s && *s >= '0' && *s <= '9')
		s++;
	return (!*s);
}

int	ft_putstr_fd(int fd, char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
		i++;
	return (write(fd, s, i));
}

unsigned int	ft_atoi(char *s)
{
	unsigned int	res;

	res = 0;
	while (*s >= 48 && *s <= 57)
	{
		res *= 10;
		res += *s - 48;
		s++;
	}
	return (res);
}

int	ft_get_params(int ac, char **av, t_data *data)
{
	int	i;

	if (ac < 4 || ac > 5)
		return (-1);
	i = -1;
	while (++i < ac && ft_isdigits(av[i]))
		;
	if (i < ac)
		return (-1);
	data->p_nb = ft_atoi(av[0]);
	data->t_die = ft_atoi(av[1]);
	data->t_eat = ft_atoi(av[2]);
	data->t_sleep = ft_atoi(av[3]);
	data->t_m_eat = 0;
	if (ac == 5)
		data->t_m_eat = ft_atoi(av[4]);
	return (0);
}
