/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:34:50 by plopes-c          #+#    #+#             */
/*   Updated: 2023/09/11 10:34:50 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	stop_heredoc(int signal)
{
	(void)signal;
	(*control())->status = 130;
	close(STDIN_FILENO);
	write(1, "\n", 1);
}

void	forced_eof(t_control *get, char *eof, int *in_pipe)
{
	char	*message;

	if (isatty(STDIN_FILENO))
	{
		message = ft_strjoin("Minishell: warning: here-document at line ",
				sttc_itoa(get->input_count));
		ft_stradd(&message, " delimited by end-of-file (wanted `");
		ft_stradd(&message, eof);
		ft_stradd(&message, "')\n");
		write (2, message, ft_strlen(message));
		free(message);
	}
	else
	{
		dup2(get->in_out[0], STDIN_FILENO);
		close(in_pipe[0]);
		close_doc_pipes(get->tokens);
		get->tokens = free_split((char **)get->tokens);
		input_reset(get);
	}
}

int	find_eof(int fd, char *eof, int expand, char **envp)
{
	char	*line;

	while (eof)
	{
		line = readline("> ");
		if (!line)
			return (0);
		if (!ft_strcmp(line, eof))
			eof = NULL;
		else
		{
			if (expand && *line != '~')
				line = input_expand(line, envp, 0);
			ft_stradd(&line, "\n");
			write(fd, line, ft_strlen(line));
		}
		safe_free_null(&line);
	}
	return (1);
}

int	*here_doc(t_control *get, char *eof)
{
	int	expand;
	int	*in_pipe;

	if (!new_pipe(&in_pipe, get))
		return (NULL);
	expand = (!find_pair(ft_strchr(eof, '"'), "\'\"")
			&& !find_pair(ft_strchr(eof, '\''), "\'\""));
	remove_pair(eof, "\'\"");
	signal(SIGINT, stop_heredoc);
	if (!find_eof(in_pipe[1], eof, expand, get->envp))
		forced_eof(get, eof, in_pipe);
	signal(SIGINT, (void *)control_c);
	close(in_pipe[1]);
	if (read(in_pipe[0], 0, 0) < 0)
		safe_free_null((char **)&in_pipe);
	return (in_pipe);
}
