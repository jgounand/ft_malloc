/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 19:31:21 by jgounand          #+#    #+#             */
/*   Updated: 2018/04/21 13:55:24 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/ft_malloc.h"

void show_alloc_mem(void)
{
	bool first;

	first = 1;
	init_mem();
	t_node	*tmp;
	tmp = (t_node *)(g_mem + 1);
	printf("TINY : %p\n", tmp->end);
	while (tmp->next)
	{
		if (first)
			first = 0;
		else if (tmp->size)
		printf("%p - %p : %lu octets type %d\n", tmp->ptr, tmp->end , tmp->size, tmp->type);
		tmp = tmp->next;
	}
	tmp = (t_med *)(g_mem + getpagesize());
	printf("SMALL : %p\n", tmp->end);
	first = 1;
	while (tmp->next)
	{
		if (first)
			first = 0;
		else if (tmp->size)
		printf("%p - %p : %lu octets type %d\n", tmp->ptr, tmp->end , tmp->size, tmp->type);
		tmp = tmp->next;
	}
	tmp = (t_med *)(g_mem + getpagesize() * 2);
	printf("LARGE: %p\n", tmp->end + getpagesize());
	first = 1;
	while (tmp->next)
	{
		if (first)
			first = 0;
		else if (tmp->size)
		printf("%p - %p : %lu octets type %d\n", tmp->ptr, tmp->end , tmp->size, tmp->type);
		tmp = tmp->next;
	}
}
