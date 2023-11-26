/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:53:00 by plopes-c          #+#    #+#             */
/*   Updated: 2023/08/02 15:54:31 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while ((((unsigned char *)s1)[i] || ((unsigned char *)s2)[i]))
	{
		if ((((unsigned char *)s1)[i]) > (((unsigned char *)s2)[i]))
			return (1);
		if ((((unsigned char *)s1)[i]) < (((unsigned char *)s2)[i]))
			return (-1);
		i++;
	}
	return (0);
}
