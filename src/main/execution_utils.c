/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 09:39:55 by rteles-f          #+#    #+#             */
/*   Updated: 2023/08/18 09:35:33 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	safe_close_fd(int fd, int fd2)
{
	if (!isatty(fd) && fd > 0)
		close(fd);
	if (!isatty(fd2) && fd > 0)
		close(fd2);
}

void	check_dup2(int in, int out)
{
	if (!isatty(in))
	{
		dup2(in, STDIN_FILENO);
	}
	if (!isatty(out))
		dup2(out, STDOUT_FILENO);
}
