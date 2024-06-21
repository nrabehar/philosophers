/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:27:25 by nrabehar          #+#    #+#             */
/*   Updated: 2024/06/21 09:02:11 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

# ifndef P_COLORS
#  define C_RED "\e[1;31m"
#  define C_RESET "\e[0m"
# endif

typedef struct s_data
{
	unsigned int	p_nb;
	unsigned int	t_die;
	unsigned int	t_eat;
	unsigned int	t_sleep;
	unsigned int	t_m_eat;
}					t_data;

int					ft_putstr_fd(int fd, char *s);
int					ft_get_params(int ac, char **av, t_data *data);

#endif