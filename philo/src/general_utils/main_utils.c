/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:31:24 by tsantana          #+#    #+#             */
/*   Updated: 2024/09/29 17:33:00 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

long	ft_atol(const char *nptr)
{
	long int	result;
	int			i;
	int			sign;

	result = 0;
	i = 0;
	sign = 1;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (is_number(nptr[i]))
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return ((long)result * sign);
}

static t_philos	*init_philo(t_general *gnrl, int id, t_philos *prev)
{
	t_philos	*philo;
	
	philo = malloc(sizeof(t_philos));
	if (!philo)
		return (NULL);
	philo->id = id;
	philo->is_dead = 0;
	philo->qnt_meal = gnrl->max_meals;
	philo->reference = gnrl;
	philo->philo = 0;
	philo->f_right = (t_mutex){0};
	philo->last_meal = 0;
	philo->nxt = NULL;
	philo->prv = prev;
	pthread_mutex_init(&philo->f_left, NULL);
	pthread_mutex_init(&philo->death, NULL);
	return (philo);
}

t_philos	*make_philo_order(int num, t_general *gnrl)
{
	int			i;
	t_philos	*philos;
	t_philos	*head;

	philos = init_philo(gnrl, 1, NULL);
	head = philos;
	i = 2;
	printf("%d\n", philos->id);
	while (i <= num)
	{
		philos->nxt = init_philo(gnrl, i, philos);
		philos->f_right = philos->nxt->f_left;
		philos = philos->nxt;
		printf("%d\n", philos->id);
		i++;
	}
	if (philos->nxt == NULL)
	{
		philos->nxt = head;
		philos->f_right = philos->nxt->f_left;
		head->prv = philos;
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
