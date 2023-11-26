/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 22:20:10 by plopes-c          #+#    #+#             */
/*   Updated: 2023/08/16 16:15:35 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	count_wildcards(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] == '*')
		i++;
	return (i);
}

int	count_wildcard_chars(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != '*')
		i++;
	return (i);
}
