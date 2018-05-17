/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 14:01:39 by jgounand          #+#    #+#             */
/*   Updated: 2018/05/17 15:58:58 by jgounand         ###   ########.fr       */
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

void	clear_header(void)
{
	t_tny	*tny;
	size_t	node;

	node = MAX_HEADER(t_med, S_HEADER_M) - MED_SIZE;
	tny = H_MED;
	while (node)
	{
		if (!tny->ptr && !tny->size)
			MED_SIZE++;
		tny++;
		node--;
	}
	node = MAX_HEADER(t_tny, S_HEADER_T) - TINY_SIZE;
	tny = H_TINY;
	while (node)
	{
		if (!tny->ptr && !tny->size)
			TINY_SIZE++;
		tny++;
		node--;
	}
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
	A_SIZE = MAX_HEADER(t_start, S_HEADER_A);
	start = (t_start *)(g_mem + 1);

	//start->start = (t_start *)(g_mem + 1);
	start->start = mem_data();
	t_tny	*tny;

	tny = H_TINY;
	tny->ptr = get_addr(start->start);
	tny->size = - MAX_TINY;
	printf("tny->ptr %p size %d\n", tny->ptr, tny->size);
	tny = H_MED;
	tny->ptr = get_addr(start->start + MAX_TINY);
	tny->size = - MAX_MED;
	TINY_SIZE--;
			MED_SIZE--;
			A_SIZE--;
	printf("med->ptr %p size %d\n", tny->ptr, tny->size);
	
	printf("HEADER_A %p\n", (t_start *)(g_mem + 1));
	printf("HEADER_T %p\n", H_TINY);
	printf("HEADER_M %p\n", H_MED);
	printf("HEADER_F %p\n", H_FAT);
	printf("TINY_SIZE %lu\n", TINY_SIZE);
	printf("MED_SIZE %lu\n", MED_SIZE);
	printf("FAT_SIZE %lu\n", FAT_SIZE);
	printf("INIT=>start->start %p\n", start->start);
	printf("S_HEADER_A %d\n", S_HEADER_A);
	printf("S_HEADER_T %d\n", S_HEADER_T);
	printf("S_HEADER_M %d\n", S_HEADER_M);
	printf("S_HEADER_F %d\n", S_HEADER_F);
//	exit (1);
	return (g_mem);
}

void	add_mem_header(short type)
{
	//	show_alloc_mem();
	t_mem	*new;
	size_t	s_cpy;
	size_t	total;

	//show_alloc_mem();
	printf("S_HEADER_A %d\n", S_HEADER_A);
	printf("S_HEADER_T %d\n", S_HEADER_T);
	printf("S_HEADER_M %d\n", S_HEADER_M);
	printf("S_HEADER_F %d\n", S_HEADER_F);
	printf("TINY_SIZE %lu\n", TINY_SIZE);
//	show_alloc_mem();
	printf("\n\n");
	total = getpagesize() * (S_HEADER_A + S_HEADER_T + S_HEADER_M + S_HEADER_F);
	if (type == 0)
	{
		s_cpy = getpagesize() * (S_HEADER_A + S_HEADER_T);
		S_HEADER_T++;
	}
	else if (type == 1)
	{
		s_cpy =getpagesize() * ( S_HEADER_A + S_HEADER_T + S_HEADER_M);
		S_HEADER_M++;
	}
	else if (type == 2)
	{
		s_cpy = getpagesize()* (S_HEADER_A + S_HEADER_T + S_HEADER_M + S_HEADER_F);
		S_HEADER_F++;
	}
	else
	{
		s_cpy = getpagesize() * S_HEADER_A;
		S_HEADER_A++;
	}
	if (!(new = mem_header(g_mem->nb_pages_header)))
		exit (1);
	ft_memcpy(new , g_mem , s_cpy);
	ft_memcpy((void *)(new) + s_cpy + getpagesize(), (void *)(g_mem) + s_cpy, total - s_cpy);
	ft_memcpy(new, g_mem, sizeof (t_mem));
	ft_memcpy(new->nb_pages_header, g_mem->nb_pages_header, sizeof(unsigned int[4]));
	ft_memcpy(new->max_size, g_mem->max_size, sizeof(unsigned int[4]));
	if (type == 0)
	{
		printf("reset 0\n");
		new->max_size[0] = MAX_HEADER(t_tny, 1);
	}
	else if (type == 1)
	{
		printf("reset 1\n");
		new->max_size[1] = MAX_HEADER(t_med, 1);
	}
	else if (type == 2)
	{
		printf("reset 2\n");
		new->max_size[2] = MAX_HEADER(t_fat,1);
	}
	else if (type == 3)
	{
		printf("reset 3\n");
		new->max_size[3] = MAX_HEADER(t_start,1);
	}
	t_start	*start = (t_start *)(g_mem + 1);
	munmap(g_mem, total);
	g_mem = new;
	start = (t_start *)(g_mem + 1);
	printf("\nHEADER_A %p\n\n", start->start);
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
	//exit(1);
	//checker ici !!!! le nombre de header
	//	exit (1);
//	show_alloc_mem();
	//if (i ==3)
//	exit(1);
	if (TINY_SIZE > 300 || MED_SIZE >300)
		exit(1);
//	show_alloc_mem();
//	exit (1);
}
/*
void	*get_data(void *ptr,short type, size_t lenght, t_tny *current)
{
	t_start	*start;
	size_t	cpt;

	cpt = 0;
	start = (t_start *)(g_mem + 1);
	printf("=>Get_DATAstart->start %p ptr %p\n", start->start + (type ? MAX_TINY + MAX_MED : MAX_TINY), ptr);
	printf("type %d lenght %lu ptr %p\n", type, lenght ,ptr);
	while (start->start)
	{
		printf("ptr + lenght %p max %p min %p type %d %lu cpt %lu\n",ptr + lenght, start->start + (type ? MAX_TINY + MAX_MED : MAX_TINY), start->start + (type ? MAX_TINY : 0), type, A_SIZE, cpt);
		printf("doit etre plus petit %d soit etre plus grand %d\n", ptr + lenght <= start->start + (type ? MAX_MED + MAX_TINY : MAX_TINY), ptr + lenght >= start->start + (type ? MAX_TINY : 0));

		if (ptr + lenght < start->start + (type ? MAX_MED + MAX_TINY : MAX_TINY) && ptr + lenght >= start->start + (type ? MAX_TINY : 0))
			break;
		start++;
		cpt++;
	}
	if (!start->start)
	{
		printf("start->data %p\n", ((t_start *)(g_mem + 1))->start);
		printf("(start - 1)->start %p\n", (start -1)->start);
		dprintf(2,"il faut add space cpt %lu\n", cpt);
		start->start = mem_data();
		current->ptr = ptr;
		current->size = -((start->start + (type ? MAX_MED + MAX_TINY : MAX_TINY))-((current -1)->ptr + (current -1)->size));
		(current + 1)->ptr = start->start + (type ? MAX_TINY : 0);
		(current + 1)->size = lenght;
		A_SIZE--;
		if (!type)
			TINY_SIZE--;
		else
			MED_SIZE--;
		//	if (cpt == 2)
		//		exit(1);
		printf("ptr free fin size %d et serait %lu\n", current->size, (uintptr_t)((current -1)->ptr + (current -1)->size) - (uintptr_t)(start->start + MAX_TINY));
		//exit (1);
		return (NULL);
	}
	printf("return get_data %p next ptr %p \n\n\n", ptr, get_addr(ptr + lenght + 1) + 2);
	//printf("A_SIZE %lu\n", A_SIZE);
	return (ptr);
}
*/
t_start	*get_start(void *ptr, bool next)
{
	t_start	*start;
	size_t	node;

	node = MAX_HEADER(t_start, S_HEADER_A) - A_SIZE;
	start = (t_start *)(g_mem + 1);
	printf ("get_start ptr %p\n", ptr);
	while (node--)
	{
		if (ptr >= start->start && ptr <= start->start + MAX_MED + MAX_TINY)
			break;
	//	printf("start %p node %lu\n", start, node);
		start++;
	}
	printf("get_start ret node %lu\n", node);
	if (next)
	{
		return ((t_start *)node);
	}
	return (start);
}

t_start	*get_new_data(void *ptr)
{
	t_start	*new;

	dprintf(2, "TINY_SIZE %lu MED_SIZE %lu\n", TINY_SIZE, MED_SIZE);
	dprintf(2, "ptr %p\n", ptr);
	if (!S_HEADER_A)
	{
		add_mem_header(3);
		exit (1);
	}
	if (get_start(ptr, 1) != (t_start *)0)
		return (get_start(ptr,0));
	new = get_start(ptr, 0) + 1;
	new->start = mem_data();
	A_SIZE--;
	dprintf(2, "\t\t\t\t\t\t\t\tA_SIZE %lu\n", A_SIZE);
	dprintf(2,"new %p\n",new->start);
		if (TINY_SIZE > 300 || MED_SIZE > 300)
		{
			dprintf(2, "TINY_SIZE %lu MED_SIZE %lu\n", TINY_SIZE, MED_SIZE);
			exit (3);
	}
	return (new);
}
