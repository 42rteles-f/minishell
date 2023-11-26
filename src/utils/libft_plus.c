/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_plus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:44:31 by rteles-f          #+#    #+#             */
/*   Updated: 2023/09/17 00:25:14 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_space(char c)
{
	if ((8 < c && c < 14) || c == 32)
		return (1);
	return (0);
}

char	*ft_stradd(char **original, char *add)
{
	int		i;
	int		j;
	char	*joined;

	if (!original || !(*original) || !add)
		return (NULL);
	joined = ft_calloc(sizeof(char),
			(ft_strlen((*original)) + ft_strlen(add) + 1));
	if (!joined)
		return (NULL);
	i = -1;
	while ((*original)[++i])
		joined[i] = (*original)[i];
	j = -1;
	while (add[++j])
		joined[i + j] = add[j];
	free((*original));
	*original = joined;
	return (joined);
}

char	*ft_unsplit(char **split, int posize, char c, int flag_nl)
{
	char	*line;
	int		i;

	if (!split || (!*split && !posize))
		return (NULL);
	if (*split)
		line = ft_unsplit((split + 1), posize + ft_strlen(*split) + 1, c, 1);
	else
	{
		line = ft_calloc(sizeof(char), posize + 1);
		if (flag_nl)
			line[posize - 1] = '\n';
		return (line);
	}
	i = 0;
	while ((*split)[i])
		line[posize++] = (*split)[i++];
	if (*(split + 1))
		line[posize] = c;
	return (line);
}

char	*sttc_itoa(int number)
{
	static char	to_ascii[12];
	int			index;
	int			sign;

	sign = (number > 0) - (number < 0);
	index = 11;
	while (number || index == 11)
	{
		to_ascii[--index] = (number % 10) * sign + '0';
		number = number / 10;
	}
	if (sign < 0)
		to_ascii[--index] = '-';
	return (&to_ascii[index]);
}

void	finish_list_with(char **list, char *put)
{
	char	*temp;

	while (*list)
	{
		temp = ft_strjoin(*list, put);
		free(*list);
		*list = temp;
		list++;
	}
}
