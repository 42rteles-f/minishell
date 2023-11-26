/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:31:03 by plopes-c          #+#    #+#             */
/*   Updated: 2023/09/14 20:49:30 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_execute(char *current, char **directory, char **envp, t_command *get)
{
	if (!directory || !*directory)
		return ;
	if (chdir(*directory))
	{
		write (2, "minishell: cd: ", 15);
		write (2, *directory, ft_strlen(*directory));
		write(2, ": Not a directory\n", 19);
		get->main->status = 1;
		return ;
	}
	free(get->main->prompt);
	get->main->prompt = get_prompt();
	get->main->status = 0;
	current = getcwd(NULL, 0);
	envp = get_envaddress(envp, "PWD");
	if (envp && *envp)
		change_env_variable("OLDPWD", &(*envp)[4]);
	change_env_variable("PWD", current);
	free(current);
}

void	cd_prepare(t_command *command, int index)
{
	int	args;

	args = 0;
	while (command->terminal[index + args]
		&& !split_case(command->terminal[index + args]))
		args++;
	if (args == 1)
		if (command->main->home)
			command->flags = ft_split(command->main->home, ' ');
	if (args > 2)
	{
		command->exec_path = ft_strdup("minishell: cd: too many arguments\n");
		command->execute = builtin_execute;
		command->status = 1;
		return ;
	}
	if (args == 2)
	{
		command->flags = copy_shellsplit(&command->terminal[index + 1]);
		command->terminal[index + 1][0] = 0;
	}
	if (!command->status)
		command->execute = (void *)cd_execute;
	if (execute_now(command))
		command->is_parent = PARENT;
}
