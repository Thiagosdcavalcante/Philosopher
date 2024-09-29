/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:36:24 by tsantana          #+#    #+#             */
/*   Updated: 2024/09/29 18:21:34 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"
#include <unistd.h>

void	destroy_everything(t_monitor **mntr)
{
	t_philos	*tmp;
	
	if (!(*mntr)->phl)
		return ;
	while ((*mntr)->phl)
	{
		tmp = (*mntr)->phl;
		(*mntr)->phl = (*mntr)->phl->nxt;
		pthread_mutex_destroy(&(*mntr)->phl->f_left);
		if (tmp)
		{
			free(tmp);
			tmp = NULL;
		}
	}
	if ((*mntr)->phl)
	{
		free((*mntr)->phl);
		(*mntr)->phl = NULL;
	}
	pthread_mutex_destroy(&(*mntr)->gnrl->m_dead);
	pthread_mutex_destroy(&(*mntr)->gnrl->write);
}

void	*ft_monitoring(void *arg)
{
	t_philos	*phl;
	t_monitor	*mntr;

	mntr = (t_monitor *)arg;
	phl = mntr->phl;
	pthread_mutex_lock(&mntr->gnrl->m_dead);
	while (mntr->gnrl->dead == 0)
	{
		pthread_mutex_unlock(&mntr->gnrl->m_dead);
		pthread_mutex_lock(&phl->death);
		if (phl->is_dead == 1)
		{
			pthread_mutex_unlock(&phl->death);
			print_philo_activity(mntr->gnrl, phl, DEAD);
			pthread_mutex_lock(&mntr->gnrl->m_dead);
			mntr->gnrl->dead = 1;
			pthread_mutex_unlock(&mntr->gnrl->m_dead);
			break ;
		}
		phl = phl->nxt;
		usleep(100);
	}
	return (arg);
}
