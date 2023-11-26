/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:48:50 by plopes-c          #+#    #+#             */
/*   Updated: 2023/09/17 00:26:17 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_exit(char *str, char **flag, char **env, t_command *command);
int		check_exit(t_command *command, char *str);
void	exit_help(t_command *command, int status);

void	exit_prepare(t_command *command, int index)
{
	if (execute_now(command))
		ft_printf("exit\n");
	if (command->terminal[index + 1]
		&& !split_case(command->terminal[index + 1]))
	{
		if (check_exit(command, command->terminal[index + 1]))
			exit_help(command, 2);
		if (command->terminal[index + 2] && (!command->status)
			&& !split_case(command->terminal[index + 2]))
		{
			write(2, "minishell: exit: too many arguments\n", 37);
			command->status = 1;
			return ;
		}
		remove_pair(command->terminal[index + 1], "\'\"");
		command->exec_path = ft_strdup(command->terminal[index + 1]);
		command->terminal[index + 1][0] = 0;
	}
	if (!command->status)
		command->execute = (void *)do_exit;
	if (execute_now(command))
		command->is_parent = PARENT;
}

void	do_exit(char *str, char **flag, char **env, t_command *command)
{
	(void)str;
	(void)flag;
	(void)env;
	if (command->status != 1 && command->status != 2)
		if (command->exec_path)
			command->status = ft_atoi(command->exec_path);
	exit_help(command, 0);
}

int	check_exit(t_command *command, char *str)
{
	if (ft_strcmp(str, sttc_llitoa(ft_atoll(str))))
	{
		write(2, "minishell: exit: ", 17);
		write(2, str,
			ft_strlen(str));
		write(2, ": numeric argument required\n", 29);
		command->status = 2;
		return (1);
	}
	return (0);
}

void	exit_help(t_command *command, int status)
{
	t_control	*get;

	if (status)
		command->status = status;
	get = command->main;
	if (command->status)
		get->status = command->status;
	if (execute_now(command))
	{
		delete_command(command);
		end_shell(get);
	}
}
// 9223372036854775807