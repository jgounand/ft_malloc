/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 14:01:39 by jgounand          #+#    #+#             */
/*   Updated: 2019/04/09 17:28:39 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

/*
**	Input:	t_tny **tmp
**			short type
**			short position
**	Output: void
**	Purpose:	add data on both Header Tiny and Med
*/

void		add_mem_data(t_tny **tmp, short type, short position)
{
	t_tny	*tmp2;
	t_start	*start;

	start = get_new_data(((*tmp) - 1)->ptr);
	if (type)
	{
		tmp2 = H_TINY + MAX_HEADER(t_tny, S_HEADER_T) - TINY_SIZE;
		tmp2->ptr = get_addr(start->start);
		((*tmp) + position)->ptr = get_addr(start->start + MAX_TINY);
	}
	else
	{
		tmp2 = H_MED + MAX_HEADER(t_med, S_HEADER_M) - MED_SIZE;
		((*tmp) + position)->ptr = get_addr(start->start);
		tmp2->ptr = get_addr(start->start + MAX_TINY);
	}
	((*tmp) + position)->size = -MAX_MED;
	tmp2->size = -MAX_MED;
	if (!position)
	{
		add_rm_header(4, type);
		return ;
	}
	add_rm_header(0, type);
	return ;
}

/*
**	Input:	unsigned int nb_pages[4]
**	Output:	t_mem *new
**	Purpose:	mmap the futur global, with the size of each header and the
**				size of the global variable
*/

t_mem		*mem_header(unsigned int nb_pages[4])
{
	t_mem	*new;
	size_t	size;

	size = nb_pages[0] + nb_pages[1] + nb_pages[2] + nb_pages[3];
	new = mmap(NULL, sizeof(t_mem) + getpagesize() * size * NB_PAGES,
	PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (!new)
	{
		write(2, "ERROR MMAP in mem_header mem.c\n", 20);
		return (NULL);
	}
	return (new);
}

/*
**	Input:
**	Output:	void *new
**	Purpose:	mmap the place where data will be
*/

void		*mem_data(void)
{
	void	*new;

	new = mmap(NULL, MAX_TINY + MAX_MED, PROT_READ | PROT_WRITE, MAP_ANON |
			MAP_PRIVATE, -1, 0);
	if (!new)
	{
		write(2, "ERROR MMAP in mem_data() mem.c\n", 20);
		return (NULL);
	}
	ft_bzero(new, MAX_TINY + MAX_MED);
	return (new);
}

/*
**	Input:
**	Output:
**	Purpose:	Init the first header of Tiny, Small and Data
*/

static bool	init_headers(void)
{
	t_tny	*tny;
	t_start	*start;

	start = (t_start *)(g_mem + 1);
	start->start = mem_data();
	if (!start->start)
		return (1);
	tny = H_TINY;
	tny->ptr = get_addr(start->start);
	tny->size = -MAX_TINY;
	tny = H_MED;
	tny->ptr = get_addr(start->start + MAX_TINY);
	tny->size = -MAX_MED;
	TINY_SIZE--;
	MED_SIZE--;
	A_SIZE--;
	return (0);
}

/*
**	Input:
**	Output:	t_mem *g_mem
**	Purpose:	If g_mem doen t exit, need to alloc
**				Init size of the header and init the first header
*/

t_mem		*init_mem(void)
{
	unsigned int	header_size[4];

	if (g_mem)
		return (g_mem);
	header_size[0] = 1;
	header_size[1] = 1;
	header_size[2] = 1;
	header_size[3] = 1;
	if (!(g_mem = mem_header(header_size)))
		return (NULL);
	S_HEADER_A = 1;
	S_HEADER_T = 1;
	S_HEADER_M = 1;
	S_HEADER_F = 1;
	TINY_SIZE = MAX_HEADER(t_tny, S_HEADER_T);
	MED_SIZE = MAX_HEADER(t_med, S_HEADER_M);
	FAT_SIZE = MAX_HEADER(t_fat, S_HEADER_F);
	A_SIZE = MAX_HEADER(t_start, S_HEADER_A);
	if (init_headers())
		return (NULL);
	return (g_mem);
}
