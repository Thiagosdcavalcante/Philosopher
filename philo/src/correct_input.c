/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:42:51 by tsantana          #+#    #+#             */
/*   Updated: 2024/08/25 20:07:19 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>
#include <unistd.h>

void	*one_philo(void *arg)
{
	t_monitor	*mntr;

	mntr = (t_monitor *)arg;
	write_mutex(mntr->gnrl, mntr->phl, " took a fork...", usec_definition());
	usleep(mntr->gnrl->time_die);
	write_mutex(mntr->gnrl, mntr->phl, " is DEAD!", usec_definition());
	return (arg);
}

static void	make_one_philo(t_philos **phl, t_general **gnrl, t_monitor **mntr)
{
	(*phl) = malloc(sizeof(t_philos));
	(*phl)->philo = 0;
	if ((*gnrl)->max_meals != 0)
		(*phl)->qnt_meal = (*gnrl)->max_meals;
	else
		(*phl)->qnt_meal = 0;
	(*phl)->meal = 0;
	(*phl)->born = usec_definition();
	(*phl)->f_left = (t_mutex){0};
	(*phl)->f_right = NULL;
	pthread_mutex_init(&(*phl)->f_left, NULL);
	(*phl)->id = 1;
	(*phl)->nxt = NULL;
	(*phl)->prv = NULL;
	pthread_create(&(*phl)->philo, NULL, &one_philo, (void *)(*mntr));
	pthread_join((*phl)->philo, NULL);
}


static void	make_philos(t_philos **phl, t_general **gnrl)
{
	(*phl) = make_philo_order((*gnrl)->qnt_philos, gnrl);
	init_philos_aux(phl, (*gnrl)->qnt_philos, gnrl);
}

void	correct_input(char **av, t_monitor *mntr)
{
	mntr->gnrl->write = (t_mutex){0};
	pthread_mutex_init(&mntr->gnrl->write, NULL);
	mntr->gnrl->qnt_philos = ft_atoi(av[1]);
	mntr->gnrl->time_eat = ft_atoi(av[2]);
	mntr->gnrl->time_sleep = ft_atoi(av[3]);
	mntr->gnrl->qnt_forks = ft_atoi(av[1]);
	if (av[6])
		mntr->gnrl->max_meals = ft_atoi(av[6]);
	if (mntr->gnrl->qnt_philos > 1)
		make_philos(&mntr->phl, &mntr->gnrl);
	else
		make_one_philo(&mntr->phl, &mntr->gnrl, &mntr);
}
