/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:43:59 by rteles-f          #+#    #+#             */
/*   Updated: 2023/09/13 17:00:39 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_control	**control(void)
{
	static t_control	*get;

	return (&get);
}

static void	catch_input(t_control *get)
{
	rl_on_new_line();
	get->input = readline(get->prompt);
	if (!get->input)
		control_d(get);
	else
	{
		get->input_count++;
		if (*get->input)
			add_history(get->input);
	}
	rl_on_new_line();
}

static int	tester(t_control *get, char *argv)
{
	get->input = ft_strdup(argv);
	add_history(get->input);
	normalize_input(get);
	structure_commands(get);
	run_input(get);
	input_reset(get);
	end_shell(get);
	return (get->status);
}

int	main(int argc, char **argv, char **envp)
{
	static t_control	get;

	(void)argc;
	(void)argv;
	setup(&get, envp);
	if (argc == 3)
		return (tester(&get, argv[2]));
	while (true)
	{
		catch_input(&get);
		if (normalize_input(&get))
		{
			structure_commands(&get);
			run_input(&get);
		}
		input_reset(&get);
	}
	return (get.status);
}
