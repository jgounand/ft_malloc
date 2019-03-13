/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 14:01:39 by jgounand          #+#    #+#             */
/*   Updated: 2018/05/20 17:26:46 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

/**
 **	Input:	unsigned int nb_pages[4]
 **	Output:	t_mem *new
 **	Purpose:	mmap the futur global, with the size of each header and the
 **				size of the global variable
 */

static t_mem	*mem_header(unsigned int nb_pages[4])
{
	t_mem	*new;
	size_t	size;

	size = nb_pages[0] + nb_pages[1] + nb_pages[2] + nb_pages[3];
	new = mmap(NULL, sizeof(t_mem) + getpagesize() * size *NB_PAGES ,
			PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (!new)
	{
		write(2, "ERROR MMAP in mem_header mem.c\n", 20);
		return (NULL);
	}
	ft_bzero(new, sizeof(t_mem) + getpagesize() * size);
	return (new);
}

/**
 **	Input:
 **	Output:	void *new
 **	Purpose:	mmap the place where data will be
 */

static void		*mem_data(void)
{
	void	*new;

	new = mmap(NULL, MAX_TINY + MAX_MED, PROT_READ | PROT_WRITE, MAP_ANON |
			MAP_PRIVATE, -1, 0);
	if (!new)
	{
		write(2, "ERROR MMAP in mem_data() mem.c\n", 20);
		return (NULL);
	}
	return (new);
}

/**
 **	Input:
 **	Output:
 **	Purpose:	Init the first header of Tiny, Small and Data
 */

bool	init_headers()
{
	t_tny	*tny;
	t_start	*start;

	start = (t_start *)(g_mem + 1);
	start->start = mem_data();
	if (!start->start)
		return (1);
	tny = H_TINY;
	tny->ptr = get_addr(start->start);
	tny->size = - MAX_TINY;
	tny = H_MED;
	tny->ptr = get_addr(start->start + MAX_TINY);
	tny->size = - MAX_MED;
	TINY_SIZE--;
	MED_SIZE--;
	A_SIZE--;
	return (0);
}

/**
 **	Input:
 **	Output:	t_mem *g_mem
 **	Purpose:	If g_mem doen t exit, need to alloc
 **				Init size of the header and init the first header
 */

t_mem	*init_mem(void)
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
	init_headers();
	return (g_mem);
}

/**
 **	Input:	t_mem **new
 **	Output:
 **	Purpose:	Cpy from the old g_mem to the new one
 */

void	add_mem_header_0(t_mem **new)
{
	void *dest;
	void *src;
	size_t size;

	ft_memcpy(*new,g_mem, sizeof(t_mem) + getpagesize() * (S_HEADER_A + S_HEADER_T));
	dest = (void *)((*new) + 1) + getpagesize() * (S_HEADER_A + S_HEADER_T + 1);
	src = (void *)(g_mem + 1) + getpagesize() * (S_HEADER_A + S_HEADER_T);
	size = getpagesize() * (S_HEADER_M + S_HEADER_F);
	ft_memcpy(dest, src, size);
	g_mem = *new;
	S_HEADER_T++;
	(*new)->max_size[0] = MAX_HEADER(t_tny, 1);
}

void	add_mem_header_1(t_mem **new)
{
	void *dest;
	void *src;
	size_t size;

		ft_memcpy(*new,g_mem, sizeof(t_mem) + getpagesize() * (S_HEADER_A + S_HEADER_T + S_HEADER_M));
		dest = (void *)((*new) + 1) + getpagesize() * (S_HEADER_A + S_HEADER_T + S_HEADER_M + 1);
		src = (void *)(g_mem + 1) + getpagesize() * (S_HEADER_A + S_HEADER_T + S_HEADER_M);
		size = getpagesize() * (S_HEADER_F);
		ft_memcpy(dest,src , size);
		g_mem = *new;
		S_HEADER_M++;
		(*new)->max_size[1] = MAX_HEADER(t_med, 1);
}

void	add_mem_header_2(t_mem **new)
{
	ft_memcpy(*new,g_mem, sizeof(t_mem) + getpagesize() * (S_HEADER_A + S_HEADER_T + S_HEADER_M + S_HEADER_F));
		g_mem = *new;
		S_HEADER_F++;
		(*new)->max_size[2] = MAX_HEADER(t_fat,1);
}

void	add_mem_header_3(t_mem **new)
{
	void *dest;
	void *src;
	size_t size;

	ft_memcpy(*new,g_mem, sizeof(t_mem) + getpagesize() * (S_HEADER_A));
		dest = (void *)((*new) + 1) + getpagesize() * (S_HEADER_A + 1);
		src = (void *)(g_mem + 1) + getpagesize() * (S_HEADER_A);
		size = getpagesize() * (S_HEADER_T + S_HEADER_M + S_HEADER_F);
		ft_memcpy(dest,src, size);
		g_mem = *new;
		S_HEADER_A++;
		(*new)->max_size[3] = MAX_HEADER(t_start,1);
}

bool	add_mem_header(short type)
{
	t_mem	*new_mem;

	S_HEADER_A++;
	if (!(new_mem = mem_header(g_mem->nb_pages_header)))
		return  (1);
	S_HEADER_A--;
	if (type == 0)
		add_mem_header_0(&new_mem);
	else if (type == 1)
		add_mem_header_1(&new_mem);
	else if (type == 2)
		add_mem_header_2(&new_mem);
	else if (type == 3)
		add_mem_header_3(&new_mem);
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
		add_mem_header (3);
	if (get_start(ptr, 1) != (t_start *)0)
		return (get_start(ptr,0) + 1);
	new = get_start(ptr, 0) + 1;
	tmp = mem_data();
	if (!tmp)
		return (NULL);
	new->start= tmp;
	A_SIZE--;
	return (new);
}
