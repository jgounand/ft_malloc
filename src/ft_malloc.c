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

void *get_addr(void *ptr)
{
	while ((uintptr_t)ptr % 8)
		ptr++;
	return (ptr);
}

void	*add_node_free(t_tny *tmp, void *ptr, bool type)
{
	size_t bytes_cpy;
	void *max;

	dprintf(2,"tmp %p , ptr %p, type %u\n",tmp,ptr,type);
    if (type == 0)
	{
    	max = H_TINY + MAX_HEADER(t_tny,S_HEADER_T);
    	bytes_cpy = (size_t)(max) - (size_t)(tmp + 1) - sizeof(t_tny) * TINY_SIZE;
        dprintf(2, "tmp %p tmp + 1 %p\n", max, tmp + 1);
		dprintf(2, "size to move %lu tiny size %lu\n", bytes_cpy, TINY_SIZE * sizeof(t_tny));
		ft_memmove(tmp + 2, tmp + 1, bytes_cpy);
		//TINY_SIZE--;
	}
    else
	{
		max = H_MED + MAX_HEADER(t_med,S_HEADER_M);
		bytes_cpy = (void *)(max) - (void *)(tmp + 1) - sizeof(t_tny) * MED_SIZE;
		dprintf(2, "tmp %p tmp + 1 %p\n", tmp, tmp + 1);
		dprintf(2, "size to move %lu tiny size %lu\n", bytes_cpy, TINY_SIZE * sizeof(t_tny));
		ft_memmove(tmp + 2, tmp + 1, bytes_cpy);
		//dprintf(2, "size to move %lu\n", (size_t)((void *)(H_MED) + MAX_HEADER(t_tny, 0 + S_HEADER_M) - (void *)(tmp + 1)));
		//MED_SIZE--;
	}
	(tmp + 1)->ptr = ptr;
	if (!diff_data(tmp + 1))
	{
		dprintf(2,"tmp + 1 diff === false");
		(tmp + 1)->size = -((tmp + 2)->ptr - (tmp + 1)->ptr);
		dprintf(2,"tmp + 1 ptr %p, tmp + 2 ptr %p", (tmp + 1)->ptr, (tmp + 2)->ptr);
		if (!(tmp + 1)->size)
			exit (7);
	}
	else
	{
	    dprintf(2,"tmp + 1 diff === true\n");
		(tmp + 1)->size = -(((void *)(get_start((tmp + 1)->ptr, 0)->start) + MAX_TINY  + (type ? MAX_MED : 0)) - (tmp + 1)->ptr);
		dprintf(2, "tmp + 1 size %d\n", (tmp + 1)->size);
		if (!(tmp + 1)->size)
		{
			ft_memmove(tmp + 1, tmp + 2, bytes_cpy);

			if (!type)
				TINY_SIZE++;
			else
				MED_SIZE++;
			printf("Let the Battle Begin 2!\n");
			printf("Press Any Key to Continue\n");
			//getchar();
		}
	}
	if ((tmp + 1)->size == 0)
	{
		dprintf(2,"ft_malloc 1");
		show_alloc_mem(2);
		exit (5);
	}

	return (NULL);
}

void	*add_small(short type, size_t lenght)
{
	t_tny *tmp;
	size_t	node;
	void *new;
	new = NULL;

	debug_check_MAX_HEADER();
	dprintf(2,"add small start\n");

	check_header_left();

	/**
	 * chercher le nombre de header deja utilise,
	 * Init == 1 header avec la size negatif
	 */
	if (type == 1)
	{
		tmp = H_MED;
		node = MAX_HEADER(t_med, S_HEADER_M) - MED_SIZE;
	}
	else
	{
		tmp = H_TINY;
		node = MAX_HEADER(t_tny, S_HEADER_T) - TINY_SIZE;
	}
	dprintf(2,"\t\t\t\ttype %d %p node %lu\n", type, tmp, node);
	while (node)
	{
		if (tmp->size < 0 && lenght <= (size_t)-tmp->size)
			break ;
		if (!node)
			break ;
		tmp++;
		node--;
	}
	dprintf(2,"node %lu tmp->size %d lenght %lu\n", node, tmp->size, lenght);
	//printf("10 lenght %lu => %lu type %d %d node %llu\n",lenght ,((tmp + 1)->ptr - get_addr(tmp->ptr + lenght + 1)), type, (type ? TINY + 1 : 1), node) ;
	//		printf("+");
	/**
	 * Hypothese si node === 0  => parcout toute les nodes sans trouver de place
	 * Donc pas la place dans la data.
	 *
	 */
	if (!node)
	{
		if (!(tmp-1)->ptr)
		{
			/**
			 * Erreur ca ne devrait par arriver
			 */
			dprintf(2,"ft_malloc 2");
			show_alloc_mem(1);
			dprintf(2, "tmp -1 ptr %p, tmp-2 ptr %p tmp -3 ptr %p\n error exit 9\n", (tmp - 1)->ptr, (tmp -2)->ptr, (tmp -3)->ptr);
			exit (9);
		}
		/**
		 * Si la place header === 1 => plus de place, il faut reallouer header
		 * et recommencer le processus
		 */
		if (!(g_mem->max_size[(int)type])) // C'etait -2 avant
		{
			add_mem_header(type);
			printf("error 254\n");
			exit (254);
			return (add_small(type, lenght));
			//ici plus de place need more header et plus de data
		}
		dprintf(2,"1\n");
		dprintf(2,"\til faut realouer data !! type %d\n", type);
		/**
		 * New start, tmp - 1 dernier alloue
		 */
		 add_mem_data(&tmp,type,0);
		 check_header_left();
		 return (add_small(type, lenght));
	}
	/**
	 * tmp + 1 => dernier header qui doit etre negatif car c est la place qui reste dans data.
	 * recherche le prochaine addresse avec % 8, puis la taille est calucle entre le ptr le MAX
	 *
	 */

	int exit_ = 0;
	dprintf(2,"-tmp->size - lenght < 8 == %d\n",-tmp->size - lenght < 8);
	if (!(node - 1) && -tmp->size - lenght < 8)
	{
		dprintf(2,"add_mem_data\n");
		add_mem_data(&tmp,type,1);
	 	node++;
	}
	/**
	 * add node free si il la diffenrence de taille est superieur a 8
	 * Exemple : node -24, need 8 ===> decallage de (node +1,...x) a (node + 2,...x), puis  node = 8, node + 1 = -16.
				{
	 */
	else if (-tmp->size - lenght > 8)
	{
		// ajouter un free apres tmp et le mmemove
		dprintf(2,"3\n");
		new = tmp->ptr;
		dprintf(2,"\tajouter free apres\n");
		dprintf(2,"TINY_SIZE %lu, MED_SIZE %lu, A_SIZE %lu\n",TINY_SIZE,MED_SIZE,A_SIZE);
	//	show_alloc_mem();
		add_node_free(tmp, get_addr(tmp->ptr + lenght + 1), type);
	//	show_alloc_mem();
		//	if (!type)
		//		TINY_SIZE++;
		//	else
		//		MED_SIZE++;
	}
	else
		{
		exit_ = 1;
		if (!type)
	 		TINY_SIZE++;
		else
			MED_SIZE++;
		new = tmp->ptr;
	 	}
	 tmp->size = lenght;
	 dprintf(2,"tmp->size = %d tmp %p\n",tmp->size, tmp);
	 if (check_header_left())
	 	add_small(type,lenght);
	 if (!type)
		TINY_SIZE--;
	 else
		MED_SIZE--;
	//clear_header();
	if ((tmp + 1)->size > 0 && !exit_)
    {
		dprintf(2,"ft_malloc 6");
        show_alloc_mem(1);
        dprintf(1,"tmp + 1 ne doit jamais etre positif ptr %p\n", (tmp + 1)->ptr);
		dprintf(1,"tmp + 1 ne doit jamais etre positif %p\n", (tmp + 1));
		printf("Let the Battle Begin!\n");
		printf("Press Any Key to Continue\n");
		//getchar();
    }
    dprintf(2,"return tmp->ptr\n");
    check_header_left();

	dprintf(2,"TINY_SIZE %lu, MED_SIZE %lu, A_SIZE %lu\n",TINY_SIZE,MED_SIZE,A_SIZE);
	if (!new)
		new = tmp->ptr;
	return (new);
}
void	add_mem_data(t_tny **tmp, short type, short position)
{
	t_tny *tmp2;

	dprintf(2,"\n----- 4 \n");
	dprintf(2,"type %d\n", type);
    dprintf(2,"position %d\n", position);
	dprintf(2,"\ttmp->size %d tmp->ptr %p tmp %p\n", (*tmp)->size, (*tmp)->ptr, *tmp);
	dprintf(2,"g_mem %p\n",g_mem);
	/////////////////////////////////////////////// ajout new data
	dprintf(2,"g_mem %p\n",g_mem);
	t_start	*start = get_new_data(((*tmp) -1)->ptr);
	dprintf(2,"4.1 \n=>start->start %p\n", start->start);
	dprintf(2,"g_mem %p\n",g_mem);
	if (type) /// Med
	{
		/**
         * Ajout dans les header tiny le nouveau clear header
         */

		tmp2 = H_TINY + MAX_HEADER(t_tny, S_HEADER_T) - TINY_SIZE;
        tmp2->ptr = get_addr(start->start);
		((*tmp) + position)->ptr = get_addr(start->start + MAX_TINY);
	}
	else /// Tiny
	{
		/**
         * Ajout dans les header med le nouveau clear header
         */

		tmp2 = H_MED + MAX_HEADER(t_med, S_HEADER_M) - MED_SIZE;
		((*tmp) +position)->ptr = get_addr(start->start);
		tmp2->ptr = get_addr(start->start + MAX_TINY);
	}
	dprintf(2,"get_start->start %p ptr- %p\n", (*tmp)->ptr, get_start((*tmp)->ptr, 0)->start + MAX_TINY);
	((*tmp) + position)->size = - MAX_MED;
	tmp2->size = - MAX_MED;
	dprintf(2, "tmp->ptr %p size %d tmp %p\n", (*tmp)->ptr, (*tmp)->size,tmp);
	dprintf(2, "tmp + 1->ptr %p size %d tmp %p\n", ((*tmp) +1)->ptr, ((*tmp) +1)->size, ((*tmp) + 1));
	dprintf(2,"g_mem %p\n",g_mem);
	if (!position)
	{
		TINY_SIZE--;
		MED_SIZE--;
		return;
	}
	if (type)
		TINY_SIZE--;
	else
		MED_SIZE--;

	return; ;
	if (((*tmp) + position)->size > 0)
	{
		dprintf(2,"tmp + 1 ne doit jamais etre positif, %p size %d\n",(*tmp) + 1, ((*tmp) +1)->size);
		dprintf(2,"ft_malloc 3");
		show_alloc_mem(1);
		exit(33);
	}
	if (!(*tmp)->size)
		exit(34);
	dprintf(2,"\n-----\n");
}
short	check_header_left()
{
	if (!TINY_SIZE || !MED_SIZE || !A_SIZE)
	{
		dprintf(2,"ft_malloc 4");
		show_alloc_mem(2);
		dprintf(2,"add header \n");
		if (!TINY_SIZE)
			add_mem_header(0);
		else if (!MED_SIZE)
			add_mem_header(1);
		else if (!A_SIZE)
			add_mem_header(3);
		dprintf(2,"ft_malloc 5");
		show_alloc_mem(2);
		return (1);
	}
	return (0);
}
void	*add_fat(size_t lenght)
{
	t_fat *tmp;
	size_t	node;

	node = MAX_HEADER(t_fat, S_HEADER_F) - FAT_SIZE;
	printf("ADD FAT\n");
	//tmp = type == 1? H_MED : H_TINY;
	if (!g_mem->max_size[2])
	{
		printf("il faut realouer !!\n");
		add_mem_header(2);
        return (add_fat(lenght));
	}
	tmp = H_FAT; 
	printf("type %p tmp->size %lu \n", tmp, tmp->size);
	while (node--)
		tmp++;
	printf("-\n");
	printf("tmp == H_FAT size %lu\n", lenght);
	//retroruver addresse du ptr;
	tmp->ptr = mmap(NULL,lenght, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	tmp->size = lenght;
	printf("ptr %p\n", tmp->ptr);
	FAT_SIZE--;
	return (tmp->ptr);
}

void *ft_malloc(size_t size)
{
	if (size <= 0)
		return (NULL);
	init_mem();
	if (size <= TINY)
		return (add_small(0,size));
	else if (size <= SMALL)
		return (add_small(1,size));
	else
		return (add_fat(size));
	return (NULL);
}
