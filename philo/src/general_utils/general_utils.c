/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:37:28 by tsantana          #+#    #+#             */
/*   Updated: 2024/09/27 19:32:13 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

long	usec_definition(void)
{
	struct timeval	usec;

	gettimeofday(&usec, NULL);
	return (usec.tv_sec * 1000 * 1000 + usec.tv_usec);
}

static int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	result;
	int	i;
	int	sign;

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
	while (ft_isdigit(nptr[i]))
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}

static size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s || s == NULL)
		return ((size_t) 0);
	while (*s)
	{
		i++;
		s++;
	}
	return (i);
}

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = ft_strlen(s);
	write(fd, s, i);
	write(fd, "\n", 1);
}
