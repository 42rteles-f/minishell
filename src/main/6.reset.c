/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6.reset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:34:23 by rteles-f          #+#    #+#             */
/*   Updated: 2023/09/12 19:46:50 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	end_shell(t_control *get)
{
	input_reset(get);
	free_split(get->paths);
	free(get->home);
	safe_free_null(&get->prompt);
	rl_clear_history();
	free_split(get->envp);
	close(get->in_out[0]);
	close(get->in_out[1]);
	exit(get->status);
}

void	input_reset(t_control *get)
{
	ft_lstclear(&get->commands, (void *)delete_command);
	get->tokens = free_triple_pointer(get->tokens);
	safe_free_null(&get->input);
}

void	safe_free_null(char **string)
{
	if (*string)
	{
		free(*string);
		*string = NULL;
	}
}

void	*free_triple_pointer(char ***pointer)
{
	int	i;
	int	j;

	if (pointer)
	{
		i = 0;
		while (pointer[i])
		{
			j = 0;
			while (pointer[i][j])
			{
				free(pointer[i][j++]);
			}
			free(pointer[i++]);
		}
		free(pointer);
	}
	return (NULL);
}
