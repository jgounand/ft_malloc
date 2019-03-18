/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 04:00:29 by jgounand          #+#    #+#             */
/*   Updated: 2018/04/23 04:02:30 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

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
/**
 **	Input:
 **	Output:
 **	Purpose:	Check if they are place on headers => add_mem_header
 **				
 */

short	check_header_left(void)
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
 **	Input:	void *ptr
			bool nextw
 **	Output:
 **	Purpose:	Find the node where ptr is inside of the range allocate of start
 **				If next return nb node else return the node find
 */

t_start	*get_start(void *ptr, bool next)
{
	t_start	*start;
	size_t	node;

	node = MAX_HEADER(t_start, S_HEADER_A) - A_SIZE;
	start = (t_start *)(g_mem + 1);
	while (node--)
	{
		if (ptr >= start->start && ptr < start->start + MAX_MED + MAX_TINY)
			break;
		start++;
	}
	if (next)
		return ((t_start *)node);
	return (start);
}

/**
 **	Input:	void *ptr
 **	Output:
 **	Purpose:	If they are no Header palce left, alloc need place
 **				If its not the last header start return the next one
 **				Add new start at the end
 */

t_start	*get_new_data(void *ptr)
{
	t_start	*new;
	void	*tmp;

	if (!A_SIZE)
		add_mem_header(3);
	if (get_start(ptr, 1) != (t_start *)0)
		return (get_start(ptr, 0) + 1);
	new = get_start(ptr, 0) + 1;
	tmp = mem_data();
	if (!tmp)
		return (NULL);
	new->start= tmp;
	A_SIZE--;
	return (new);
}
