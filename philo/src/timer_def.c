/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer_def.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 19:26:12 by tsantana          #+#    #+#             */
/*   Updated: 2024/08/23 21:59:47 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	usec_definition(void)
{
	struct timeval	usec;

	gettimeofday(&usec, NULL);
	return ((usec.tv_sec * 1000) + (1000 / usec.tv_usec));
}

