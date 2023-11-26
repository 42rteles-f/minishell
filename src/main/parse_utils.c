/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:04:00 by plopes-c          #+#    #+#             */
/*   Updated: 2023/09/13 17:36:48 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_first_char(char **split)
{
	if (*split && !ignore_quotes(*split))
	{
		if (*split && split[1] && (!ft_strcmp(*split, "|")
				|| !ft_strcmp(*split, ")") || !ft_strcmp(*split, "&&")
				|| !ft_strcmp(*split, ";") || !ft_strcmp(*split, "||")))
		{
			ft_printf("minishell: syntax error near unexpected token `%s'\n",
				*split);
			return (0);
		}
	}
	return (1);
}

int	check_last_char(char **split)
{
	int	last_split;

	last_split = last_split_index(split);
	if (split[last_split] && !ignore_quotes(split[last_split]))
	{
		if (split[last_split]
			&& split_case(split[last_split]) && *split[last_split]
			&& *split[last_split] != ')' && *split[last_split] != ';')
		{
			ft_printf("minishell: syntax error \
near unexpected token `newline'\n");
			return (0);
		}
	}
	return (1);
}

int	last_split_index(char **split)
{
	int	i;

	i = 0;
	while (split && split[i] && split[i + 1])
		i++;
	return (i);
}

int	ft_splitchar(char **split, char c)
{
	int	i;

	if (!split)
		return (0);
	i = 0;
	while (split[i])
	{
		if (!ignore_quotes(split[i]))
		{
			if (ft_strchr(split[i], c))
				return (1);
		}
		i++;
	}
	return (0);
}

int	count_char(char **split, char c)
{
	int	i[2];
	int	count;

	count = 0;
	i[0] = 0;
	while (split && split[i[0]])
	{
		if (!ignore_quotes(split[i[0]]))
		{
			i[1] = 0;
			while (split[i[0]] && split[i[0]][i[1]])
			{
				if (split[i[0]][i[1]] == c)
					count++;
				i[1]++;
			}
		}
		i[0]++;
	}
	return (count);
}
