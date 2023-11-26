/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 19:16:41 by plopes-c          #+#    #+#             */
/*   Updated: 2023/08/18 12:09:56 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_end_of_command(char *token)
{
	if (!token || !*token)
		return (0);
	if ((*token == '&' && *(token + 1) == '&')
		|| *token == '|' || *token == ';')
		return (1);
	return (0);
}

int	count_cases(char **string)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (!string)
		return (0);
	while (string[i])
	{
		if (is_end_of_command(string[i]))
			count++;
		i++;
	}
	return (count);
}
