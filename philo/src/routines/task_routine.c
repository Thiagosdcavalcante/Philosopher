/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:15:37 by tsantana          #+#    #+#             */
/*   Updated: 2024/10/09 18:11:47 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"
#include <pthread.h>

static void	ft_sleeping(t_philos *philo)
{
	long	temp;
	long	die;
	long	last_meal;

	pthread_mutex_lock(&philo->reference->m_die);
	die = philo->reference->time_die;
	pthread_mutex_unlock(&philo->reference->m_die);
	pthread_mutex_lock(&philo->reference->m_sleep);
	temp = philo->reference->time_sleep;
	pthread_mutex_unlock(&philo->reference->m_sleep);
	my_print_func(philo, SLEEPING);
	pthread_mutex_lock(&philo->m_last);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->m_last);
	if ((usec_definition() - last_meal) >= die)
	{
		sleeping_sup(philo, die);
		return ;
	}
	usleep(temp * 1000);
}

static void	sup_for_eating(t_philos *philo)
{
	int	meal;

	meal = 0;
	pthread_mutex_lock(&philo->reference->m_meal);
	meal = philo->reference->time_eat;
	pthread_mutex_unlock(&philo->reference->m_meal);
	usleep(meal * 1000);
	if (philo->id % 2 != 0)
	{
		pthread_mutex_unlock(&philo->f_left);
		pthread_mutex_unlock(philo->f_right);
	}
	else if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->f_right);
		pthread_mutex_unlock(&philo->f_left);
	}
}

static void	cond_mutex_order(t_philos *phl)
{
	if (phl->id % 2 != 0)
	{
		pthread_mutex_lock(&phl->f_left);
		my_print_func(phl, HAS_FORK);
		pthread_mutex_lock(phl->f_right);
		my_print_func(phl, HAS_FORK);
	}
	else if (phl->id % 2 == 0)
	{
		pthread_mutex_lock(phl->f_right);
		my_print_func(phl, HAS_FORK);
		pthread_mutex_lock(&phl->f_left);
		my_print_func(phl, HAS_FORK);
	}
}

static void	ft_eat(t_philos *philo)
{
	cond_mutex_order(philo);
	if (philo->qnt_meal > 0)
	{
		pthread_mutex_lock(&philo->m_last);
		philo->last_meal = usec_definition();
		pthread_mutex_unlock(&philo->m_last);
		my_print_func(philo, EATING);
		if (philo->qnt_meal > 0)
			philo->qnt_meal--;
		sup_for_eating(philo);
		return ;
	}
	else if (philo->qnt_meal == -1)
	{
		pthread_mutex_lock(&philo->m_last);
		philo->last_meal = usec_definition();
		pthread_mutex_unlock(&philo->m_last);
		my_print_func(philo, EATING);
		sup_for_eating(philo);
		return ;
	}
	sup_for_eating(philo);
}

void	*philo_routine(void *arg)
{
	t_philos	*phl;

	phl = (t_philos *)arg;
	while (phl_routine_sup(phl) == 0 && ft_is_dead(phl) == 0)
	{
		ft_eat(phl);
		if (phl->qnt_meal == 0)
		{
			pthread_mutex_lock(&phl->reference->everyone);
			phl->reference->everyone_eat += 1;
			pthread_mutex_unlock(&phl->reference->everyone);
			return (arg);
		}
		ft_sleeping(phl);
		if (phl_routine_sup(phl) == 0 && ft_is_dead(phl) == 0)
			ft_thinking(phl);
		else if (phl->qnt_meal != 0)
		{
			pthread_mutex_lock(&phl->death);
			phl->is_dead = 1;
			pthread_mutex_unlock(&phl->death);
			return (arg);
		}
	}
	return (arg);
}
