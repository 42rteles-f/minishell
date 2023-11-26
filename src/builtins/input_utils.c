/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 19:13:57 by rteles-f          #+#    #+#             */
/*   Updated: 2023/08/14 19:14:39 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	close_doc_pipes(char ***tokens)
{
	int	index;

	index = 0;
	while (tokens && *tokens && (*tokens)[index])
	{
		if (*(short *)(*tokens)[index] == *(short *)"<<")
		{
			if (!isatty(((int *)(*tokens)[index + 1])[0]))
				close(((int *)(*tokens)[index + 1])[0]);
			if (!isatty(((int *)(*tokens)[index + 1])[1]))
				close(((int *)(*tokens)[index + 1])[1]);
		}
		index++;
	}
	if (tokens && *(tokens + 1))
		close_doc_pipes(tokens + 1);
}

int	new_pipe(int **newpipe, t_control *get)
{
	*newpipe = ft_calloc(sizeof(int), 2);
	if (pipe(*newpipe) < 0)
	{
		free(*newpipe);
		write (2, "minishell: error in pipe usage\n", 32);
		input_reset(get);
		return (0);
	}
	return (1);
}
