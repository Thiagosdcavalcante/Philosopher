/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 21:16:28 by tsantana          #+#    #+#             */
/*   Updated: 2024/10/10 19:33:29 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <bits/types/struct_timeval.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/select.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

# define RED	"\x1b[31m"
# define RESET	"\x1b[0m"
# define MAG	"\033[0;35m"
# define GRN	"\x1b[32m"
# define CYAN	"\033[0;36m"

# define MAX_PHILOS 200

typedef pthread_mutex_t	t_mutex;
typedef suseconds_t		t_usec;

typedef struct s_general
{
	long			born;
	long			time_eat;
	long			time_sleep;
	long			time_die;
	int				dead;
	int				everyone_eat;
	int				qnt_philos;
	int				qnt_forks;
	int				max_meals;
	t_mutex			m_dead;
	t_mutex			everyone;
	t_mutex			m_born;
	t_mutex			m_meal;
	t_mutex			m_sleep;
	t_mutex			m_die;
	t_mutex			write;
}	t_general;

typedef struct s_philos
{
	pthread_t		philo;
	long			last_meal;
	int				id;
	int				qnt_meal;
	int				is_dead;
	t_mutex			f_left;
	t_mutex			m_last;
	t_mutex			death;
	t_mutex			*f_right;
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

void		*philo_routine(void *arg);
void		*ft_monitoring(void *arg);
void		ft_print_instructions(void);
void		correct_input(char **av, t_monitor *mntr);
void		*monitor_routine(void *gnrl);
void		destroy_everything(t_monitor *mntr);
void		get_timer_routines(t_general **gnrl, char **av);
void		init_philos_aux(t_philos **phl, int stop);
void		ft_putendl_fd(char *s, int fd);
void		*one_philo(void *arg);
void		join_threads(t_philos **phl, int stop);
void		sleeping_sup(t_philos *phl, int die);
void		my_print_func(t_philos *phl, int type);
void		ft_thinking(t_philos *philo);
void		print_dead(t_monitor *mntr, int id);
long		usec_definition(void);
long		ft_atol(const char *nptr);
int			my_print_sup(t_general *gnrl);
int			ft_is_dead(t_philos *phl);
int			phl_routine_sup(t_philos *phl);
int			is_number(char numb);
int			my_print_dead(t_philos *phl);
t_philos	*make_philo_order(int num, t_general *gnrl);
t_general	*general_init(char **av);

#endif
