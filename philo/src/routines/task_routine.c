/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:15:37 by tsantana          #+#    #+#             */
/*   Updated: 2024/09/29 18:46:33 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

static void	ft_sleeping(t_philos *philo)
{
	long	temp;
	long	die;

	pthread_mutex_lock(&philo->reference->m_die);
	die = philo->reference->time_die * 1000;
	pthread_mutex_unlock(&philo->reference->m_die);
	print_philo_activity(philo->reference, philo, SLEEPING);
	pthread_mutex_lock(&philo->reference->m_sleep);
	temp = philo->reference->time_sleep * 1000;
	pthread_mutex_unlock(&philo->reference->m_sleep);
	pthread_mutex_lock(&philo->death);
	pthread_mutex_lock(&philo->reference->m_die);
	if (philo->is_dead == 0 && philo->reference->dead == 0)
	{
		pthread_mutex_unlock(&philo->reference->m_die);
		pthread_mutex_unlock(&philo->death);
	}
	else if ((philo->last_meal + temp) > (philo->last_meal + die))
	{
		pthread_mutex_lock(&philo->death);
		philo->is_dead = 1;
		pthread_mutex_unlock(&philo->death);
		usleep(die * 1000);
		return ;
	}
	usleep(temp * 1000);
}

static void	ft_thinking(t_philos *philo)
{
	long	die;

	pthread_mutex_lock(&philo->reference->m_die);
	die = philo->reference->time_die + philo->last_meal;
	pthread_mutex_unlock(&philo->reference->m_die);
	pthread_mutex_lock(&philo->reference->m_dead);
	pthread_mutex_lock(&philo->death);
	if (philo->is_dead == 1 || philo->reference->dead == 1)
	{
		pthread_mutex_unlock(&philo->reference->m_dead);
		pthread_mutex_unlock(&philo->death);
	}
	else if ((die - (philo->last_meal + (8 * 1000))) > 0)
	{
		pthread_mutex_unlock(&philo->reference->m_dead);
		pthread_mutex_unlock(&philo->death);
		print_philo_activity(philo->reference, philo, THINKING);
		usleep(8 * 1000);
		return ;
	}
	print_philo_activity(philo->reference, philo, THINKING);
	usleep((die - philo->last_meal) * 1000);
	pthread_mutex_lock(&philo->death);
	philo->is_dead = 1;
	pthread_mutex_unlock(&philo->death);
}

static void	ft_eat(t_philos *philo)
{
	pthread_mutex_lock(&philo->reference->m_dead);
	if (philo->reference->dead == 1)
		pthread_mutex_unlock(&philo->reference->m_dead);
	else if (philo->qnt_meal > 0 || philo->qnt_meal == -1)
	{
		pthread_mutex_lock(&philo->f_left);
		print_philo_activity(philo->reference, philo, HAS_FORK);
		pthread_mutex_lock(&philo->f_right);
		print_philo_activity(philo->reference, philo, HAS_FORK);
		philo->last_meal = usec_definition();
		print_philo_activity(philo->reference, philo, EATING);
		if (philo->qnt_meal > 0)
			philo->qnt_meal--;
		usleep(philo->reference->time_eat * 1000);
		pthread_mutex_unlock(&philo->f_left);
		pthread_mutex_unlock(&philo->f_right);
		return ;
	}
	pthread_mutex_lock(&philo->death);
	philo->is_dead = 1;
	pthread_mutex_unlock(&philo->death);
}

void	*philo_odd_routine(void *arg)
{
	t_philos	*phl;
	int			dead;

	phl = (t_philos *)arg;
	pthread_mutex_lock(&phl->death);
	pthread_mutex_lock(&phl->reference->m_dead);
	while (phl->is_dead == 0 || phl->reference->dead == 0)
	{
		pthread_mutex_unlock(&phl->reference->m_dead);
		pthread_mutex_unlock(&phl->death);
		ft_eat(phl);
		ft_sleeping(phl);
		pthread_mutex_lock(&phl->death);
		dead = phl->is_dead;
		pthread_mutex_unlock(&phl->death);
		if (dead == 1)
			break ;
		ft_thinking(phl);
		pthread_mutex_lock(&phl->death);
		dead = phl->is_dead;
		pthread_mutex_unlock(&phl->death);
		if (dead == 1)
			break ;
	}
	return (arg);
}

void	*philo_pair_routine(void *arg)
{
	t_philos	*phl;
	int			dead;

	phl = (t_philos *)arg;
	pthread_mutex_lock(&phl->death);
	pthread_mutex_lock(&phl->reference->m_dead);
	while (phl->is_dead == 0 || phl->reference->dead == 0)
	{
		pthread_mutex_unlock(&phl->death);
		pthread_mutex_unlock(&phl->reference->m_dead);
		ft_thinking(phl);
		pthread_mutex_lock(&phl->death);
		dead = phl->is_dead;
		pthread_mutex_unlock(&phl->death);
		if (dead == 1)
			break ;
		ft_eat(phl);
		ft_sleeping(phl);
		pthread_mutex_lock(&phl->death);
		dead = phl->is_dead;
		pthread_mutex_unlock(&phl->death);
		if (dead == 1)
			break ;
	}
	return (arg);
}
