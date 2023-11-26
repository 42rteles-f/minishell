/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:14:57 by rteles-f          #+#    #+#             */
/*   Updated: 2023/08/18 18:28:57 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	split_case(char *line)
{
	if (!*line)
		return (0);
	else if (*line == '<' && *(line + 1) == '<')
		return (2);
	else if (*line == '>' && *(line + 1) == '>')
		return (2);
	else if (*line == '|' && *(line + 1) == '|')
		return (2);
	else if (*line == '&' && *(line + 1) == '&')
		return (2);
	else if (*line == '>' || *line == '<' || *line == ';' || *line == '|'
		|| *line == '(' || *line == ')')
		return (1);
	return (0);
}

void	*free_split(char **split)
{
	int	i;

	if (split)
	{
		i = 0;
		while (split[i])
			free(split[i++]);
		free(split);
		split = 0;
	}
	return (NULL);
}

char	**copy_shellsplit(char **split)
{
	char	**new;
	int		counter;
	int		found;

	counter = 0;
	while (split[counter])
		counter++;
	new = ft_calloc(sizeof(char *), counter + 1);
	counter = 0;
	found = 0;
	while (split[counter])
	{
		if (!split_case(split[counter]))
		{
			new[found] = ft_strdup(split[counter]);
			new[found] = input_expand(new[found], (*control())->envp, 1);
			remove_pair(new[found], "\"\'");
			found++;
			*split[counter] = 0;
		}
		counter += (*split[counter] == '>' || *split[counter] == '<');
		counter++;
	}
	return (new);
}

int	ignore_quotes(char *string)
{
	int		i;
	char	stop;

	i = 0;
	if (string[i] == '\"' || string[i] == '\'')
	{
		stop = string[i++];
		while (string[i] && string[i] != stop)
			i++;
		if (string[i] != stop)
			return (0);
	}
	return (i);
}
