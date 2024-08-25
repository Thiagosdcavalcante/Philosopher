/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:02:30 by tsantana          #+#    #+#             */
/*   Updated: 2024/08/15 18:55:09 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>

/* static void	free_philos(t_philos *phl) */
/* { */
/* 	t_philos	*temp; */
/**/
/* 	phl->prv->nxt = NULL; */
/* 	phl->prv = NULL; */
/* 	while (phl) */
/* 	{ */
/* 		temp = phl; */
/* 		phl = phl->nxt; */
/* 		pthread_mutex_destroy(&temp->f_left); */
/* 		free(temp); */
/* 	} */
/* } */
/**/
/* void	final_free(t_general *gnrl) */
/* { */
/* 	pthread_mutex_destroy(&gnrl->write); */
/* 	if (gnrl->philos) */
/* 		free_philos(gnrl->philos); */
/* 	pthread_mutex_destroy(&gnrl->write); */
/* } */
