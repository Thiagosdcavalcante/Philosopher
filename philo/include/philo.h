/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 21:16:28 by tsantana          #+#    #+#             */
/*   Updated: 2024/07/27 19:11:44 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <bits/types/struct_timeval.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define RED	"\x1b[31m"
# define RESET	"\x1b[0m"
# define MAG	"\033[0;35m"
# define GRN	"\x1b[32m"

# define MAX_PHILOS 200

typedef pthread_mutex_t	t_mutex;

typedef struct s_philos
{
	pthread_t		philo;
	int				id;
	int				dead;
	int				status;
	int				status_chagend;
	t_mutex			f_left;
	t_mutex			*f_right;
	t_mutex			*meal;
	struct s_philos	*nxt;
	struct s_philos	*prv;
}	t_philos;

typedef struct s_general
{
	t_philos		*philos;
	long			usec;
	long			time_eat;
	long			time_sleep;
	pthread_t		monitors;
	int				has_dead;
	int				qnt_philos;
	int				qnt_forks;
	int				max_meals;
	t_mutex			*write;
}	t_general;

enum e_status
{
	HAS_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DEAD
};

void		ft_print_instructions(void);
void		correct_input(int ac, char **av, t_general *gnrl);
void		print_philo(t_philos *phl);
void		final_free(t_general *gnrl);
void		*monitor_routine(void *gnrl);
int			ft_atoi(const char *nptr);
t_philos	*make_philo_order(char *num);

#endif
