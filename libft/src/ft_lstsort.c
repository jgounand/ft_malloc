/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 10:13:29 by jgounand          #+#    #+#             */
/*   Updated: 2017/12/19 12:01:31 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstsort(t_list **lst, int (*f)())
{
	t_list	*tmp;
	void	*content;
	size_t	size;

	tmp = *lst;
	while (tmp->next)
	{
		if ((*f)(tmp->content, tmp->next->content))
		{
			size = tmp->content_size;
			content = tmp->content;
			tmp->content_size = tmp->next->content_size;
			tmp->content = tmp->next->content;
			tmp->next->content_size = size;
			tmp->next->content = content;
			tmp = *lst;
		}
		else
			tmp = tmp->next;
	}
}
