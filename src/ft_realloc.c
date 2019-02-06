/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 12:27:24 by jgounand          #+#    #+#             */
/*   Updated: 2018/05/24 14:58:23 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

static bool	need_alloc(t_tny *node, size_t size)
{
	if ((node + 1)->ptr - (void *)node->ptr >= (long)size)
		return (0);
	return (1);
}

static bool	same_node(size_t size, short type)
{
	if ((size <= TINY && type == 0) || (size > TINY && size <= SMALL && type == 1))
		return (1);
	return (0);
}

static void	*ft_realloc_small(void *ptr, size_t size, short type)
{
	t_tny	*node;
	void	*new;

	if (!type)
		node = H_TINY;
	else
		node = H_MED;
	if (!(node = ret_node(node, ptr)))
	{
			printf("Error ptr inconnu\n");
			exit (65);
	}
	if (need_alloc(node, size) || !same_node(size, type))
	{
		new = ft_malloc(size);
		ft_memcpy(new, node, ((int)size < node->size ? size : node->size));
		ft_free(ptr);
		return (new);
	}
	else
	{
		node->size = size;
		add_node_free(node, ptr, type);
	//	try_defragment(node +1);
		return (node->ptr);
	}
		return (new);
}
static	void	*ft_realloc_fat(void *ptr, size_t size)
{
	t_fat	*fat;
	size_t	node;
	void	*new;

	fat = H_FAT;
	node = MAX_HEADER(t_fat, S_HEADER_F) - FAT_SIZE;
	while(node)
	{
		if (fat->ptr == ptr)
			break ;
		fat++;
		node--;
	}
	if (!node)
	{
		printf("Error %p non reconnu\n", ptr);
	}
	new = malloc(size);
	if (size < fat->size)
		ft_memcpy(new, ptr, size);
	else
		ft_memcpy(new, ptr, fat->size);
	ft_free(ptr);
	return (new);
}

void *ft_realloc(void *ptr, size_t size)
{
	short	type;

	type = get_type(ptr);
	if (type != 2)
		return (ft_realloc_small(ptr, size, type));
	else
		return(ft_realloc_fat(ptr, size));
}
