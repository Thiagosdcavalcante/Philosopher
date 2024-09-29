/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct_input_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:36:31 by tsantana          #+#    #+#             */
/*   Updated: 2024/09/29 18:30:35 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void	write_mutex(t_general *gnrl, t_philos *phl, char *msg, t_usec time)
{
	pthread_mutex_lock(&gnrl->write);
	pthread_mutex_lock(&gnrl->m_dead);
	pthread_mutex_lock(&phl->death);
	if (gnrl->dead == 0 || phl->is_dead == 0)
	{
		pthread_mutex_unlock(&phl->death);
		pthread_mutex_unlock(&gnrl->m_dead);
		printf("PHILO:%d -> %s TIME:%ld\n", phl->id, msg, time);
	}
	pthread_mutex_unlock(&gnrl->write);
}

void	print_philo_activity(t_general *gnrl, t_philos *phl, int type)
{
	if (type == HAS_FORK)
		write_mutex(gnrl, phl, " has a new fork!", (usec_definition() - phl->last_meal) / 1000);
	else if (type == EATING)
		write_mutex(gnrl, phl, " is eating!", (usec_definition() - phl->last_meal) / 1000);
	else if (type == SLEEPING)
		write_mutex(gnrl, phl, " is sleeping!", (usec_definition() - phl->last_meal) / 1000);
	else if (type == THINKING)
		write_mutex(gnrl, phl, " is thinking!", (usec_definition() - phl->last_meal) / 1000);
	else if (type == DEAD)
		write_mutex(gnrl, phl, " is DEAD!", (usec_definition() - phl->last_meal) / 1000);
}

void	join_threads(t_philos **phl, int stop)
{
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
	pthread_create(&(*phl)->philo, NULL, philo_odd_routine, (void *)(*phl));
}

void	init_philos_aux(t_philos **phl, int stop)
{
	while ((*phl)->id <= stop)
	{
		usleep(15);
		if ((*phl)->id % 2 != 0)
			put_time_pthread(phl);
		if ((*phl)->id == stop)
		{
			(*phl) = (*phl)->nxt;
			break ;
		}
		(*phl) = (*phl)->nxt;
	}
	while ((*phl)->id <= stop)
	{
		usleep(15);
		if ((*phl)->id % 2 == 0)
			put_time_pthread(phl);
		if ((*phl)->id == stop)
		{
			(*phl) = (*phl)->nxt;
			break ;
		}
		(*phl) = (*phl)->nxt;
	}
}
