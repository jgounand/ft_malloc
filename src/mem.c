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
		exit(1);
		return (NULL);
	}
	ft_bzero(new, sizeof(t_mem) + getpagesize() * size);
	printf("sizeotf t_meme %lu\n", sizeof (t_mem));
	printf("size init %lu nb page %lu\n", sizeof(t_mem) + getpagesize () * size ,size);
	return (new);
}
/**
 *
 * @return new data mmap size MAX_TINY + MAX_MED
 */
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
	printf("size beetween g_mem et H_A %lu\n",  (void *)(g_mem + 1) - (void *)g_mem);
	printf("size beetween header_a et H_tiny %lu\n",  ((void *)(g_mem + 1) + getpagesize()) - (void *)(g_mem + 1));
	printf("size beetween H_T et H_ME %lu\n", ((void *)(g_mem + 1) + getpagesize() * 2) - ((void *)(g_mem + 1) + getpagesize()));
	printf("size beetween H_M et H_FAT %lu\n", ((void *)(g_mem + 1) + getpagesize() * 3) - ((void *)(g_mem + 1) + (getpagesize() * 2)));
	printf("size beetween H_F et H_END %lu\n", ((void *)(g_mem + 1) + getpagesize() * 4) - ((void *)(g_mem + 1) + (getpagesize() * 3)));
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
	return (g_mem);
}
void	add_mem_header(short type)
{
    dprintf(2,"add meme header type %u\n",type);
	//	show_alloc_mem();
	t_mem	*new;
	//show_alloc_mem();
//	show_alloc_mem();
	printf("S_HEADER_A %d\n", S_HEADER_A);
	printf("S_HEADER_T %d\n", S_HEADER_T);
	printf("S_HEADER_M %d\n", S_HEADER_M);
	printf("S_HEADER_F %d\n", S_HEADER_F);
	printf("TINY_SIZE %lu\n", TINY_SIZE);
//	show_alloc_mem();
	printf("\n\n");
	//show_alloc_mem();
	S_HEADER_A++;
	if (!(new = mem_header(g_mem->nb_pages_header)))
		exit (1);
	S_HEADER_A--;
//	ft_memcpy(new, g_mem, sizeof(t_mem) + getpagesize() * (S_HEADER_A + S_HEADER_T + S_HEADER_M + S_HEADER_F) + sizeof(t_mem));
   // ft_memcpy(new, g_mem, sizeof(t_mem) + getpagesize() * (S_HEADER_A + S_HEADER_T + S_HEADER_M + S_HEADER_F));
   // exit (13);
   void *dest;
   void *src;
   size_t size;
	dprintf(2,"mem 1");
	show_alloc_mem(2);
	if (type == 0)
	{
		dprintf(1,"reset 0\n");
		dprintf(2,"reset 0\n");
		ft_memcpy(new,g_mem, sizeof(t_mem)  + getpagesize() * (S_HEADER_A + S_HEADER_T));
		dest = (void *)(new + 1) + getpagesize() * (S_HEADER_A + S_HEADER_T + 1);
		src = (void *)(g_mem + 1) + getpagesize() * (S_HEADER_A + S_HEADER_T);
		size = getpagesize() * (S_HEADER_M + S_HEADER_F);
		ft_memcpy(dest, src, size);
//		ft_memmove(
//				(t_med *)((void *)(new + 1) + getpagesize() * (S_HEADER_A + S_HEADER_T + 1)),
//				(t_med *)((void *)(g_mem + 1) + getpagesize() * (S_HEADER_A + S_HEADER_T)), getpagesize() * (S_HEADER_M + S_HEADER_F));
	g_mem = new;
		//ft_bzero((void *)(g_mem+ 1) + getpagesize() * (S_HEADER_A + S_HEADER_T), getpagesize());
	S_HEADER_T++;
		new->max_size[0] = MAX_HEADER(t_tny, 1);
		dprintf(2,"wtf\n");
		show_alloc_mem(2);
		printf("wtf\n");
	}
	else if (type == 1)
	{
		printf("reset 1\n");
		dprintf(2,"reset 1\n");
		//ft_memmove(
		//		(t_med *)((void *)(new +1) + getpagesize() * (S_HEADER_A + S_HEADER_T + S_HEADER_M + 1)),
		//		(t_med *)((void *)(g_mem + 1) + getpagesize() * (S_HEADER_A + S_HEADER_T  + S_HEADER_M)), getpagesize() * (S_HEADER_F));
		ft_memcpy(new,g_mem, sizeof(t_mem) + getpagesize() * (S_HEADER_A + S_HEADER_T + S_HEADER_M));
		dest = (void *)(new + 1) + getpagesize() * (S_HEADER_A + S_HEADER_T + S_HEADER_M + 1);
		src = (void *)(g_mem + 1) + getpagesize() * (S_HEADER_A + S_HEADER_T + S_HEADER_M);
		size = getpagesize() * (S_HEADER_F);
		ft_memcpy(dest,src , size);
	g_mem = new;
	//	ft_bzero((void *)(g_mem + 1) + getpagesize() * (S_HEADER_A + S_HEADER_T + S_HEADER_M), getpagesize());
		S_HEADER_M++;
		new->max_size[1] = MAX_HEADER(t_med, 1);
	}
	else if (type == 2)
	{
		printf("reset 2\n");
		dprintf(2,"reset 2\n");
		ft_memcpy(new,g_mem, sizeof(t_mem) + getpagesize() * (S_HEADER_A + S_HEADER_T + S_HEADER_M + S_HEADER_F));
	g_mem = new;
		S_HEADER_F++;
		new->max_size[2] = MAX_HEADER(t_fat,1);
	}
	else if (type == 3)
	{
		printf("reset 3\n");
		dprintf(2,"reset 3\n");
		ft_memcpy(new,g_mem, sizeof(t_mem) + getpagesize() * (S_HEADER_A));
		dest = (void *)(new + 1) + getpagesize() * (S_HEADER_A + 1);
		src = (void *)(g_mem + 1) + getpagesize() * (S_HEADER_A);
		size = getpagesize() * (S_HEADER_T + S_HEADER_M + S_HEADER_F);
		ft_memcpy(dest,src, size);
	//ft_memmove(
	//			(t_med *)((void *)(new + 1) + getpagesize() * (S_HEADER_A +  1)),
	//			(t_med *)((void *)(g_mem + 1) + getpagesize() * (S_HEADER_A ))
	//			, getpagesize() * (S_HEADER_F + S_HEADER_T + S_HEADER_M));
	g_mem = new;
		//ft_bzero((void *)(g_mem + 1) + getpagesize() * (S_HEADER_A), getpagesize());
		S_HEADER_A++;
		new->max_size[3] = MAX_HEADER(t_start,1);
	//	exit (9);
	}
	t_start	*start = (t_start *)(g_mem + 1);
//	munmap(g_mem, total);
//	g_mem = new;
	start = (t_start *)(g_mem + 1);
	dprintf(2,"mem 2");
	show_alloc_mem(2);
	printf("et la\n");
	printf("\nHEADER_A %p\n\n", start->start);
	printf("HEADER_T %p\n", H_TINY);
	printf("HEADER_M %p\n", H_MED);
	printf("MAX_HEADER M %lu\n", MAX_HEADER(t_med, 1));
	printf("HEADER_F %p\n", H_FAT);
	printf("TINY_SIZE %lu\n", TINY_SIZE);
	printf("MED_SIZE %lu\n", MED_SIZE);
	printf("FAT_SIZE %lu\n", FAT_SIZE);
	printf("A_SIZE %lu\n", A_SIZE);
	printf("S_HEADER_A %d\n", S_HEADER_A);
	printf("S_HEADER_T %d\n", S_HEADER_T);
	printf("S_HEADER_M %d\n", S_HEADER_M);
	printf("S_HEADER_F %d\n", S_HEADER_F);
	if (TINY_SIZE > 300 || MED_SIZE >300)
		exit(1);
}

void	add_mem_header_old(short type)
{
    dprintf(2,"add meme header type %u\n",type);
	//	show_alloc_mem();
	t_mem	*new;
	//show_alloc_mem();
//	show_alloc_mem();
	printf("S_HEADER_A %d\n", S_HEADER_A);
	printf("S_HEADER_T %d\n", S_HEADER_T);
	printf("S_HEADER_M %d\n", S_HEADER_M);
	printf("S_HEADER_F %d\n", S_HEADER_F);
	printf("TINY_SIZE %lu\n", TINY_SIZE);
//	show_alloc_mem();
	printf("\n\n");
	//show_alloc_mem();
	S_HEADER_A++;
	if (!(new = mem_header(g_mem->nb_pages_header)))
		exit (1);
	S_HEADER_A--;
	ft_memcpy(new, g_mem, sizeof(t_mem) + getpagesize() * (S_HEADER_A + S_HEADER_T + S_HEADER_M + S_HEADER_F) + sizeof(t_mem));
   // ft_memcpy(new, g_mem, sizeof(t_mem) + getpagesize() * (S_HEADER_A + S_HEADER_T + S_HEADER_M + S_HEADER_F));
   // exit (13);
	if (type == 0)
	{
		printf("reset 0\n");
		ft_memmove(
				(t_med *)((void *)(new + 1) + getpagesize() * (S_HEADER_A + S_HEADER_T + 1)),
				(t_med *)((void *)(g_mem + 1) + getpagesize() * (S_HEADER_A + S_HEADER_T)), getpagesize() * (S_HEADER_M + S_HEADER_F));
	g_mem = new;
		ft_bzero((void *)(g_mem+ 1) + getpagesize() * (S_HEADER_A + S_HEADER_T), getpagesize());
	S_HEADER_T++;
		new->max_size[0] = MAX_HEADER(t_tny, 1);
		printf("wtf\n");
	}
	else if (type == 1)
	{
		printf("reset 1\n");
		ft_memmove(
				(t_med *)((void *)(new +1) + getpagesize() * (S_HEADER_A + S_HEADER_T + S_HEADER_M + 1)),
				(t_med *)((void *)(g_mem + 1) + getpagesize() * (S_HEADER_A + S_HEADER_T  + S_HEADER_M)), getpagesize() * (S_HEADER_F));
	g_mem = new;
		ft_bzero((void *)(g_mem + 1) + getpagesize() * (S_HEADER_A + S_HEADER_T + S_HEADER_M), getpagesize());
		S_HEADER_M++;
		new->max_size[1] = MAX_HEADER(t_med, 1);
	}
	else if (type == 2)
	{
		printf("reset 2\n");
	g_mem = new;
		S_HEADER_F++;
		new->max_size[2] = MAX_HEADER(t_fat,1);
	}
	else if (type == 3)
	{
		printf("reset 3\n");
	ft_memmove(
				(t_med *)((void *)(new + 1) + getpagesize() * (S_HEADER_A +  1)),
				(t_med *)((void *)(g_mem + 1) + getpagesize() * (S_HEADER_A ))
				, getpagesize() * (S_HEADER_F + S_HEADER_T + S_HEADER_M));
	g_mem = new;
		ft_bzero((void *)(g_mem + 1) + getpagesize() * (S_HEADER_A), getpagesize());
		S_HEADER_A++;
		new->max_size[3] = MAX_HEADER(t_start,1);
	//	exit (9);
	}
	t_start	*start = (t_start *)(g_mem + 1);
//	munmap(g_mem, total);
//	g_mem = new;
	start = (t_start *)(g_mem + 1);
	//show_alloc_mem();
	printf("et la\n");
	printf("\nHEADER_A %p\n\n", start->start);
	printf("HEADER_T %p\n", H_TINY);
	printf("HEADER_M %p\n", H_MED);
	printf("MAX_HEADER M %lu\n", MAX_HEADER(t_med, 1));
	printf("HEADER_F %p\n", H_FAT);
	printf("TINY_SIZE %lu\n", TINY_SIZE);
	printf("MED_SIZE %lu\n", MED_SIZE);
	printf("FAT_SIZE %lu\n", FAT_SIZE);
	printf("A_SIZE %lu\n", A_SIZE);
	printf("S_HEADER_A %d\n", S_HEADER_A);
	printf("S_HEADER_T %d\n", S_HEADER_T);
	printf("S_HEADER_M %d\n", S_HEADER_M);
	printf("S_HEADER_F %d\n", S_HEADER_F);
	if (TINY_SIZE > 300 || MED_SIZE >300)
		exit(1);
}
/**
 *
 * @param ptr
 * @param next
 * @return t_start * start , if next === 1 => node restant apres celle de start
 *
 */
t_start	*get_start(void *ptr, bool next)
{
	t_start	*start;
	size_t	node;

	/**
	 * node = nbr de HEADER A
	 * start = ou commence les HEADER A
	 **/
	node = MAX_HEADER(t_start, S_HEADER_A) - A_SIZE;
	start = (t_start *)(g_mem + 1);
//	printf ("get_start ptr %p node %lu\n", ptr, node);
	/**
	 * Tant qu il y a un Header
	 *  Si ptr est entre start->start et start + MAX_MED + MAX_TINY  (la plage allouee par get_data)
	 *  break;
	 */
	while (node--)
	{
		if (ptr >= start->start && ptr < start->start + MAX_MED + MAX_TINY)
			break;
		start++;
	}
//	printf("get_start ret node %lu\n", node);
	if (next)
	{
		return ((t_start *)node);
	}
	return (start);
}
/**
 *
 * @param ptr
 * @return t_start *start + 1 of the ptr si il existe pas il le creer
 */
t_start	*get_new_data(void *ptr)
{
	t_start	*new;

	dprintf(2, "TINY_SIZE %lu MED_SIZE %lu\n", TINY_SIZE, MED_SIZE);
	dprintf(2, "ptr %p\n", ptr);
	/**
	 * SI !A_SIZE === 0 => plus de place pour un HEADER_A.
	 */
	if (!A_SIZE)
		add_mem_header (3);
	/**
	 * SI get_start(ptr) next existe
	 * return le start du ptr
	*	////////////// revoir lao
	 **/
	if (get_start(ptr, 1) != (t_start *)0)
	{
		return (get_start(ptr,0) + 1); // ajoute + 1 car je veux start + 1 un new data et pas le meme
	}
/**
 * se positioner apres le dernier header A (qui  ne doit pas etre utilise)
 * allocation d une nouvelle plage
 * decrimenter la taille de Header A
 */
	new = get_start(ptr, 0) + 1;
	new->start = mem_data();
	A_SIZE--;
	dprintf(2, "\t\t\t\t\t\t\t\tA_SIZE %lu\n", A_SIZE);
	dprintf(2,"new %p\n",new->start);
	debug_check_MAX_HEADER();
		dprintf(2,"new %p H_TINY %p\n", new, H_TINY);
	return (new);
}
