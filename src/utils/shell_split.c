/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 20:09:16 by rteles-f          #+#    #+#             */
/*   Updated: 2023/07/26 11:56:52 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	getwords(char *s);
static int	fill_list(char *s, char **list);
static char	*checkmalloc(int size, int members, char **list);

char	**shell_split(char *s)
{
	int		foundwords;
	int		check;
	char	**list;

	if (!s)
		return (NULL);
	foundwords = getwords(s);
	list = ft_calloc(sizeof(char *), (foundwords + 1));
	if (!list)
		return (NULL);
	check = fill_list(s, list);
	if (!check)
		return (NULL);
	return (list);
}

static int	getwords(char *s)
{
	int		i;
	int		count;
	int		size;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && is_space(s[i]))
			i++;
		size = split_case(&s[i]);
		count += (s[i] && (!is_space(s[i])));
		i += size + ignore_quotes(&s[i]);
		while (s[i] && !is_space(s[i]) && !split_case(&s[i]) && !size)
			i++;
	}
	return (count);
}

static int	fill_list(char *s, char **list)
{
	int		i;
	int		j;
	int		word;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] && is_space(s[i]))
			i++;
		word = split_case(&s[i]);
		while (s[i + word] && !is_space(s[i + word]) && !split_case(&s[i])
			&& !split_case(&s[i + word]))
			word += 1 + ignore_quotes(&s[i + word]);
		if (word > 0)
		{
			list[j] = checkmalloc((word + 1), j, list);
			if (!list[j])
				return (0);
			ft_memcpy(list[j++], &(s)[i], word);
			i += word;
		}
	}
	return (1);
}

static char	*checkmalloc(int size, int members, char **list)
{
	int		i;
	char	*string;

	string = ft_calloc(sizeof(char), size);
	if (!string)
	{
		i = -1;
		while (i < members)
		{
			free(list[members - 1]);
			members--;
		}
		free(list);
		return (NULL);
	}
	return (string);
}
