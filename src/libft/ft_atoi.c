/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:23:43 by plopes-c          #+#    #+#             */
/*   Updated: 2023/09/17 00:10:55 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		i;
	int		sign;
	long	number;

	i = 0;
	while ((8 < nptr[i] && nptr[i] < 14) || nptr[i] == 32)
		i++;
	sign = (nptr[i] != '-') - (nptr[i] == '-');
	i += (nptr[i] == '-' || nptr[i] == '+');
	number = 0;
	while (47 < nptr[i] && nptr[i] < 58)
		number = (nptr[i++] - 48) + (number * 10);
	return ((int)(number * sign));
}

/*
 int	main(void)
 {
	const char str[] = "1234";

	printf("%d\n", ft_atoi(str));
	return (0);
 }
*/