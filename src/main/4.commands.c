/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4.commands.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:24:58 by rteles-f          #+#    #+#             */
/*   Updated: 2023/09/15 03:31:12 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
Test if the string starts with ./ and is a executable, if not
Try building the command with path and check if is a executable.
*/
static char	*build_executable_path(t_control *get, char *command)
{
	int			index;
	char		*exec_path;

	index = is_executable(command);
	if (index == 1 && (*command == '/'
			|| *(short *)command == *(short *)"./"))
		return (ft_strdup(command));
	else if (index == 2 || index == -1)
		return (ft_strjoin("\xFF", sttc_itoa(index)));
	index = 0;
	while (get->paths[index] && *command)
	{
		exec_path = ft_strjoin(get->paths[index++], command);
		if (is_executable(exec_path) == 1)
			return (exec_path);
		free(exec_path);
	}
	return (NULL);
}

static char	*command_error(t_command *command, char *type, char *input)
{
	char	*error;

	error = ft_strjoin("minishell: ", input);
	if (!type)
	{
		command->status = 127;
		ft_stradd(&error, ": command not found\n");
	}
	else if (ft_atoi(type + 1) == 2)
	{
		command->status = 126;
		ft_stradd(&error, ": Is a directory\n");
	}
	else
		ft_stradd(&error, ": error checking file\n");
	free(type);
	return (error);
}

static void	try_command(t_command *get, int index)
{
	if (get->status)
		return ;
	get->exec_path = build_executable_path(get->main, get->terminal[index]);
	if (!get->exec_path || *get->exec_path == '\xFF')
	{
		get->exec_path = command_error(get, get->exec_path,
				get->terminal[index]);
		get->execute = builtin_execute;
		return ;
	}
	get->flags = copy_shellsplit(&get->terminal[index++]);
	while (get->terminal[index] && !split_case(get->terminal[index]))
		get->terminal[index++][0] = 0;
	if (!get->status)
		get->execute = (void *)execve;
}

static t_exe	solve(char *find)
{
	int				index;
	static char		*cases[20] = {
		"", ">>", ">", "<",
		"<<", "echo", "cd", "pwd",
		"export", "unset", "env", "exit",
		"|", "(", ")", "ignore\xFF",
		"&&", ";", "||", NULL
	};
	static t_exe	functions[20] = {
		do_nothing, output_redirect, output_redirect, input_redirect,
		input_redirect, echo_prepare, cd_prepare, pwd_prepare,
		export_prepare, unset_prepare, env_prepare, exit_prepare,
		do_nothing, do_nothing, do_nothing, jump_command,
		bonus_execute, bonus_execute, bonus_execute, try_command
	};

	index = !!(*find);
	remove_pair(find, "\"\'");
	while (cases[index] && ft_strncmp(find, cases[index], 10))
		index++;
	return (functions[index]);
}

void	structure_commands(t_control *get)
{
	int			i;
	int			j;
	t_command	*command;

	i = -1;
	while (get->tokens && get->tokens[++i])
	{
		command = new_command(get);
		command->terminal = get->tokens[i];
		j = -1;
		while (get->tokens && get->tokens[i][++j] && command->parse)
		{
			get->tokens[i][j] = input_expand(get->tokens[i][j], get->envp, 1);
			(solve(get->tokens[i][j]))(command, j);
		}
		if (command->is_parent == PARENT)
		{
			command->execute(command->exec_path, command->flags,
				command->main->envp, command);
			get->status = command->status;
			delete_command(command);
		}
		else
			ft_lstadd_back(&get->commands, ft_lstnew((void *)command));
	}
}
