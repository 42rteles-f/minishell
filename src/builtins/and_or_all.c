/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:25:26 by rteles-f          #+#    #+#             */
/*   Updated: 2023/09/16 23:46:37 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	find_split_char(char **split, char find)
{
	int	i;
	int	counter;

	if (!split || !*split)
		return (0);
	counter = 0;
	i = 0;
	while (split[i])
	{
		if (ft_strchr(split[i++], find))
			counter++;
	}
	return (counter);
}

void	ignore_parenthesis(char ***tokens)
{
	if (tokens[1] && (find_split_char(*tokens, '(') > 1
			|| !find_split_char(*tokens, ')')))
		ignore_parenthesis(&tokens[1]);
	stop_command(tokens);
}

//((ls) && asd) && ((asd) || ls)
static int	stop_next_command(char ***tokens, char **split)
{
	int	index;

	if (!tokens || !*tokens)
		return (0);
	index = 0;
	while (tokens[index] != split)
		index++;
	while (tokens[index] && *(tokens[index]) && **(tokens[index]))
	{
		if (find_split_char(tokens[index], '('))
		{
			ignore_parenthesis(&tokens[index]);
			return (1);
		}
		else if (*(short *)(tokens[index][0]) == *(short *)"||"
			|| **(tokens[index]) == ';' || **(tokens[index]) == '&')
			return (1);
		else
			stop_command(&tokens[index]);
		index++;
	}
	return (0);
}

void	bonus_execute(t_command *command, int index)
{
	(void)index;
	run_input(command->main);
	ft_lstclear(&command->main->commands, delete_command);
	if ((command->main->status == 0 && command->terminal[index][0] == '|')
		|| (command->main->status != 0 && command->terminal[index][0] == '&'))
	{
		jump_command(command, 0);
		stop_next_command(command->main->tokens, command->terminal);
		command->status = command->main->status;
	}
}
