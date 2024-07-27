/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:42:51 by tsantana          #+#    #+#             */
/*   Updated: 2024/07/27 19:11:33 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	set_next_forks(t_general **gnrl)
{
	int			stop;
	t_philos	*phl;

	phl = (*gnrl)->philos;
	stop = phl->id;
	if (phl->nxt)
		phl->f_right = &phl->nxt->f_left;
	phl = phl->nxt;
	while (phl->id != stop)
	{
		phl->f_right = &phl->nxt->f_left;
		phl = phl->nxt;
	}
	(*gnrl)->philos = phl;
}

static void	action_5(t_general *gnrl, char **av, int ac)
{
	gnrl->philos = make_philo_order(av[1]);
	set_next_forks(&gnrl);
	pthread_create(&gnrl->monitors, NULL, monitor_routine, (void *) gnrl);
	print_philo(gnrl->philos);
}

static void	action_6(t_general *gnrl, char **av, int ac)
{
	gnrl->philos = make_philo_order(av[1]);
	set_next_forks(&gnrl);
	print_philo(gnrl->philos);
	printf("forks: %d\n", gnrl->qnt_forks);
}

void	correct_input(int ac, char **av, t_general *gnrl)
{
	int	i;

	i = 1;
	gnrl->qnt_philos = ft_atoi(av[1]);
	/* printf("philos: %d\n", gnrl->qnt_philos); */
	gnrl->time_eat = ft_atoi(av[2]);
	/* printf("eat: %ld\n", gnrl->time_eat); */
	gnrl->time_sleep = ft_atoi(av[3]);
	/* printf("sleep: %ld\n", gnrl->time_sleep); */
	gnrl->qnt_forks = ft_atoi(av[1]);
	/* printf("forks: %d\n", gnrl->qnt_forks); */
	if (av[6])
		gnrl->max_meals = ft_atoi(av[6]);
	if (ac == 5)
		action_5(gnrl, av, ac);
	else
		action_6(gnrl, av, ac);
}
