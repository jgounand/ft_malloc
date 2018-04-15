/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lststr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 20:39:10 by jgounand          #+#    #+#             */
/*   Updated: 2018/01/09 20:40:51 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lststr(t_list **lst, void *compare, int (*f)())
{
	t_list *tmp;

	if (!lst || !*lst || !compare)
		return (NULL);
	tmp = *lst;
	while (tmp)
	{
		if ((*f)(tmp->content, compare))
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}
