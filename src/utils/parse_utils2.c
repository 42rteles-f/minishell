/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 17:58:44 by plopes-c          #+#    #+#             */
/*   Updated: 2023/09/14 21:31:00 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_in_out_parse(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
	{
		if (!ignore_quotes(split[i]))
		{
			if (split[i] && (*split[i] == '>' || *split[i] == '<'
					|| !ft_strcmp(split[i], ">>")
					|| !ft_strcmp(split[i], "<<")))
			{
				if (split[i + 1] && (*split[i + 1] == '>'
						|| *split[i + 1] == '<'))
				{
					write(2, "minishell: syntax error \
near unexpected token `", 47);
					write(2, split[i + 1], ft_strlen(split[i + 1]));
					write(2, "'\n", 2);
					return (0);
				}
			}
		}
		i++;
	}
	return (1);
}

int	check_last_parenteses(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
	{
		if (!ignore_quotes(split[i]))
		{
			if (*split[i] == ')')
			{
				if (split[i + 1] && (*split[i + 1] == '('
						|| !split_case(split[i + 1])))
				{
					write(2, "minishell: syntax error \
near unexpected token `", 47);
					write(2, split[i + 1], ft_strlen(split[i + 1]));
					write(2, "'\n", 2);
					return (0);
				}
			}
		}
		i++;
	}
	return (1);
}
