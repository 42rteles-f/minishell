/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:51:06 by plopes-c          #+#    #+#             */
/*   Updated: 2023/09/17 00:25:38 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

long long	ft_atoll(char *nptr)
{
	int			i;
	int			sign;
	long long	number;

	i = 0;
	while ((8 < nptr[i] && nptr[i] < 14) || nptr[i] == 32)
		i++;
	sign = (nptr[i] != '-') - (nptr[i] == '-');
	i += (nptr[i] == '-' || nptr[i] == '+');
	number = 0;
	while (47 < nptr[i] && nptr[i] < 58)
		number = (nptr[i++] - 48) + (number * 10);
	return ((number * sign));
}

char	*sttc_llitoa(long long number)
{
	static char	to_ascii[22];
	int			index;
	int			sign;

	sign = (number > 0) - (number < 0);
	index = 21;
	while (number || index == 21)
	{
		to_ascii[--index] = (number % 10) * sign + '0';
		number = number / 10;
	}
	if (sign < 0)
		to_ascii[--index] = '-';
	return (&to_ascii[index]);
}
