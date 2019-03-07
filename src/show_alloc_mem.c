/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 19:31:21 by jgounand          #+#    #+#             */
/*   Updated: 2018/05/18 18:39:58 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/ft_malloc.h"

void show_alloc_mem(int fd)
{
	printf("\n##########################################################\n");
	t_tny	*tmp;
	t_fat	*fat;
	size_t	nb_node;
	t_start	*start;
	short exit_ = 0;

	init_mem();
	start = (t_start *)(g_mem +1);
	tmp = H_TINY;//	printf("MAX_HEADER(t_tny) %lu %lu \n", MAX_HEADER(t_tny) ,TINY_SIZE);
	nb_node = MAX_HEADER(t_tny, S_HEADER_T) - TINY_SIZE;
	dprintf(fd,"\n\nTINY : %p %lu\n", start->start, nb_node);
	size_t nb = 0;
	size_t nb_positif = 0;
	while (nb_node--)
	{
		dprintf(fd,"H %p %p : %d octets \tnumber : %zu\n",tmp, tmp->ptr, tmp->size,nb);
		if (tmp->size == 0)
		{

			dprintf(fd,"--------------------------------------------------------------------------\n");
			exit_ = 1;
		}
		if (get_type(tmp->ptr))
		{
			dprintf(fd,"--------------------------------------------------------------------------\n");
			exit_ = 2;
		}
		if (tmp->size > 0)
			nb_positif++;
		nb++;
		tmp++;
	}
	dprintf(fd,"%lu header tiny left\n", TINY_SIZE);
	tmp = H_MED;
	nb_node = MAX_HEADER(t_med, S_HEADER_M) - MED_SIZE;
	dprintf(fd,"SMALL : %p %lu header %p\n", start->start + MAX_TINY, nb_node,tmp);
	nb = 0;
	while (nb_node--)
	{
		dprintf(fd,"M  %p %p : %d octets \tnumber : %zu\n",tmp, tmp->ptr, tmp->size,nb);
		if (tmp->size == 0)
		{

			dprintf(fd,"--------------------------------------------------------------------------\n");
			exit_ = 1;
		}
		if (!get_type(tmp->ptr))
		{
			dprintf(fd,"--------------------------------------------------------------------------\n");
			exit_ = 2;
		}
		if (tmp->size > 0)
			nb_positif++;
		tmp++;
		nb++;
	}
	dprintf(fd,"%lu header med left\n",MED_SIZE);
	fat = H_FAT;
	nb_node = MAX_HEADER(t_fat, S_HEADER_F) -  FAT_SIZE;
	dprintf(fd,"LARGE: %p %lu\n", (void *)g_mem + getpagesize() *3 + MAX_TINY + MAX_MED, nb_node);
	while (nb_node--)
	{
		dprintf(fd,"%p %p : %lu octets\n",fat, fat->ptr, fat->size);
		nb_positif++;
		fat++;
	}
	dprintf(fd,"%lu header fat left\n",FAT_SIZE);
	nb_node = MAX_HEADER(t_start, S_HEADER_A) -  A_SIZE;
	start = (t_start *)(g_mem + 1);
	dprintf(fd,"HEADER_A %lu\n",MAX_HEADER(t_start, S_HEADER_A) - A_SIZE);
	nb = 0;
	while (nb_node--)
	{
		dprintf(fd,"%p : %p octets to %p to %p \tnumber : %zu\n", start, start->start,start->start + MAX_TINY, start->start + MAX_TINY + MAX_MED, nb);
		start++;;
		nb++;
	}
	dprintf(fd,"S_HEADER_A %u \n S_HEADER_T %u \n S_HEADER_M %u \n S_HEADER_F %u\n", S_HEADER_A, S_HEADER_T,S_HEADER_M,S_HEADER_F);
	dprintf(fd,"g_mem %p\n",g_mem);
	dprintf(fd,"nb positif alloc %zu current_size %zu\n", nb_positif, current_size);
	dprintf(fd,"\n##########################################################\n");
	if (fd == 1)
		dprintf(fd,"------------------------------------------------------------------------\n");

	if (nb_positif != current_size && fd == 1)
		exit_ =0;
	if (exit_)
		exit(13);

}
