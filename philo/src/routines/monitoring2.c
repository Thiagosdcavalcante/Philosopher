/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:00:54 by tsantana          #+#    #+#             */
/*   Updated: 2024/10/10 19:45:33 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

void	print_dead(t_monitor *mntr, int id)
{
	long	time;

	time = my_print_sup(mntr->gnrl);
	pthread_mutex_lock(&mntr->gnrl->write);
	printf("%ld %d " RED "died\n" RESET, time, id);
	pthread_mutex_unlock(&mntr->gnrl->write);
}

