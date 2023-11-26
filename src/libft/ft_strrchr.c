/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 18:45:37 by plopes-c          #+#    #+#             */
/*   Updated: 2023/07/27 16:40:09 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;

	if (!s || !*s)
		return (NULL);
	i = ft_strlen(s) - 1;
	if ((unsigned char)c == '\0')
		return ((char *)&s[i + 1]);
	while (i >= 0)
	{
		if ((unsigned char)c == (s[i]))
		{
			return ((char *)&s[i]);
		}
		i--;
	}
	return (NULL);
}

/* int	main(void)
{
	 const char	src[] = "abqqqqcdefqqqghijqqqklmnopqarsquvxz";
	char	d;

	d = 't';
	printf("%s\n", ft_strrchr(src, d));
}
 */