/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 04:29:58 by rteles-f          #+#    #+#             */
/*   Updated: 2023/08/18 09:32:11 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	fail_out_pipe(t_command *command, char *string)
{
	command->parse = 0;
	command->status = 1;
	safe_free_null(&command->exec_path);
	command->exec_path = ft_strdup("minishell: ");
	command->exec_path = \
		ft_strjoin("Error opening file: ", string);
	ft_stradd(&command->exec_path, "\n");
	command->execute = builtin_execute;
}

void	output_redirect(t_command *command, int index)
{
	safe_close_fd(command->out_pipe[0], command->out_pipe[1]);
	command->terminal[index + 1] = \
		input_expand(command->terminal[index + 1], command->main->envp, 1);
	remove_pair(command->terminal[index + 1], "\'\"");
	if (*(short *)command->terminal[index] == *(short *)">>")
		command->out_pipe[1] = open(command->terminal[index + 1],
				O_CREAT | O_APPEND | O_WRONLY, 0644);
	else
		command->out_pipe[1] = open(command->terminal[index + 1],
				O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (command->out_pipe[1] < 0)
	{
		fail_out_pipe(command, command->terminal[index + 1]);
		return ;
	}
	command->out_pipe[0] = open("/dev/null", O_RDONLY);
	command->terminal[index + 1][0] = 0;
}
