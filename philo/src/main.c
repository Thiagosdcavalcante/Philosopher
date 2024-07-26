/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 21:16:01 by tsantana          #+#    #+#             */
/*   Updated: 2024/07/26 16:07:13 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static long	usec_definition(void)
{
	struct timeval	usec;

	gettimeofday(&usec, NULL);
	return (usec.tv_sec * 1000 * 1000 + usec.tv_usec);
}

static void	error_input(int ac)
{
	if (ac > 6)
		ft_print_instructions();
	else if (ac < 5)
		ft_print_instructions();
	else
		printf("INVALID CONTENT");
}

static int	is_number(char numb)
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
	t_general	main_strc;

	main_strc = (t_general){0};
	main_strc.usec = usec_definition();
	printf("%lu\n", main_strc.usec);
	if (ac == 5 || ac == 6)
	{
		if (valid_args(av))
		{
			correct_input(ac, av, &main_strc);
			return (final_free(&main_strc), EXIT_SUCCESS);
		}
	}
	else
	{
		error_input(ac);
		return (final_free(&main_strc), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
