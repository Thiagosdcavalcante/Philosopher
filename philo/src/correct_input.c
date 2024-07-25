/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:42:51 by tsantana          #+#    #+#             */
/*   Updated: 2024/07/25 19:50:17 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	set_next_forks(t_general **gnrl)
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

void	correct_input(int ac, char **av, t_general *gnrl)
{
	int	i;

	i = 1;
	if (ac == 5)
	{
		gnrl->philos = make_philo_order(av[1]);
		set_next_forks(&gnrl);
		print_philo(gnrl->philos);
	}
	else
	{
		if (av[6])
			gnrl->max_meals = ft_atoi(av[6]);
		gnrl->philos = make_philo_order(av[1]);
		set_next_forks(&gnrl);
		print_philo(gnrl->philos);
		printf("forks: %d\n", gnrl->qnt_forks);
	}
	gnrl->qnt_philos = ft_atoi(av[1]);
	printf("philos: %d\n", gnrl->qnt_philos);
	gnrl->time_eat = ft_atoi(av[2]);
	printf("eat: %ld\n", gnrl->time_eat);
	gnrl->time_sleep = ft_atoi(av[3]);
	printf("sleep: %ld\n", gnrl->time_sleep);
	gnrl->qnt_forks = ft_atoi(av[1]);
	printf("forks: %d\n", gnrl->qnt_forks);
}
