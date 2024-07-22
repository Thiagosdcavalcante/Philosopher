/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:31:24 by tsantana          #+#    #+#             */
/*   Updated: 2024/07/21 17:38:55 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <stdio.h>

static void	print_philo(t_philos *phl)
{
	int	stop;

	stop = phl->philo;
	printf(GRN "PHILO: %d -\n" RESET, phl->philo);
	phl = phl->nxt;
	while (phl->philo != stop)
	{
		printf(GRN "PHILO: %d -\n" RESET, phl->philo);
		phl = phl->nxt;
	}
}

static t_philos	*make_sequence_philos(int numb, t_philos *head)
{
	t_philos	*philo;
	
	philo = malloc(sizeof(t_philos));
	if (!philo)
		return (NULL);
	philo->philo = numb;
	philo->nxt = head;
	philo->prv = NULL;
	head->prv = philo;
	return (philo);
}

static t_philos	*init_philo(void)
{
	t_philos	*philo;
	
	philo = malloc(sizeof(t_philos));
	if (!philo)
		return (NULL);
	philo->philo = 1;
	philo->nxt = NULL;
	philo->prv = NULL;
	return (philo);
}

t_philos	*make_philo_order(char *num)
{
	int			i;
	int			numb;
	t_philos	*philos;
	t_philos	*head;

	numb = ft_atoi(num);
	i = 2;
	philos = init_philo();
	head = philos;
	if (numb > 1)
	{
		while (i <= numb)
		{
			philos->nxt = make_sequence_philos(i, head);
			philos->nxt->prv = philos;
			philos = philos->nxt;
			i++;
		}
	}
	print_philo(head);
	return (head);
}

void	ft_print_instructions(void)
{
	printf(RED "INPUT ERROR:\n- FIRST: PHILO'S\n" RESET);
	printf(RED "- SECOND: TIME TO DIE\n" RESET);
	printf(RED "- THIRD: TIME TO EAT\n- FOURTH: TIME TO SLEEP\n" RESET);
	printf(RED "- FIFTH: TIME EACH PHILO HAS TO EAT\n" RESET);
	printf(RED "./philo FIRST SECOND THIRD FOURTH" RESET);
	printf(RED " FIFTH(CAN BE EMPTY)\n" RESET);
	printf(MAG " ONLY POSITIVE NUMBERS\n" RESET);
}
