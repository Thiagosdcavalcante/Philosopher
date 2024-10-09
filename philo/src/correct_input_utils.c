/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct_input_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:36:31 by tsantana          #+#    #+#             */
/*   Updated: 2024/10/09 18:26:20 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <unistd.h>

void	my_print_func(t_philos *phl, int type)
{
	int		is_dead;
	long	time;

	time = my_print_sup(phl->reference);
	pthread_mutex_lock(&phl->reference->m_dead);
	is_dead = phl->reference->dead;
	pthread_mutex_unlock(&phl->reference->m_dead);
	if (is_dead == 1)
		return ;
	pthread_mutex_lock(&phl->reference->write);
	if (type == HAS_FORK)
		printf("%ld %d "MAG"has taken a fork\n"RESET,
			time, phl->id);
	else if (type == EATING)
		printf("%ld %d "MAG"is eating\n"RESET,
			time, phl->id);
	else if (type == SLEEPING)
		printf("%ld %d " CYAN "is sleeping\n" RESET,
			time, phl->id);
	else if (type == THINKING)
		printf("%ld %d " GRN "is thinking\n" RESET,
			time, phl->id);
	else if (type == DEAD)
		printf("%ld %d " RED "died\n" RESET,
			time, phl->id);
	pthread_mutex_unlock(&phl->reference->write);
}

void	ft_thinking(t_philos *philo)
{
	my_print_func(philo, THINKING);
	/* usleep((philo->reference->time_die - (philo->reference->time_eat + philo->reference->time_sleep) - 100) * 1000); */
	usleep(50);
}

void	join_threads(t_philos **phl, int stop, t_monitor *mntr)
{

	(void)mntr; 
	while ((*phl)->id > (*phl)->prv->id)
		(*phl) = (*phl)->prv;
	while ((*phl)->id <= stop)
	{
		pthread_join((*phl)->philo, NULL);
		if ((*phl)->id == stop)
		{
			(*phl) = (*phl)->nxt;
			break ;
		}
		(*phl) = (*phl)->nxt;
	}
}

static void	put_time_pthread(t_philos **phl)
{
	(*phl)->last_meal = usec_definition();
	pthread_create(&(*phl)->philo, NULL, philo_routine, (void *)(*phl));
}

void	init_philos_aux(t_philos **phl, int stop)
{
	(*phl)->reference->born = usec_definition();
	while ((*phl)->id <= stop)
	{
		if ((*phl)->id % 2 != 0)
			put_time_pthread(phl);
		if ((*phl)->id == stop)
			break;
		(*phl) = (*phl)->nxt;
	}
	(*phl) = (*phl)->nxt;
	while ((*phl)->id <= stop)
	{
		if ((*phl)->id % 2 == 0)
			put_time_pthread(phl);
		if ((*phl)->id == stop)
			break;
		(*phl) = (*phl)->nxt;
	}
	(*phl) = (*phl)->nxt;
}
