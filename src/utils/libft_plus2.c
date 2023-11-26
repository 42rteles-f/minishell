/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_plus2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 18:48:56 by plopes-c          #+#    #+#             */
/*   Updated: 2023/08/10 18:49:21 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_split(char **input)
{
	int	i;

	i = 0;
	ft_printf("\n|::SPLIT:::\n");
	while (input && input[i])
	{
		ft_printf("|%i - %s\n", i + 1, input[i]);
		ft_printf("|\n");
		i++;
	}
}
