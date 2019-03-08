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

static short	need_alloc(t_tny *node, size_t size)
{
	size_t	current_lenght;

	if (!diff_data(node))
		current_lenght = (node + 1)->ptr - (void *)node->ptr;
	else
		current_lenght = node->size;
	if (current_lenght > size + 1)
		return (0);
	else if (!diff_data(node) && (node + 1)->size < 0 && current_lenght
		- (node + 1 )->size > size + 1)
		return (2);
	return (1);
}

static void		*ft_realloc_small(void *ptr, size_t size, short type)
{
	t_tny	*node;
	void	*new;
	short	need_all;

	if (!type)
		node = H_TINY;
	else
		node = H_MED;
	if (!(node = ret_node(node, ptr)))
		return  (NULL);
	if ((need_all = need_alloc(node, size)) == 1)
	{
		size_t node_size = node->size;
		new = ft_malloc(size);
		ft_memcpy(new, node->ptr, (size < node_size ? size : node_size));
		ft_free(ptr);
		return (new);
	}
	else if (need_all == 2)
	{
		size_t current_lenght = (node + 1)->ptr - node->ptr - (node + 1)->size;
		size_t size_to_move = ((void *)(type ? H_MED :H_TINY) + sizeof(t_tny) * MAX_HEADER(t_tny, (type ? S_HEADER_M : S_HEADER_T)) -  (void *)(node + 2));
		ft_memmove(node + 1,node + 2,size_to_move);
		node->size = size;
		void *tmp_ptr = get_addr(node->ptr + size + 1);
		if (current_lenght - size > 8)
			add_node_free(node,tmp_ptr,type);
		else
		{
			if (type)
				MED_SIZE++;
			else
				TINY_SIZE++;
		}
		return (node->ptr);
	}
	else
	{
		long	size_free = 0;
		if (diff_data(node))
			size_free = node->size;
		else
			size_free = (node + 1)->ptr - (void *)node->ptr;
		node->size = size;
		if (size_free - size > 8)
		{
		add_node_free(node, get_addr(node->ptr + size + 1), type);
			if (!type)
				TINY_SIZE--;
			else
				MED_SIZE--;
		}
		return (node->ptr);
	}
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
		return (NULL);
	size_t size_current = fat->size;
	new = ft_malloc(size);
	if (size < size_current)
		ft_memcpy(new, ptr, size);
	else
		ft_memcpy(new, ptr, size_current);
	ft_free(ptr);
	return (new);
}


void *ft_realloc(void *ptr, size_t size)
{
	short	type;

	if (size <= 0 || !ptr)
	{
		if (ptr)
			ft_free(ptr);
		return (NULL);
	}
	type = get_type(ptr);
	if (type == 0 || type == 1)
		return (ft_realloc_small(ptr, size, type));
	else if (type == 2)
		return(ft_realloc_fat(ptr, size));
	else
		return (NULL);
}
