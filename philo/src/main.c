/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 21:16:01 by tsantana          #+#    #+#             */
/*   Updated: 2024/10/09 17:09:50 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <stdlib.h>

static void	error_input(int ac)
{
	if (ac > 6)
		ft_print_instructions();
	else if (ac < 5)
		ft_print_instructions();
	else
		printf("INVALID CONTENT\n");
}

int	is_number(char numb)
{
	if (!(numb >= '0' && numb <= '9'))
		return (0);
	return (1);
}

static int	valid_args(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (is_number(av[i][j]) == 1)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_monitor	monitor;

	monitor = (t_monitor){0};
	if (!(ac == 5 || ac == 6))
		return (error_input(ac), EXIT_FAILURE);
	else 
	{
		if (valid_args(av))
		{
			correct_input(av, &monitor);
			if (monitor.gnrl->qnt_philos != 1)
			{
				join_threads(&monitor.phl, monitor.gnrl->qnt_philos, &monitor);
				pthread_join(monitor.monitors, NULL);
			}
			destroy_everything(&monitor);
			return (EXIT_SUCCESS);
		}
		else
			return (error_input(ac), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
