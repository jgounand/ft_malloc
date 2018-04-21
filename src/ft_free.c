/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 21:15:30 by jgounand          #+#    #+#             */
/*   Updated: 2018/04/21 14:45:56 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

static	t_node *search_ptr(t_node *tmp, void *ptr)
{
	while (tmp)
	{
		if (tmp->ptr == ptr)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void ft_free(void *ptr)
{
	t_node	*tmp;

	printf("free %p\n", ptr);
	if (!ptr)
		return ;
	tmp = init_mem()->tiny;
	tmp = tmp->next;
	if ((tmp = search_ptr(tmp, ptr)))
	{
		tmp->free = tmp->size;
		tmp->size = 0;
		if (g_mem->free)
		g_mem->free->previous = tmp;
		tmp->next_free = g_mem->free;
		g_mem->free = tmp;
	}
	tmp = init_mem()->med;
	tmp = tmp->next;
	if ((tmp = search_ptr(tmp, ptr)))
	{
		tmp->free = tmp->size;
		tmp->size = 0;
		if (g_mem->free)
		g_mem->free->previous = tmp;
		tmp->next_free = g_mem->free;
		g_mem->free = tmp;
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
