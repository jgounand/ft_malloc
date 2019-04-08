/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_mem_header.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:39:39 by jgounand          #+#    #+#             */
/*   Updated: 2019/04/08 16:44:43 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

/*
**	Input:	t_mem **new
**	Output:
**	Purpose:	Cpy from the old g_mem to the new one
*/

static void	add_mem_header_0(t_mem **new)
{
	void	*dest;
	void	*src;
	size_t	size;

	ft_memcpy(*new, g_mem, sizeof(t_mem) + getpagesize() *
	(S_HEADER_A + S_HEADER_T));
	dest = (void *)((*new) + 1) + getpagesize() *
	(S_HEADER_A + S_HEADER_T + 1);
	src = (void *)(g_mem + 1) + getpagesize() * (S_HEADER_A + S_HEADER_T);
	size = getpagesize() * (S_HEADER_M + S_HEADER_F);
	ft_memcpy(dest, src, size);
	g_mem = *new;
	S_HEADER_T++;
	(*new)->max_size[0] = MAX_HEADER(t_tny, 1);
}

static void	add_mem_header_1(t_mem **new)
{
	void	*dest;
	void	*src;
	size_t	size;

	ft_memcpy(*new, g_mem, sizeof(t_mem) + getpagesize() * (S_HEADER_A +
	S_HEADER_T + S_HEADER_M));
	dest = (void *)((*new) + 1) + getpagesize() * (S_HEADER_A + S_HEADER_T +
	S_HEADER_M + 1);
	src = (void *)(g_mem + 1) + getpagesize() * (S_HEADER_A + S_HEADER_T +
	S_HEADER_M);
	size = getpagesize() * (S_HEADER_F);
	ft_memcpy(dest, src, size);
	g_mem = *new;
	S_HEADER_M++;
	(*new)->max_size[1] = MAX_HEADER(t_med, 1);
}

static void	add_mem_header_2(t_mem **new)
{
	ft_memcpy(*new, g_mem, sizeof(t_mem) + getpagesize() * (S_HEADER_A +
	S_HEADER_T + S_HEADER_M + S_HEADER_F));
	g_mem = *new;
	S_HEADER_F++;
	(*new)->max_size[2] = MAX_HEADER(t_fat, 1);
}

static void	add_mem_header_3(t_mem **new)
{
	void	*dest;
	void	*src;
	size_t	size;

	ft_memcpy(*new, g_mem, sizeof(t_mem) + getpagesize() * (S_HEADER_A));
	dest = (void *)((*new) + 1) + getpagesize() * (S_HEADER_A + 1);
	src = (void *)(g_mem + 1) + getpagesize() * (S_HEADER_A);
	size = getpagesize() * (S_HEADER_T + S_HEADER_M + S_HEADER_F);
	ft_memcpy(dest, src, size);
	g_mem = *new;
	S_HEADER_A++;
	(*new)->max_size[3] = MAX_HEADER(t_start, 1);
}

bool		add_mem_header(short type)
{
	t_mem	*new_mem;

	S_HEADER_A++;
	if (!(new_mem = mem_header(g_mem->nb_pages_header)))
		return (1);
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
