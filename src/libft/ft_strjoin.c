/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:37:39 by plopes-c          #+#    #+#             */
/*   Updated: 2023/07/25 10:00:07 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		n;

	if (!s1 && !s2)
		return (NULL);
	str = malloc((ft_strlen(s1)) + (ft_strlen(s2)) + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	n = 0;
	while (s2 && s2[n])
		str[i++] = s2[n++];
	str[i] = '\0';
	return (str);
}
