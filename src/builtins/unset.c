/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:02:01 by plopes-c          #+#    #+#             */
/*   Updated: 2023/09/16 18:46:26 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_execute(char *str, char **flags, char **env)
{
	char		**var;
	int			index;
	int			size;
	int			i;

	(void)str;
	i = 0;
	while (flags && flags[i])
	{
		var = find_var(flags[i], (*control())->envp, &index, &size);
		if (var)
		{
			free(*var);
			ft_memmove(&((*control())->envp[index]),
				&((*control())->envp[index + 1]),
				sizeof(char *) * (size - index));
		}
		i++;
	}
	update_paths(env, (*control()));
}

void	unset_prepare(t_command *command, int index)
{
	int	i;
	int	len;

	if (command->terminal[1])
	{
		len = split_size(command->terminal);
		command->flags = ft_calloc(sizeof(char *), len);
		i = 0;
		while (command->terminal[++index]
			&& !split_case(command->terminal[index]))
		{
			remove_pair(command->terminal[index], "\'\"");
			command->flags[i++] = ft_strdup(command->terminal[index]);
			command->terminal[index][0] = 0;
		}
	}
	if (!command->status)
		command->execute = unset_execute;
	if (execute_now(command))
		command->is_parent = PARENT;
}

// #### IF ERROR FOUND IN UNSET: INVALID IDENTIFIER #############
// 				   write this on line 53
// if (!can(command->terminal[index]))
			// 	stderror_aux(command, command->terminal[index], 0);
			// else