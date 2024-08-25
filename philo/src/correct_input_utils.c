/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct_input_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:36:31 by tsantana          #+#    #+#             */
/*   Updated: 2024/08/25 20:07:25 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	write_mutex(t_general *gnrl, t_philos *phl, char *msg, t_usec time)
{
	pthread_mutex_lock(&gnrl->write);
	if (gnrl->dead != 1)
		printf("%ld %d %s\n", time, phl->id, msg);
	pthread_mutex_unlock(&gnrl->write);
}

void	print_philo_activity(t_general *gnrl, t_philos *phl, int type)
{
	if (type == HAS_FORK)
		write_mutex(gnrl, phl, " has a new fork!", usec_definition());
	else if (type == EATING)
		write_mutex(gnrl, phl, " is eating!", usec_definition());
	else if (type == SLEEPING)
		write_mutex(gnrl, phl, " is sleeping!", usec_definition());
	else if (type == THINKING)
		write_mutex(gnrl, phl, " is thinking!", usec_definition());
	else if (type == DEAD)
		write_mutex(gnrl, phl, " is DEAD!", usec_definition());
}

static void	join_threads(t_philos **phl, int stop)
{
	while ((*phl)->id != stop)
	{
		pthread_join((*phl)->philo, NULL);
		(*phl) = (*phl)->nxt;
	}
}

void	init_philos_aux(t_philos **phl, int stop, t_general **gnrl)
{
	while ((*phl)->id != stop)
	{
		usleep(1 * 10);
		if ((*phl)->id % 2 != 0)
			pthread_create(&(*phl)->philo, NULL, philo_routine, (void *)(*gnrl));
		(*phl) = (*phl)->nxt;
	}
	(*phl) = (*phl)->nxt;
	while ((*phl)->id != stop)
	{
		usleep(1 * 10);
		if ((*phl)->id % 2 == 0)
			pthread_create(&(*phl)->philo, NULL, philo_routine, (void *)(*gnrl));
		(*phl) = (*phl)->nxt;
	}
	pthread_join((*phl)->philo, NULL);
	(*phl) = (*phl)->nxt;
	join_threads(phl, stop);
}
