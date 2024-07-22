/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 21:16:28 by tsantana          #+#    #+#             */
/*   Updated: 2024/07/21 16:46:08 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define RED	"\x1b[31m"
# define RESET	"\x1b[0m"
# define MAG	"\033[0;35m"
# define GRN	"\x1b[32m"

typedef pthread_mutex_t	t_mutex;

typedef struct s_philos
{
	int				philo;
	t_mutex			*f_left;
	t_mutex			*f_right;
	t_mutex			*meal;
	t_mutex			*dead;
	struct s_philos	*nxt;
	struct s_philos	*prv;
}	t_philos;

typedef struct s_general
{
	t_philos	*philos;
	long		time_eat;
	long		time_sleep;
	int			monitors;
	int			qnt_philos;
	int			qnt_forks;
	int			max_meals;
	t_mutex		*write;
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
int			ft_atoi(const char *nptr);
t_philos	*make_philo_order(char *num);

#endif
