/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 21:16:28 by tsantana          #+#    #+#             */
/*   Updated: 2024/08/25 20:07:39 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <bits/types/struct_timeval.h>
# include <stdio.h>
# include <stdlib.h>
#include <sys/select.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define RED	"\x1b[31m"
# define RESET	"\x1b[0m"
# define MAG	"\033[0;35m"
# define GRN	"\x1b[32m"

# define MAX_PHILOS 200

typedef pthread_mutex_t	t_mutex;
typedef suseconds_t		t_usec;


typedef struct s_general
{
	long			usec;
	long			time_eat;
	long			time_sleep;
	long			time_die;
	int				dead;
	int				qnt_philos;
	int				qnt_forks;
	int				max_meals;
	t_mutex			m_dead;
	t_mutex			write;
}	t_general;

typedef struct s_philos
{
	pthread_t		philo;
	long			born;
	int				id;
	int				qnt_meal;
	t_mutex			f_left;
	t_mutex			*f_right;
	t_mutex			*meal;
	t_general		*reference;
	struct s_philos	*nxt;
	struct s_philos	*prv;
}	t_philos;

typedef struct s_monitor
{
	pthread_t	monitors;
	t_philos	*phl;
	t_general	*gnrl;
}	t_monitor;

enum e_status
{
	HAS_FORK = 0,
	EATING,
	SLEEPING,
	THINKING,
	DEAD
};

void		ft_print_instructions(void);
void		correct_input(char **av, t_monitor *mntr);
void		print_philo_activity(t_general *gnrl, t_philos *phl, int type);
void		final_free(t_general *gnrl);
void		*monitor_routine(void *gnrl);
void		*philo_routine(void *arg);
void		get_timer_routines(t_general **gnrl, char **av);
void		init_philos_aux(t_philos **phl, int stop, t_general **gnrl);
void		write_mutex(t_general *gnrl, t_philos *phl, char *msg, t_usec time);
long		usec_definition(void);
void		*one_philo(void *arg);
int			ft_atoi(const char *nptr);
t_philos	*make_philo_order(int num, t_general **gnrl);

#endif
