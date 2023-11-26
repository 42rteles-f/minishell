/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:59:05 by plopes-c          #+#    #+#             */
/*   Updated: 2023/09/14 20:09:19 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_str(char **split);

void	env_prepare(t_command *command, int index)
{
	if (!command->terminal[index + 1]
		|| split_case(command->terminal[index + 1]))
		command->exec_path = env_str(command->main->envp);
	if (!command->status)
		command->execute = builtin_execute;
}

char	*env_str(char **split)
{
	int		i[3];
	int		count;
	char	*str;

	i[0] = -1;
	count = 0;
	while (split && split[++i[0]])
		count += ft_strlen(split[i[0]]) + 1;
	str = ft_calloc(sizeof(char), count + 1);
	bzero(i, 12);
	while (split && split[i[1]])
	{
		if (ft_strchr(split[i[1]], '='))
		{
			i[2] = 0;
			while (split[i[1]][i[2]])
			{
				str[i[0]++] = split[i[1]][i[2]];
				i[2]++;
			}
			str[i[0]++] = '\n';
		}
		i[1]++;
	}
	return (str);
}
