/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:27:25 by nrabehar          #+#    #+#             */
/*   Updated: 2024/07/17 16:29:19 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# ifndef PH_COLORS
#  define C_RED "\e[1;31m"
#  define C_GREEN "\e[1;32m"
#  define C_YELLOW "\e[1;33m"
#  define C_BLUE "\e[1;34m"
#  define C_RESET "\e[0m"
# endif

# ifndef PH_CONST
#  define NB_PHILO 0
#  define T_DIE 1
#  define T_EAT 2
#  define T_SLEEP 3
#  define MUST_EAT 4
#  define T_THINK 5
#  define T_START 6
#  define PH_CONST 7
# endif

typedef struct s_philo
{
	int				id;
	int				nb_eat;
	long			last_eat;
	int				is_eating;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_t		thread;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	long			av[PH_CONST];
	int				all_eat;
	int				dead;
	pthread_mutex_t	*forks;
	t_philo			*philo;
	pthread_mutex_t	routine_lock;
}					t_data;

// Utils

void				ph_error(char *s);
long				ph_atol(char *s);
long				ph_get_time(void);
void				ph_msleep(long ms, t_data *data);
int					ph_print(t_philo *philo, char *state, int(can)(t_philo *));

// Settings

int					validate_args(int ac, char **av);
int					ph_init_data(int ac, char **av, t_data *data);
void				ph_destroy_forks(t_data *data, int limit);
void				ph_destroy(t_data *data);

// Routine

void				ph_take_fork(t_philo *philo);
void				ph_drop_fork(t_philo *philo);
void				ph_eat(t_philo *philo);
void				ph_sleep(t_philo *philo);
void				ph_think(t_philo *philo);
int					ph_can_continue(t_philo *philo);
int					ph_observe(t_data *data);

#endif