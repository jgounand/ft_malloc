/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsortif.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 10:10:53 by jgounand          #+#    #+#             */
/*   Updated: 2017/12/12 14:36:28 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstsortif(t_list **lst, t_list *new, int (*f)())
{
	t_list	*tmp;
	t_list	*tmp_previous;

	if (!lst && !*lst && !new)
		return ;
	if (!*lst && lst && new)
	{
		*lst = new;
		return ;
	}
	tmp_previous = NULL;
	tmp = *lst;
	while (tmp && (*f)(new->content, tmp->content))
	{
		tmp_previous = tmp;
		tmp = tmp->next;
	}
	if (tmp_previous == NULL || !tmp)
		tmp ? ft_lstadd(lst, new) : ft_lstaddback(lst, new);
	else
	{
		new->next = tmp;
		tmp_previous->next = new;
	}
}
