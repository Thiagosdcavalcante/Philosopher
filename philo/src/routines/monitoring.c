/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:36:24 by tsantana          #+#    #+#             */
/*   Updated: 2024/10/07 21:29:50 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

static int	check_for_food(t_monitor *mntr)
{
	int	everyone_eat;

	pthread_mutex_lock(&mntr->gnrl->everyone);
	everyone_eat = mntr->gnrl->everyone_eat;
	pthread_mutex_unlock(&mntr->gnrl->everyone);
	if (everyone_eat == mntr->gnrl->qnt_philos)
		return (1);
	return (0);
}

void	destroy_everything(t_monitor *mntr)
{
	t_philos	*tmp;
	t_philos	*philos;
	
	if (!mntr->phl)
		return ;
	philos = mntr->phl;
	while (philos->id < mntr->gnrl->qnt_philos)
	{
		tmp = philos;
		philos = philos->nxt;
		if (tmp)
			free(tmp);
	}
	free(philos);
	free(mntr->gnrl);
	
}

void	*ft_monitoring(void *arg)
{
	t_monitor	*mntr;
	t_philos	*phl;
	int			phl_dead;

	mntr = (t_monitor *)arg;
	phl = mntr->phl;
	phl_dead = 0;
	while (1)
	{
		if (check_for_food(mntr) == 1)
			return (arg);
		if (ft_is_dead(phl))
		{
			my_print_func(phl, DEAD);
			pthread_mutex_lock(&mntr->gnrl->m_dead);
			mntr->gnrl->dead = 1;
			pthread_mutex_unlock(&mntr->gnrl->m_dead);
			return (arg);
		}
		usleep(1000);
		phl = phl->nxt;
	}
	return (arg);
}
