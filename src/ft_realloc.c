/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 12:27:24 by jgounand          #+#    #+#             */
/*   Updated: 2018/05/24 12:52:30 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

static bool	need_alloc(t_tny *node, size_t size)
{
	if ((node + 1)->ptr - node->ptr >= size)
		return (0);
	return (1);
}

static void	*ft_realloc_small(void *ptr, size_t size, short type)
{
	t_tny	*node;

	if (!type)
		node = H_TINY;
	else
		node = H_MED;
	if (!(node = ret_node(node, ptr)))
	{
			printf("Error ptr inconnu\n");
			exit (65);
	}
	if (need_alloc(node, size))
	{
		ft_free(ptr);
		return (ft_malloc(size));
	}
	else
	{

	}
}

void *ft_realloc(void *ptr, size_t size)
{
	short	type;

	type = get_type(ptr);
	if (type != 2)
		return (ft_realloc_small(ptr, size, type));
	else
		ft_realloc_fat(ptr, size);
}
