/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 21:16:01 by tsantana          #+#    #+#             */
/*   Updated: 2024/07/21 20:48:17 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	correct_input(int ac, char **av, t_general *gnrl)
{
	int	i;

	i = 1;
	gnrl->qnt_philos = ft_atoi(av[1]);
	printf("philos: %d\n", gnrl->qnt_philos);
	gnrl->time_eat = ft_atoi(av[2]);
	printf("eat: %ld\n", gnrl->time_eat);
	gnrl->time_sleep = ft_atoi(av[3]);
	printf("sleep: %ld\n", gnrl->time_sleep);
	gnrl->qnt_forks = ft_atoi(av[1]);
	printf("forks: %d\n", gnrl->qnt_forks);
	if (ac == 5)
		gnrl->philos = make_philo_order(av[1]);
	else
		printf("%s\n", av[i]);
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
	if (ac >= 5 && ac <= 6)
	{
		if (valid_args(av))
			return (correct_input(ac, av, &main_strc), 0);
	}
	else
		return (error_input(ac), 1);
	return (0);
}
