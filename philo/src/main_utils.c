/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:31:24 by tsantana          #+#    #+#             */
/*   Updated: 2024/08/25 19:45:52 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static t_philos	*make_sequence_philos(int numb, t_philos *head, t_general *gnrl)
{
	t_philos	*philo;
	
	philo = malloc(sizeof(t_philos));
	if (!philo)
		return (NULL);
	philo->reference = gnrl;
	philo->philo = 0;
	philo->meal = 0;
	philo->born = usec_definition();
	philo->f_left = (t_mutex){0};
	philo->f_right = NULL;
	pthread_mutex_init(&philo->f_left, NULL);
	philo->id = numb;
	philo->nxt = head;
	philo->prv = NULL;
	head->prv = philo;
	return (philo);
}

static t_philos	*init_philo(t_general *gnrl)
{
	t_philos	*philo;
	
	philo = malloc(sizeof(t_philos));
	if (!philo)
		return (NULL);
	philo->id = 1;
	philo->reference = gnrl;
	philo->philo = 0;
	philo->meal = 0;
	philo->f_right = NULL;
	philo->f_left = (t_mutex){0};
	pthread_mutex_init(&philo->f_left, NULL);
	philo->nxt = NULL;
	philo->prv = NULL;
	return (philo);
}

t_philos	*make_philo_order(int num, t_general **gnrl)
{
	int			i;
	t_philos	*philos;
	t_philos	*head;

	i = 2;
	philos = init_philo(*gnrl);
	head = philos;
	if (num > 1)
	{
		while (i <= num)
		{
			philos->nxt = make_sequence_philos(i, head, *gnrl);
			philos->nxt->prv = philos;
			philos = philos->nxt;
			i++;
		}
	}
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
