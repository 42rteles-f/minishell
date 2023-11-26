/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 20:30:56 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/22 20:30:56 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	find_pair(char *string, char *jump)
{
	int		i;
	char	stop;

	if (!string || !*string)
		return (0);
	i = 0;
	if (ft_strchr(jump, string[i]))
	{
		stop = string[i++];
		while (string[i] && string[i] != stop)
			i++;
		if (string[i] != stop)
			return (0);
	}
	return (i);
}

int	remove_pair(char *string, char *find)
{
	int	i;
	int	close;
	int	stop;

	i = 0;
	while (string[i])
	{
		close = find_pair(&string[i], find);
		if (close)
		{
			stop = i + close;
			while (i++ < stop)
				string[i - 1] = string[i];
			while (string[++stop])
				string[stop - 2] = string[stop];
			string[stop - 1] = 0;
			string[stop - 2] = 0;
			i -= 2;
		}
		else
			i++;
	}
	return (1);
}
// int	main(int argc, char **argv, char **envp)
// {
// 	char	*input;

// 	(void)argc;
// 	(void)argv;
// 	input = ft_strdup("asdj\"j\"\"\'$asd\'\"\" \"\"\"asd");
// 	// input = ft_strdup("asd \" asd \" a \"\"");
// 	ft_printf("no\n%s\n", input);
// 	input = input_expand(input, envp);
// 	remove_pair(input, "\"\'");
// 	ft_printf("yes\n%s\n", input);
// 	free(input);
// }
