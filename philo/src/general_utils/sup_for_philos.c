/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sup_for_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:58:06 by tsantana          #+#    #+#             */
/*   Updated: 2024/10/09 18:07:11 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

t_general	*general_init(char **av)
{
	t_general	*gnrl;

	gnrl = malloc(sizeof(t_general));
	gnrl->born = usec_definition();
	gnrl->time_die = ft_atol(av[2]);
	gnrl->time_eat = ft_atol(av[3]);
	gnrl->time_sleep = ft_atol(av[4]);
	gnrl->dead = 0;
	gnrl->qnt_philos = ft_atol(av[1]);
	gnrl->qnt_forks = ft_atol(av[1]);
	gnrl->max_meals = 0;
	gnrl->everyone_eat = -1;
	pthread_mutex_init(&gnrl->everyone, NULL);
	pthread_mutex_init(&gnrl->m_born, NULL);
	pthread_mutex_init(&gnrl->write, NULL);
	pthread_mutex_init(&gnrl->m_meal, NULL);
	pthread_mutex_init(&gnrl->m_sleep, NULL);
	pthread_mutex_init(&gnrl->m_die, NULL);
	pthread_mutex_init(&gnrl->m_dead, NULL);
	return (gnrl);
}

int	phl_routine_sup(t_philos *phl)
{
	int		dead;
	int		someone_die;;

	pthread_mutex_lock(&phl->death);
	dead = phl->is_dead;
	pthread_mutex_unlock(&phl->death);
	pthread_mutex_lock(&phl->reference->m_dead);
	someone_die = phl->reference->dead;
	pthread_mutex_unlock(&phl->reference->m_dead);
	if (dead == 0 && someone_die == 1)
	{
		dead = 1;
		pthread_mutex_lock(&phl->death);
		phl->is_dead = 1;
		pthread_mutex_unlock(&phl->death);
	}
	return (dead);
}

void	sleeping_sup(t_philos *phl, int die)
{
	pthread_mutex_lock(&phl->death);
	phl->is_dead = 1;
	pthread_mutex_unlock(&phl->death);
	usleep(die * 1000);
}

int	ft_is_dead(t_philos *phl)
{
	long	last_meal;
	int		time_to_die;
	int		phl_die;
	int		someone_die;

	pthread_mutex_lock(&phl->death);
	phl_die = phl->is_dead;
	pthread_mutex_unlock(&phl->death);
	pthread_mutex_lock(&phl->reference->m_dead);
	someone_die = phl->reference->dead;
	pthread_mutex_unlock(&phl->reference->m_dead);
	if (phl_die == 1 || someone_die == 1)
		return (1);
	pthread_mutex_lock(&phl->m_last);
	last_meal = phl->last_meal;
	pthread_mutex_unlock(&phl->m_last);
	pthread_mutex_lock(&phl->reference->m_die);
	time_to_die = phl->reference->time_die;
	pthread_mutex_unlock(&phl->reference->m_die);
	if ((usec_definition() - last_meal) > time_to_die)
		return (1);
	return (0);
}
