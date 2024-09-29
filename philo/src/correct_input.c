/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:42:51 by tsantana          #+#    #+#             */
/*   Updated: 2024/09/29 18:34:50 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*one_philo(void *arg)
{
	t_monitor	*mntr;

	mntr = (t_monitor *)arg;
	write_mutex(mntr->gnrl, mntr->phl, " took a fork...", (usec_definition()
		- mntr->phl->last_meal) / 1000);
	usleep(mntr->gnrl->time_die * 1000);
	write_mutex(mntr->gnrl, mntr->phl, " is DEAD!", (usec_definition()
		- mntr->phl->last_meal) / 1000 );
	return (arg);
}

static void	make_one_philo(t_philos **phl, t_general *gnrl, t_monitor **mntr)
{
	int	max_meals;

	pthread_mutex_lock(&gnrl->m_meal);
	max_meals = (*gnrl).max_meals;
	pthread_mutex_unlock(&gnrl->m_meal);
	(*phl) = malloc(sizeof(t_philos));
	(*phl)->philo = 0;
	if (max_meals > 0)
		(*phl)->qnt_meal = max_meals;
	else
		(*phl)->qnt_meal = -1;
	(*phl)->last_meal = usec_definition();
	(*phl)->f_right = (t_mutex){0};
	(*phl)->reference = gnrl;	
	(*phl)->id = 1;
	(*phl)->nxt = NULL;
	(*phl)->prv = NULL;
	pthread_mutex_init(&(*phl)->f_left, NULL);
	pthread_mutex_init(&(*phl)->death, NULL);
	pthread_create(&(*phl)->philo, NULL, &one_philo, (void *)(*mntr));
}


static void	make_philos(t_philos **phl, t_general *gnrl, t_monitor *mntr)
{
	(*phl) = make_philo_order(gnrl->qnt_philos, gnrl);
	mntr->monitors = pthread_create(&mntr->monitors, NULL, ft_monitoring, mntr);
	init_philos_aux(phl, gnrl->qnt_philos);
}

void	correct_input(char **av, t_monitor *mntr)
{
	mntr->gnrl = (t_general *){0};
	mntr->gnrl = general_init(av);
	if (av[5])
		mntr->gnrl->max_meals = ft_atol(av[5]);
	else
	 	mntr->gnrl->max_meals = -1;
	if (mntr->gnrl->qnt_philos > 1)
		make_philos(&mntr->phl, mntr->gnrl, mntr);
	else
		make_one_philo(&mntr->phl, mntr->gnrl, &mntr);
	pthread_join(mntr->monitors, NULL);
	join_threads(&mntr->phl, mntr->gnrl->qnt_philos);
}
