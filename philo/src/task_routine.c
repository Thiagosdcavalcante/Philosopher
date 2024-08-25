/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:15:37 by tsantana          #+#    #+#             */
/*   Updated: 2024/08/25 19:41:38 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

static void	ft_sleeping(t_philos *philo, t_general *gnrl)
{
	if ((gnrl->time_die - (philo->born + gnrl->time_sleep)) > 0)
	{
		print_philo_activity(gnrl, philo, SLEEPING);
		usleep(gnrl->time_sleep);
	}
	else
	{
		print_philo_activity(gnrl, philo, SLEEPING);
		usleep(gnrl->time_die - philo->born);
		print_philo_activity(gnrl, philo, DEAD);
		pthread_mutex_lock(&gnrl->m_dead);
		gnrl->dead = 1;
		pthread_mutex_unlock(&gnrl->m_dead);
	}
}

static void	ft_thinking(t_philos *philo, t_general *gnrl)
{
	if ((gnrl->time_die - (philo->born + (8 * 1000))) > 0)
	{
		print_philo_activity(gnrl, philo, THINKING);
		usleep(8 * 1000);
	}
	else
	{
		print_philo_activity(gnrl, philo, THINKING);
		usleep(gnrl->time_die - philo->born);
		print_philo_activity(gnrl, philo, DEAD);
		pthread_mutex_lock(&gnrl->m_dead);
		gnrl->dead = 1;
		pthread_mutex_unlock(&gnrl->m_dead);
	}
}

static void	ft_eat(t_philos *philo, t_general *gnrl)
{
	pthread_mutex_lock(philo->meal);
	if ((philo->qnt_meal >= 1 && gnrl->max_meals != 0)
		|| (philo->qnt_meal == 0 && gnrl->max_meals == 0))
	{
		pthread_mutex_lock(&philo->f_left);
		print_philo_activity(gnrl, philo, HAS_FORK);
		pthread_mutex_lock(philo->f_right);
		print_philo_activity(gnrl, philo, HAS_FORK);
		print_philo_activity(gnrl, philo, EATING);
		philo->born = usec_definition();
		if (gnrl->max_meals != 0)
			philo->qnt_meal--;
		usleep(gnrl->time_eat);
		pthread_mutex_unlock(&philo->f_left);
		pthread_mutex_unlock(philo->f_right);
	}
	pthread_mutex_unlock(philo->meal);
}

void	*philo_routine(void *arg)
{
	t_philos	*phl;

	phl = (t_philos *)arg;
	if ((phl->id % 2) == 0)
	{
		ft_sleeping(phl, phl->reference);
		ft_thinking(phl, phl->reference);
		ft_eat(phl, phl->reference);
	}
	else if ((phl->id % 2) == 1)
	{
		ft_eat(phl, phl->reference);
		ft_thinking(phl, phl->reference);
		ft_sleeping(phl, phl->reference);
	}
	return (arg);
}
