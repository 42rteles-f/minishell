/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 19:26:47 by plopes-c          #+#    #+#             */
/*   Updated: 2023/06/07 12:27:40 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*go;

	if (!lst || !new)
		return ;
	go = *lst;
	if (!go)
		*lst = new;
	else
	{
		while (go->next)
			go = go->next;
		go->next = new;
		new->previous = go;
	}
}
