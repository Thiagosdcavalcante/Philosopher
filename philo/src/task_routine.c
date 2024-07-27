/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:15:37 by tsantana          #+#    #+#             */
/*   Updated: 2024/07/27 19:13:03 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	print_status(t_philos *phl)
{
	if (phl->status == EATING)
		printf(RED " IS EATING!" RESET);
	else if (phl->status == SLEEPING)
		printf(MAG " IS SLEEPING!" RESET);
	else if (phl->status == THINKING)
		printf(GRN " IS THINKING!" RESET);
	else if (phl->status == DEAD)
		printf(RED " IS DEAD!" RESET);
	else if (phl->status == HAS_FORK)
		printf(GRN " PHILOSOPHER TOOK A NEW FORK!" RESET);
}

void	*monitor_routine(void *gnrl)
{
	int	stop;
	t_general	*general;

	general = (t_general *) gnrl;
	while (general->has_dead == 0)
	{
		stop = general->philos->id;
		if (general->philos->dead == 1)
			break ;
		general->philos = general->philos->nxt;
		while (general->philos->id != stop)
		{
			if (general->philos->status == 1)
			{
				print_status(general->philos);
				general->philos->status = 0;
			}
			if (general->philos->dead == 1)
				break ;
			general->philos = general->philos->nxt;
		}
	}
	return (0);
}
