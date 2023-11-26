/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:13:06 by rteles-f          #+#    #+#             */
/*   Updated: 2023/09/13 16:46:35 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	execute_now(t_command *get)
{
	int	index;

	index = 0;
	while (get->main->tokens[index] != get->terminal)
		index++;
	if (get->main->tokens[index + 1]
		&& !ft_strncmp(get->main->tokens[index + 1][0], "|", 2))
		return (0);
	else if (get->main->tokens[index]
		&& !ft_strncmp(get->main->tokens[index][0], "|", 2))
		return (0);
	return (1);
}

void	builtin_execute(char *print, char **fd, char **len, t_command *command)
{
	if (!print)
		return ;
	*(long *)&fd = !!command->status + 1;
	*(long *)&len = (long)ft_strlen(print);
	write(*(long *)&fd, print, *(long *)&len);
}

void	do_nothing(void)
{
	return ;
}

// char	**insert_input(char **tokens, char *new)
// {
// 	int		counter;
// 	char	**resized;

// 	counter = 0;
// 	while (tokens[counter])
// 		counter++;
// 	resized = ft_calloc(sizeof(char *), counter + 2);
// 	counter = 0;
// 	while (tokens[counter])
// 	{
// 		resized[counter] = tokens[counter];
// 		counter++;
// 	}
// 	resized[counter] = new;
// 	free(tokens);
// 	return (resized);
// }

// void	extra_input(t_command *command, int index)
// {
// 	int		find;
// 	char	*add;

// 	find = 0;
// 	while (command->main->tokens[find]
// 			&& command->main->tokens[find] != command->terminal)
// 		find++;
// 	if (command->terminal[index + 1] || command->main->tokens[find + 1])
// 		return ;
// 	add = catch_one(command->main);
// 	if (!add)
// 	{
// 		command->main->tokens = free_triple_pointer(command->main->tokens);
// 		jump_command(command, 0);
// 	}
// 	else
// 		command->main->tokens[find] =
// 			insert_input(command->main->tokens[find], add);
// }
// void	printf_input(t_control *get)
// {
// 	ft_printf("\nInput-->\n");
// 	for (int i = 0; get->tokens[i]; i++)
// 	{
// 		ft_printf("command %i->\n", i);
// 		for (int j = 0; get->tokens[i][j]; j++)
// 			ft_printf("%s\n", get->tokens[i][j]);
// 	}
// 	ft_printf("end.\n");
// }
