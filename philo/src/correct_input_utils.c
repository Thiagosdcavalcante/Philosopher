/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct_input_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:36:31 by tsantana          #+#    #+#             */
/*   Updated: 2024/10/10 19:48:10 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	my_print_func(t_philos *phl, int type)
{
	long	time;

	time = my_print_sup(phl->reference);
	pthread_mutex_lock(&phl->reference->write);
	if (my_print_dead(phl) == 1)
	{
		pthread_mutex_unlock(&phl->reference->write);
		return ;
	}
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
	usleep(200);
}

void	join_threads(t_philos **phl, int stop)
{
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
			break ;
		(*phl) = (*phl)->nxt;
	}
	(*phl) = (*phl)->nxt;
	while ((*phl)->id <= stop)
	{
		if ((*phl)->id % 2 == 0)
			put_time_pthread(phl);
		if ((*phl)->id == stop)
			break ;
		(*phl) = (*phl)->nxt;
	}
	(*phl) = (*phl)->nxt;
}
