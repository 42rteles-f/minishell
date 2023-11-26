/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 04:27:44 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/10 04:27:44 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	fail_in_pipe(t_command *command, char *string)
{
	if (!pipe(command->in_pipe))
		close(command->in_pipe[1]);
	command->parse = 0;
	command->status = 1;
	safe_free_null(&command->exec_path);
	command->exec_path = ft_strdup("minishell: ");
	ft_stradd(&command->exec_path, string);
	ft_stradd(&command->exec_path, ": No such file or directory\n");
	command->execute = builtin_execute;
}

void	input_redirect(t_command *command, int index)
{
	safe_close_fd(command->in_pipe[0], command->in_pipe[1]);
	if (*(short *)command->terminal[index] == *(short *)"<<")
		*(long *)command->in_pipe = *(long *)command->terminal[index + 1];
	else
	{
		command->terminal[index + 1] = \
			input_expand(command->terminal[index + 1], command->main->envp, 1);
		remove_pair(command->terminal[index + 1], "\'\"");
		command->in_pipe[0]
			= open(command->terminal[index + 1], O_RDONLY | 0644);
	}
	if (command->in_pipe[0] < 0)
	{
		fail_in_pipe(command, command->terminal[index + 1]);
		return ;
	}
	if (command->terminal)
		*command->terminal[index + 1] = 0;
}
// int	here_doc(t_command *command, char *eof)
// {
// 	int	expand;

// 	if (pipe(command->in_pipe) < 0)
// 		return (-1);
// 	command->main->status = 0;
// 	expand = !!find_pair(eof, "\'\"");
// 	remove_pair(eof, "\'\"");
// 	signal(SIGINT, stop_heredoc);
// 	if (!find_eof(eof, expand, command))
// 	{
// 		if (isatty(STDIN_FILENO))
// 			warning_control_d(eof, command->main->input_count);
// 		else
// 		{
// 			jump_command(command, 0);
// 			dup2(command->main->in_out[0], STDIN_FILENO);
// 		}
// 		command->terminal = 0;
// 	}
// 	signal(SIGINT, control_c);
// 	close(command->in_pipe[1]);
// 	return (command->in_pipe[0]);
// }

// char	*catch_one(t_control *get)
// {
// 	char	*line;

// 	line = "start";
// 	signal(SIGINT, stop_heredoc);
// 	while (line)
// 	{
// 		line = readline("> ");
// 		if (!line)
// 		{
// 			if (isatty(STDIN_FILENO))
// 				end_shell(get);
// 			else
// 			{
// 				dup2(get->in_out[0], STDIN_FILENO);
// 				break ;
// 			}
// 		}
// 		else if (!*line)
// 			safe_free_null(&line);
// 		else
// 			break;
// 	}
// 	signal(SIGINT, control_c);
// 	return (line);
// }