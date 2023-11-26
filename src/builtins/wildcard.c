/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:33:16 by plopes-c          #+#    #+#             */
/*   Updated: 2023/08/18 12:27:21 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**wildcard(char *str)
{
	int				count;

	count = count_wildcard(str);
	if (!count)
		return (ft_split(str, ' '));
	return (build_wildcard_list(str, count));
}

char	**wildcard_aux(char **split)
{
	int		i;
	char	**wildcard_split;

	wildcard_split = NULL;
	i = 0;
	while (split && split[i])
	{
		if (!ignore_quotes(split[i]))
		{
			if (ft_strchr(split[i], '*'))
			{
				wildcard_split = wildcard(split[i]);
				split = ft_join_split(split, wildcard_split, &i);
			}
		}
		i++;
	}
	return (split);
}

char	**ft_split_wildcard(char *str)
{
	int		i;
	int		j;
	char	**split;
	int		len;

	split = ft_calloc(sizeof(char *), ft_split_wildcard_count(str) + 1);
	i = 0;
	j = 0;
	while (str && str[i])
	{
		if (str[i] == '*')
		{
			len = count_wildcards(&str[i]);
			split[j] = ft_substr(str, i, len);
		}
		else
		{
			len = count_wildcard_chars(&str[i]);
			split[j] = ft_substr(str, i, len);
		}
		i += len;
		j++;
	}
	return (split);
}

// int	check_wildcard(char *wildcard, char *folder)
// {
// 	int		i;
// 	char	**split;

// 	i = 0;
// 	split = ft_split_wildcard(wildcard);
// 	while (split && split[i])
// 	{
// 		if (ft_strchr(split[i], '*'))
// 			i++;
// 		else
// 		{
// 			if (i == 0)
// 				folder = ft_strnstr(folder, split[i], ft_strlen(split[i]));
// 			else
// 				folder = ft_strnstr(folder, split[i], ft_strlen(folder));
// 			if (!folder)
// 			{
// 				free_split(split);
// 				return (0);
// 			}
// 			i++;
// 		}
// 	}
// 	free_split(split);
// 	return (1);
// }

static int	check_wildcard_aux(int i, char **matrix, char **name, int flag)
{
	while (flag && matrix && matrix[i])
	{
		*name = ft_strnstr(*name, matrix[i], ft_strlen(*name));
		if (!*name)
			flag = 0;
		else
			*name += ft_strlen(matrix[i]);
		i++;
	}
	return (flag);
}

int	check_wildcard(char *str, char *name)
{
	int		i[4];
	char	**matrix;

	matrix = ft_split(str, '*');
	i[2] = split_size(matrix);
	i[0] = 0;
	i[3] = 1;
	if (i[3] && str && str[0] != '*')
	{
		i[0] = 1;
		i[1] = ft_strlen(matrix[0]);
		if (ft_strncmp(name, matrix[0], i[1]))
			i[3] = 0;
		else
			name += i[1];
	}
	if (i[3] && str && str[ft_strlen(str) - 1] != '*')
	{
		i[1] = ft_strlen(matrix[i[2] - 1]);
		if (ft_strncmp(matrix[i[2] - 1], &name[ft_strlen(name) - i[1]], i[1]))
			i[3] = 0;
	}
	i[3] = check_wildcard_aux(i[0], matrix, &name, i[3]);
	free_split(matrix);
	return (i[3]);
}
