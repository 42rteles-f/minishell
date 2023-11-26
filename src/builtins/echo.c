/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:58:19 by plopes-c          #+#    #+#             */
/*   Updated: 2023/09/16 23:01:57 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_flag(char *string)
{
	int	i;

	if (!string || *string != '-')
		return (0);
	i = 1;
	while (string[i] && string[i] == 'n')
		i++;
	if (string[i])
		return (0);
	return (1);
}

static void	echo_execute(char *a, char **print)
{
	int	i;

	(void)a;
	i = 0;
	while (check_flag(print[i]))
		i++;
	while (print[i])
	{
		ft_printf("%s", print[i]);
		if (print[i + 1])
			ft_printf(" ");
		i++;
	}
	if (!check_flag(*print))
		ft_printf("\n");
	(*control())->status = 0;
}

void	echo_prepare(t_command *command, int index)
{
	command->flags = copy_shellsplit(&command->terminal[index + 1]);
	while (command->terminal[index] && !split_case(command->terminal[index]))
		*command->terminal[index++] = 0;
	if (!command->status)
		command->execute = echo_execute;
}
