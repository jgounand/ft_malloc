/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 21:15:30 by jgounand          #+#    #+#             */
/*   Updated: 2018/04/20 21:36:39 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

void ft_free(void *ptr)
{
	t_node	*tmp;

	printf("free %p\n", ptr);
	if (!ptr)
		return ;
	tmp = init_mem()->tiny;
	tmp = tmp->next;
	while (tmp)
	{
		if (tmp->ptr == ptr)
		{
			tmp->previous->next = tmp->next;
			tmp->free = 1;
		}
		tmp = tmp->next;
	}
	tmp = init_mem()->med;
	tmp = tmp->next;
	while (tmp)
	{
		if (tmp->ptr == ptr)
		{
			tmp->previous->next = tmp->next;
			tmp->free = 1;
		}
		tmp = tmp->next;
	}
	tmp = init_mem()->fat;
	tmp = tmp->next;
	while (tmp)
	{
		if (tmp->ptr == ptr)
		{
			munmap(ptr, tmp->size);
			tmp->previous->next = tmp->next;
			tmp->free = 1;
		}
		tmp = tmp->next;
	}
}
