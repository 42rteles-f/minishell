/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 20:40:02 by plopes-c          #+#    #+#             */
/*   Updated: 2023/08/16 00:58:50 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**split_sort_by_order(char **split);

int	count_wildcard(char *str)
{
	DIR				*dir;
	struct dirent	*entry;
	int				count;

	dir = opendir(".");
	if (!dir)
		return (0);
	entry = readdir(dir);
	count = 0;
	while (entry)
	{
		if (*entry->d_name != '.')
		{
			if (check_wildcard(str, entry->d_name))
				count++;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (count);
}

char	**ft_join_split(char **split, char **add, int *index)
{
	int		i[3];
	char	**new_split;

	i[0] = -1;
	new_split = ft_calloc(sizeof(char *),
			split_size(split) + split_size(add));
	while (split && split[++i[0]] && i[0] < *index)
		new_split[i[0]] = ft_strdup(split[i[0]]);
	i[1] = 0;
	i[2] = i[0] + 1;
	while (add && add[i[1]])
		new_split[i[0]++] = ft_strdup(add[i[1]++]);
	while (split && split[i[2]])
		new_split[i[0]++] = ft_strdup(split[i[2]++]);
	*index += split_size(add) - 1;
	if (add)
		free_split(add);
	if (split)
		free_split(split);
	return (new_split);
}

char	**build_wildcard_list(char *str, int count)
{
	struct dirent	*entry;
	DIR				*dir;
	char			**list;

	list = ft_calloc(sizeof(char *), count + 1);
	dir = opendir(".");
	if (!dir)
		return (NULL);
	entry = readdir(dir);
	count = 0;
	while (entry)
	{
		if (*entry->d_name != '.')
		{
			if (check_wildcard(str, entry->d_name))
			{
				list[count] = ft_strdup(entry->d_name);
				count++;
			}
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (split_sort_by_order(list));
}

int	ft_split_wildcard_count(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (str[i] && str[i] == '*')
		{
			while (str[i] && str[i] == '*')
				i++;
			count++;
		}
		else if (str[i] && str[i] != '*')
		{
			while (str[i] && str[i] != '*')
				i++;
			count++;
		}
	}
	return (count);
}

char	**split_sort_by_order(char **split)
{
	int		i;
	char	*tmp;

	i = 0;
	while (split && split[i])
	{
		if (split[i + 1] && ft_strcmp(split[i], split[i + 1]) == -1)
		{
			tmp = split[i];
			split[i] = split[i + 1];
			split[i + 1] = tmp;
		}
		i++;
	}
	return (split);
}
