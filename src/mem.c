/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 14:01:39 by jgounand          #+#    #+#             */
/*   Updated: 2018/05/09 18:49:04 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

static t_mem	*mem_header(unsigned int nb_pages[4])
{
	t_mem	*new;
	size_t	size;

	size = nb_pages[0] + nb_pages[1] + nb_pages[2] + nb_pages[3];
	new = mmap(NULL, sizeof(t_mem) + getpagesize() * size,
			PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (!new)
	{
		write(2, "ERROR MMAP in mem_header mem.c\n", 20);
		exit(1);
		return (NULL);
	}
	ft_bzero(new, sizeof(t_mem) + getpagesize() * size);
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
		exit(1);
	}
	return (new);
}

t_mem	*init_mem(void)
{
	t_start	*start;
	unsigned int	header_size[4];

	if (g_mem)
		return (g_mem);
	header_size[0] = 1;
	header_size[1] = 1;
	header_size[2] = 1;
	header_size[3] = 1;
	if (!(g_mem = mem_header(header_size)))
		exit (1);
	S_HEADER_A = 1;
	S_HEADER_T = 1;
	S_HEADER_M = 1;
	S_HEADER_F = 1;
	TINY_SIZE = MAX_HEADER(t_tny, S_HEADER_T);
	MED_SIZE = MAX_HEADER(t_med, S_HEADER_M);
	FAT_SIZE = MAX_HEADER(t_fat, S_HEADER_F);
	A_SIZE = MAX_HEADER(t_start, S_HEADER_F);

start = (t_start *)(g_mem + 1);
	if (!(start->start = mem_data()))
		exit (1);
	printf("HEADER_A %p\n", (t_start *)(g_mem + 1));
	printf("HEADER_T %p\n", H_TINY);
	printf("HEADER_M %p\n", H_MED);
	printf("HEADER_F %p\n", H_FAT);
	printf("TINY_SIZE %lu\n", TINY_SIZE);
	printf("MED_SIZE %lu\n", MED_SIZE);
	printf("FAT_SIZE %lu\n", FAT_SIZE);
	printf("start->start size %p\n", start->start);
	printf("S_HEADER_A %d\n", S_HEADER_A);
	printf("S_HEADER_T %d\n", S_HEADER_T);
	printf("S_HEADER_M %d\n", S_HEADER_M);
	printf("S_HEADER_F %d\n", S_HEADER_F);
	return (g_mem);
}

void	add_mem_header(short type)
{
//	show_alloc_mem();
	t_mem	*new;
	size_t	s_cpy;
	size_t	total;

	total = sizeof(t_mem) + getpagesize() * (S_HEADER_A + S_HEADER_T + S_HEADER_M + S_HEADER_F);
	if (type == 0)
	{
		s_cpy = sizeof(t_mem) + getpagesize() * (S_HEADER_A + S_HEADER_T);
		S_HEADER_T++;
	}
	else if (type == 1)
	{
		s_cpy = sizeof (t_mem) +getpagesize() * ( S_HEADER_A + S_HEADER_T + S_HEADER_M);
		S_HEADER_M++;
	}
	else if (type == 2)
	{
		s_cpy = sizeof(t_mem) +getpagesize()*( S_HEADER_A + S_HEADER_T + S_HEADER_M + S_HEADER_F);
		S_HEADER_F++;
	}
	else
	{
		s_cpy = sizeof(t_mem);
		S_HEADER_A++;;
	}
	if (!(new = mem_header(g_mem->nb_pages_header)))
		exit (1);
	ft_memcpy(new, g_mem, s_cpy);
	ft_memcpy((void *)new + s_cpy + getpagesize(),(void *)g_mem + s_cpy, total - s_cpy);
	ft_memcpy(new->nb_pages_header, g_mem->nb_pages_header, sizeof(unsigned int[4]));
	ft_memcpy(new->max_size, g_mem->max_size, sizeof(unsigned int[4]));
	new->max_size[0] = MAX_HEADER(t_tny, 1);
	new->max_size[1] = MAX_HEADER(t_med, 1);
	new->max_size[2] = MAX_HEADER(t_fat,1);
	new->max_size[3] = MAX_HEADER(t_start,1);
	t_start	*start = (t_start *)(g_mem + 1);
	printf("start->start %p\n",  (t_start *)(g_mem + 1));
	munmap(g_mem, total);
	g_mem = new;
	printf("HEADER_A %p\n", (t_start *)(g_mem + 1));
	printf("HEADER_T %p\n", H_TINY);
	printf("HEADER_M %p\n", H_MED);
	printf("HEADER_F %p\n", H_FAT);
	printf("TINY_SIZE %lu\n", TINY_SIZE);
	printf("MED_SIZE %lu\n", MED_SIZE);
	printf("FAT_SIZE %lu\n", FAT_SIZE);
	printf("A_SIZE %lu\n", A_SIZE);
	printf("S_HEADER_A %d\n", S_HEADER_A);
	printf("S_HEADER_T %d\n", S_HEADER_T);
	printf("S_HEADER_M %d\n", S_HEADER_M);
	printf("S_HEADER_F %d\n", S_HEADER_F);
	start = (t_start *)(g_mem + 1);
	printf("HEADER_A %p\n", start->start);
	//checker ici !!!! le nombre de header
//	exit (1);
	//show_alloc_mem();
}

void	*get_data(void *ptr,short type, size_t lenght)
{
	t_start	*start;
	size_t	cpt;

	cpt = 0;
	start = (t_start *)(g_mem + 1);
	while (start->start)
	{
		printf("ptr %p min %p max %p type %d %lu cpt %lu\n",ptr + lenght,start->start + MAX_TINY, start->start + MAX_TINY + MAX_MED, type, A_SIZE, cpt);

		if (ptr + lenght < start->start + (type ? MAX_MED + MAX_TINY : MAX_TINY) && ptr >= start->start + (type ? MAX_TINY : 0))
			break;
		start++;
		cpt++;
	if (cpt == 1)
	{
		printf("(start-1)->start %p", ((t_start *)(g_mem + 1))->start);
	exit(1);
	}
	}
	if (!start->start)
	{
		dprintf(2,"il faut add space\n");
		start->start = mem_data();
		A_SIZE--;
		return (start->start + (type ? MAX_TINY : 0));
		}
		return (start);
}

void	add_mem_data(void)
{
	
}
