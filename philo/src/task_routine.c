/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:15:37 by tsantana          #+#    #+#             */
/*   Updated: 2024/07/25 19:50:13 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>
#include <stdlib.h>

static int	monitoring_routine()
{

}

int	check_routine(t_general *general)
{
	pthread_create(general->monitors, NULL, monitoring_routine(), )
	while (1)
	{
	}
	return (EXIT_SUCCESS);
}
