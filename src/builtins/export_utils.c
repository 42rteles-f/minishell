/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 18:47:00 by plopes-c          #+#    #+#             */
/*   Updated: 2023/08/16 17:52:59 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**find_var(char *name, char **env, int *index, int *size)
{
	int	i;
	int	name_len[2];

	i = 0;
	name_len[0] = ft_strlen(name);
	if (size)
		*size = split_size(env);
	i = 0;
	while (env && env[i])
	{
		name_len[1] = ft_strlenchr(env[i], '=');
		if ((!ft_strncmp(name, env[i], name_len[1]))
			&& (name_len[0] == name_len[1]))
		{
			if (index)
				*index = i;
			return (&env[i]);
		}
		i++;
	}
	if (index)
		*index = -1;
	return (NULL);
}

char	**env_copy(char **env, char *new_str)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env && env[i])
		i++;
	new_env = ft_calloc(sizeof(char *), i + 2);
	i = 0;
	while (env && env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = ft_strdup(new_str);
	free_split(env);
	return (new_env);
}
