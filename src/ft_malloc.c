/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 20:46:23 by jgounand          #+#    #+#             */
/*   Updated: 2018/05/24 14:29:59 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

t_mem	*g_mem = NULL;

/**
 **	Input:	void *ptr
 **	Output:	void *ptr
 **	Purpose:	return the next ptr % 8
 */

void *get_addr(void *ptr)
{
	while ((uintptr_t)ptr % 8)
		ptr++;
	return (ptr);
}

/**
 **	Input:	t_tny **tmp
 **			short type
 **	Output:	size_t bytes_cpy
 **	Purpose:	Get size beetwen MAX position header and the current + 1
 **				Move tmp + 1 => tmp + 2 to have the place to add the free node
 */

size_t push_header(t_tny **tmp, short type)
{
	void *max;
	size_t bytes_cpy;

	if (type == 0)
	{
		max = H_TINY + MAX_HEADER(t_tny,S_HEADER_T);
		bytes_cpy = (void *)(max) - (void *)((*tmp) + 1) - sizeof(t_tny) * TINY_SIZE;
	}
	else
	{
		max = H_MED + MAX_HEADER(t_med,S_HEADER_M);
		bytes_cpy = (void *)(max) - (void *)((*tmp) + 1) - sizeof(t_tny) * MED_SIZE;
	}
	ft_memmove((*tmp) + 2, (*tmp) + 1, bytes_cpy);
	return (bytes_cpy);
}

/**
 **	Input:	t_tny **tmp
 **			short type
 **			size_t bytes_cpy
 **	Output:	size_t bytes_cpy
 **	Purpose:	Move tmp + 2 => tmp + 1 to delete the node tmp + 1
 */

size_t	remove_header(t_tny **tmp, size_t bytes_cpy, short type)
{

	ft_memmove((*tmp) + 1, (*tmp) + 2, bytes_cpy);
	if (!type)
		TINY_SIZE++;
	else
		MED_SIZE++;
	return (bytes_cpy);
}

/**
 **	Input:	t_tny *tmp
 **			void *ptr
 **			bool type
 **	Output:	void* NULL
 **	Purpose:	Get size beetwen (tmp + 1) and end
 **				Push header tmp + 1 to have the place to put the need node free
 **				if same data tmp + 1 and tmp + 2 size = diff ptr tmp1 and tmp2
 **				else size = MAX - (tmp + 1)->ptr
 **				if new size == 0 => remove the header
 */

void	*add_node_free(t_tny *tmp, void *ptr, bool type)
{
	size_t bytes_cpy;

	bytes_cpy = push_header(&tmp,type);
	(tmp + 1)->ptr = ptr;
	if (!diff_data(tmp + 1))
		(tmp + 1)->size = -((tmp + 2)->ptr - (tmp + 1)->ptr);
	else
	{
		(tmp + 1)->size = -(((void *)(get_start((tmp + 1)->ptr, 0)->start) + MAX_TINY  + (type ? MAX_MED : 0)) - (tmp + 1)->ptr);
		if (!(tmp + 1)->size)
			remove_header(&tmp,bytes_cpy,type);
	}
	return (NULL);
}

/**
 **	Input:	short type
 **			size_t lenght
 **	Output:	t_infonode node
 **	Purpose:	Get the number Header and the start of the header
 **				Break if they are no node left or node free > lenght
 */

t_tny *get_free_node(short type,size_t lenght)
{
	t_tny 	*tmp;
	size_t	node_left;

	tmp = type ? H_MED : H_TINY;
	node_left = type ? MAX_HEADER(t_med, S_HEADER_M) - MED_SIZE : MAX_HEADER(t_tny, S_HEADER_T) - TINY_SIZE;
	while (node_left)
	{
		if (!node_left || (tmp->size < 0 && lenght <= (size_t)-tmp->size))
			break ;
		tmp++;
		node_left--;
	}
	ft_putstr("\nstart get free node\n");
	print_addrhex((uint16_t)tmp->ptr);
	ft_putstr(" ");
	ft_putnbr(node_left);
	ft_putstr("\nfin get free node\n");
	return (tmp);
}
/**
 **	Input:	short type
 **			size_t lenght
 **	Output:	t_infonode node
 **	Purpose:	Get the number Header and the start of the header
 **				Break if they are no node left or node free > lenght
 */

size_t get_free_nodeleft(short type,size_t lenght)
{
	t_tny 	*tmp;
	size_t	node_left;

	tmp = type ? H_MED : H_TINY;
	node_left = type ? MAX_HEADER(t_med, S_HEADER_M) - MED_SIZE : MAX_HEADER(t_tny, S_HEADER_T) - TINY_SIZE;
	while (node_left)
	{
		if (!node_left || (tmp->size < 0 && lenght <= (size_t)-tmp->size))
			break ;
		tmp++;
		node_left--;
	}
	return (node_left);
}
/**
 **	Input:	short add
 **			short type
 **	Output:
 **	Purpose:	add or remove header_size 
 */

void	add_rm_header(short add, short type)
{
	if (add == 1)
	{
		if (!type)
			TINY_SIZE++;
		else
			MED_SIZE++;
	}
	else if (add == 0)
	{
		if (!type)
			TINY_SIZE--;
		else
			MED_SIZE--;
	}
	else if (add == 4)
	{
		TINY_SIZE--;
		MED_SIZE--;
	}
}

void	check_header_zero(short type)
{

	size_t	node_left;
	t_tny	*tmp;

	tmp = type ? H_MED : H_TINY;
	node_left = type ? MAX_HEADER(t_med, S_HEADER_M) - MED_SIZE : MAX_HEADER(t_tny, S_HEADER_T) - TINY_SIZE;
	while (node_left)
	{
		if (!node_left)
			break ;
		if (!tmp->size)
		{
			ft_putstr("check header zero OK\n");
			void *max;
			size_t bytes_cpy;

			if (type == 0)
			{
				max = H_TINY + MAX_HEADER(t_tny,S_HEADER_T);
				bytes_cpy = (void *)(max) - (void *)(tmp + 1) - sizeof(t_tny) * TINY_SIZE;
			}
			else
			{
				max = H_MED + MAX_HEADER(t_med,S_HEADER_M);
				bytes_cpy = (void *)(max) - (void *)(tmp + 1) - sizeof(t_tny) * MED_SIZE;
			}
			remove_header(&tmp,bytes_cpy,type);
			check_header_left(type);
			return ;
		}
		tmp++;
		node_left--;
	}
}

/**
 **	Input:	short type
 **			size_t lenght
 **	Output: void* ptr
 **	Purpose:	Find a node with the place to fit the lenght
 **				Else add new data zone and try again
 **				Save ptr if they are update of the size Header during proscess
 **				The last header need to be a free node, Add data zone if they
**				are not the place to add a free node
**				if nothing of that happen i dont need to increment header
 */

void	*add_small(short type, size_t lenght)
{
	void *new;
	t_tny	*node;
	size_t node_left;
	short	error;

	if ((error = check_header_left()))
	return (error == 1 ? add_small(type,lenght): NULL);
	node = get_free_node(type, lenght);
	node_left = get_free_nodeleft(type,lenght);
	if (!node_left)
	{
		add_mem_data(&node,type,0);
		return (add_small(type, lenght));
	}
	if (!node->ptr)
		print_addrhex((uint16_t)node->ptr);
	new = node->ptr;
	if (!(node_left - 1) && -node->size - lenght < 8)
		add_mem_data(&node,type,1);
	else if (-node->size - lenght > 8)
		add_node_free(node, get_addr(node->ptr + lenght + 1), type);
	else
		add_rm_header(1,type);
	node->size = lenght;
	if ((error = check_header_left()) == 1)
		add_small(type,lenght);
	if (error == 2)
		return (NULL);
	add_rm_header(0,type);
	if (check_header_left() == 2)
		return (NULL);
	check_header_zero(type);
	return (new);
}

/**
 **	Input:	t_tny **tmp
 **			short type
 **			short position
 **	Output: void
 **	Purpose:	add data on both Header Tiny and Med
**				
 */

void	add_mem_data(t_tny **tmp, short type, short position)
{
	t_tny *tmp2;

	t_start	*start = get_new_data(((*tmp) -1)->ptr);
	if (type)
	{
		tmp2 = H_TINY + MAX_HEADER(t_tny, S_HEADER_T) - TINY_SIZE;
		tmp2->ptr = get_addr(start->start);
		((*tmp) + position)->ptr = get_addr(start->start + MAX_TINY);
	}
	else
	{
		tmp2 = H_MED + MAX_HEADER(t_med, S_HEADER_M) - MED_SIZE;
		((*tmp) +position)->ptr = get_addr(start->start);
		tmp2->ptr = get_addr(start->start + MAX_TINY);
	}
	((*tmp) + position)->size = - MAX_MED;
	tmp2->size = - MAX_MED;
	if (!position)
	{
		add_rm_header(4,type);
		return ;
	}
	add_rm_header(0,type);
	return;
}

/**
**	Input:
**	Output:
**	Purpose:	Check if they are place on headers => add_mem_header
**				
*/

short	check_header_left()
{
	short ret;

	ret = 0;
	if (!TINY_SIZE || !MED_SIZE || !A_SIZE || !FAT_SIZE)
	{
		if (!TINY_SIZE)
			ret = add_mem_header(0);
		else if (!MED_SIZE)
			ret = add_mem_header(1);
		else if (!A_SIZE)
			ret = add_mem_header(3);
		else if (!FAT_SIZE)
			ret = add_mem_header(2);
		return (ret + 1);
	}
	return (0);
}

/**
**	Input:	size_t lenght
**	Output: void *ptr
**	Purpose:	Check if they are place on headers => add_mem_header
**				Allez sur la derniere node
**				Mmap la taille
*/

void	*add_fat(size_t lenght)
{
	t_fat *tmp;
	size_t	node;

	if (check_header_left() == 2)
		return (NULL);
	node = MAX_HEADER(t_fat, S_HEADER_F) - FAT_SIZE;
	tmp = H_FAT;
	while (node--)
		tmp++;
	tmp->ptr = mmap(NULL,lenght, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	tmp->size = lenght;
	FAT_SIZE--;
	return (tmp->ptr);
}

/**
**	Input:	size_t lenght
**	Output: void *ptr
**	Purpose:	Init global and call the right function depend of the size
*/

void *ft_malloc(size_t size)
{
	if (size <= 0)
		return (NULL);
	if (!init_mem())
		return (NULL);
	if (size <= TINY)
		return (add_small(0,size));
	else if (size <= SMALL)
		return (add_small(1,size));
	else
		return (add_fat(size));
}
