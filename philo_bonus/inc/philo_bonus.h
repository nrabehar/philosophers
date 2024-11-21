/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:27:25 by nrabehar          #+#    #+#             */
/*   Updated: 2024/07/23 11:32:39 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# ifndef PH_COLORS
#  define C_RED "\e[1;31m"
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
#  define PH_MAX 242
# endif

# ifndef PH_SEMS
#  define PH_SEM_FORKS "/ph_forks_sem"
#  define PH_SEM_ROUTINE "/ph_routine_sem"
#  define PH_SEM_PRINT "/ph_print_sem"
#  define PH_SEM_STOP "/ph_stop_sem"
# endif

typedef struct s_philo
{
	int				id;
	int				nb_eat;
	int				is_eating;
	int				stop;
	long			last_eat;
	pid_t			self;
	pthread_t		observer;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	long			av[PH_CONST];
	t_philo			philo[PH_MAX];
	sem_t			*forks;
	sem_t			*routine_sem;
	sem_t			*print_sem;
	sem_t			*stop_sem;
}					t_data;

void				ph_error(char *s);
long				ph_atol(char *s);
long				ph_get_time(void);
void				ph_msleep(long ms);
void				ph_print(t_philo *philo, char *state);
int					validate_args(int ac, char **av);
int					ph_revalide_data(t_data *data);
int					ph_init_data(int ac, char **av, t_data *data);
void				ph_destroy(t_data *data);
void				ph_take_fork(t_philo *philo);
void				ph_drop_fork(t_philo *philo);
void				ph_eat(t_philo *philo);
void				ph_sleep(t_philo *philo);
void				ph_think(t_philo *philo);
int					ph_can_continue(t_philo *philo);
void				*ph_observe(void *arg);

#endif