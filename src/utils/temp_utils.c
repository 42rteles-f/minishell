/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:32:54 by plopes-c          #+#    #+#             */
/*   Updated: 2023/09/16 18:46:26 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_size(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
		i++;
	return (i);
}

char	**env_var(char *var, char **env)
{
	int		i;

	i = 0;
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], var, ft_strlenchr(env[i], '=')))
			return (&(env[i]));
		i++;
	}
	return (NULL);
}

void	change_env_variable(char *variable, char *value)
{
	char	**tmp;
	char	*join;

	tmp = env_var(variable, (*control())->envp);
	join = ft_strjoin(variable, "=");
	if (tmp)
	{
		free(*tmp);
		*tmp = ft_strjoin(join, value);
	}
	else
		(*control())->envp = env_copy((*control())->envp,
				ft_stradd(&join, value));
	free(join);
}

int	can(char *str)
{
	int	i;

	i = 0;
	if (str && (ft_isdigit(str[0]) || str[0] == '='))
		return (0);
	while (str && str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	stderror_export(t_command *command, char *str)
{
	safe_free_null(&command->exec_path);
	command->exec_path = ft_strjoin("Minishell: export: `", str);
	ft_stradd(&command->exec_path, "': not a valid identifier\n");
	builtin_execute(command->exec_path, NULL, NULL, command);
	command->status = 1;
	return (0);
}
