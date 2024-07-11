/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:27:25 by nrabehar          #+#    #+#             */
/*   Updated: 2024/07/11 10:23:33 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

# ifndef PH_COLORS
#  define C_RED "\e[1;31m"
#  define C_GREEN "\e[1;32m"
#  define C_YELLOW "\e[1;33m"
#  define C_BLUE "\e[1;34m"
#  define C_RESET "\e[0m"
# endif

# ifndef PH_MAX
#  define PH_MAX 242
# endif

typedef struct s_philo
{
	int				id;
	int				nb_eat;
	long			t_start;
	long			last_eat;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*print_lock;
	pthread_t		thread;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				p_nb;
	int				must_eat;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	int				all_eat;
	int				dead;
	pthread_mutex_t	forks[PH_MAX];
	t_philo			philo[PH_MAX];
	pthread_t		monitor;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	routine_lock;
}					t_data;

// Utils

void				ft_putstr_fd(int fd, char *s);
long				ph_atol(char *s);
long				ph_get_time(void);
void				ph_msleep(long ms, t_data *data);

// Settings

int					validate_args(int ac, char **av);
int					ph_init_data(int ac, char **av, t_data *data);
int					ph_init_mutex(t_data *data);
void				ph_destroy_mutex(t_data *data);
int					ph_print(t_philo *philo, char *state, int(can)(t_philo *));

// Routine

void				ph_take_fork(t_philo *philo);
void				ph_eating_action(t_philo *philo);
void				ph_sleeping_action(t_philo *philo);
void				ph_thinking_action(t_philo *philo);
int					ph_can_continue(t_philo *philo);
void				*ph_routine(void *arg);
void				*ph_monitor(void *arg);

#endif