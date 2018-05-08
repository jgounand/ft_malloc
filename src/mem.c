/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 14:01:39 by jgounand          #+#    #+#             */
/*   Updated: 2018/05/08 16:12:23 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

static t_mem	*mem_header(size_t nb_pages)
{
	t_mem	*new;

	new = mmap(NULL, sizeof(t_mem) + getpagesize() * nb_pages,
			PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (!new)
	{
		write(2, "ERROR MMAP in mem_header mem.c\n", 20);
		return (NULL);
	}
	ft_bzero(new, sizeof(t_mem) + getpagesize() * nb_pages);
	return (new);
}

static void	*mem_data(void)
{
	t_mem	*new;

	new = mmap(NULL, MAX_TINY + MAX_MED, PROT_READ | PROT_WRITE, MAP_ANON |
			MAP_PRIVATE, -1, 0);
	if (!new)
	{
		write(2, "ERROR MMAP in mem_data() mem.c\n", 20);
		return (NULL);
	}
	return (new);
}

t_mem	*init_mem(void)
{
	t_start	*start;

	if (g_mem)
		return (g_mem);
	if (!(g_mem = mem_header(4)))
		exit (1);
	TINY_SIZE = MAX_HEADER(t_tny);
	MED_SIZE = MAX_HEADER(t_med);
	FAT_SIZE = MAX_HEADER(t_fat);
	S_HEADER_A = 1;
	S_HEADER_T = 1;
	S_HEADER_M = 1;
	S_HEADER_F = 1;
start = (t_start *)(g_mem + 1);
	if (!(start->start = mem_data()))
		exit (1);
	printf("HEADER_A %p\n", (t_start *)(g_mem + 1));
	printf("HEADER_T %p\n", H_TINY);
	printf("HEADER_M %p\n", H_MED);
	printf("HEADER_F %p\n", H_FAT);
	return (g_mem);
}
