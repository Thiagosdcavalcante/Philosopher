/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sup_for_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:58:06 by tsantana          #+#    #+#             */
/*   Updated: 2024/09/29 17:31:51 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

t_general	*general_init(char **av)
{
	t_general	*gnrl;

	gnrl = malloc(sizeof(t_general));
	gnrl->usec = usec_definition();
	gnrl->time_die = ft_atol(av[2]);
	gnrl->time_eat = ft_atol(av[3]);
	gnrl->time_sleep = ft_atol(av[4]);
	gnrl->dead = 0;
	gnrl->qnt_philos = ft_atol(av[1]);
	gnrl->qnt_forks = ft_atol(av[1]);
	gnrl->max_meals = 0;
	pthread_mutex_init(&gnrl->write, NULL);
	pthread_mutex_init(&gnrl->m_meal, NULL);
	pthread_mutex_init(&gnrl->m_sleep, NULL);
	pthread_mutex_init(&gnrl->m_die, NULL);
	pthread_mutex_init(&gnrl->m_dead, NULL);
	return (gnrl);
}
