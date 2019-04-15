/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 18:23:15 by jgounand          #+#    #+#             */
/*   Updated: 2019/04/09 17:18:25 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

/*
**	Input:	t_tny *node
**			size_t size
**	Output:	void *new_ptr
**	Purpose:	malloc size
**				cpy max size possible of node->ptr
**				free node->ptr
*/

void		*r_mall_free(t_tny *node, size_t size)
{
	void	*new_ptr;
	t_tny	tmp;

	tmp.size = node->size;
	tmp.ptr = node->ptr;
	new_ptr = ft_malloc(size);
	ft_memcpy(new_ptr, node->ptr, (size < (size_t)tmp.size ? size : tmp.size));
	ft_free(tmp.ptr);
	return (new_ptr);
}

/*
**	Input:	t_tny **node
**			size_t size
**			short type
**	Output:	void *same_ptr
**	Purpose:	Place to fit the realloc with node + 1
**				Save the size beetwen node->ptr and (node+1)->ptr
**					and (node+1)->size
**				Dell the node + 1,
**				Add node free if size > 16 (addr every % 8)
*/

void		*r_with_node1(t_tny **node, size_t size, short type)
{
	size_t c_lenght;

	c_lenght = ((*node) + 1)->ptr - (*node)->ptr - ((*node) + 1)->size;
	ft_memmove((*node) + 1, (*node) + 2, ((void *)(type ? H_MED : H_TINY) +
	sizeof(t_tny) * MAX_HEADER(t_tny, (type ? S_HEADER_M : S_HEADER_T)) -
	(void *)((*node) + 2)));
	(*node)->size = size;
	if (c_lenght - size > 16)
		add_node_free(*node, get_addr((*node)->ptr + size + 1), type);
	else
	{
		if (type)
			MED_SIZE++;
		else
			TINY_SIZE++;
	}
	return ((*node)->ptr);
}

/*
**	Input:	t_tny **node
**			size_t size
**			short type
**	Output:	void *same_ptr
**	Purpose:	Place to fit the realloc with node
**				Save the size beetwen node->ptr and (node+1)->ptr
**				Add node free if size > 16 (addr every % 8)
**				Add size HEADER if add_free
*/

void		*r_with_node(t_tny **node, size_t size, short type)
{
	long	size_free;
	void	*ptr;

	size_free = 0;
	if (diff_data(*node, type))
		size_free = (*node)->size;
	else
		size_free = ((*node) + 1)->ptr - (void *)(*node)->ptr;
	(*node)->size = size;
	ptr = (*node)->ptr;
	if (size_free - size > 16)
	{
		add_node_free((*node), get_addr((*node)->ptr + size + 1), type);
		if (!type)
			TINY_SIZE--;
		else
			MED_SIZE--;
		ptr = (*node)->ptr;
		if (check_header_left() == 2)
			return (NULL);
	}
	return (ptr);
}
