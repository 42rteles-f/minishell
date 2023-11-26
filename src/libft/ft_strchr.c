/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:05:53 by plopes-c          #+#    #+#             */
/*   Updated: 2023/06/30 15:07:31 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if ((char)c == (s[i]))
			return (&((char *)s)[i]);
		i++;
	}
	if ((char)c == (s[i]))
		return (&((char *)s)[i]);
	return (NULL);
}
/*
int	main(void)
{
	char	src[] = "abcdefghijklmnopqrstuvxz";
	char	d;

	d = '0';
	printf("%s\n", ft_strchr(src, d));
}
*/