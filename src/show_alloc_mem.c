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

void show_alloc_mem(void)
{
	t_tny	*tmp;
	t_fat	*fat;
	size_t	nb_node;
	t_start	*start;

	init_mem();
	start = (t_start *)(g_mem +1);
	tmp = H_TINY;//	printf("MAX_HEADER(t_tny) %lu %lu \n", MAX_HEADER(t_tny) ,TINY_SIZE);
	nb_node = MAX_HEADER(t_tny, S_HEADER_T) - TINY_SIZE;
	printf("\n\nTINY : %p %lu\n", start->start, nb_node);
	while (nb_node--)
	{
		printf("H %p %p : %d octets\n",tmp, tmp->ptr, tmp->size);
		if (tmp->size > 0 && tmp->size != 2)
		{
		//	exit (11);
		}
		tmp++;
	}
	printf("%lu header tiny left\n", TINY_SIZE);
	tmp = H_MED;
	nb_node = MAX_HEADER(t_med, S_HEADER_M) - MED_SIZE;
	printf("SMALL : %p %lu\n", start->start + MAX_TINY, nb_node);
	while (nb_node--)
	{
		printf("M  %p %p : %d octets\n",tmp, tmp->ptr, tmp->size);
		tmp++;
	}
	printf("%lu header med left\n",MED_SIZE);
	fat = H_FAT;
	nb_node = MAX_HEADER(t_fat, S_HEADER_F) -  FAT_SIZE;
	printf("LARGE: %p %lu\n", (void *)g_mem + getpagesize() *3 + MAX_TINY + MAX_MED, nb_node);
	while (nb_node--)
	{
		printf("%p : %lu octets\n", fat->ptr, fat->size);
		fat++;
	}
	nb_node = MAX_HEADER(t_start, S_HEADER_A) -  A_SIZE;
	start = (void *)(g_mem + 1);
	printf("HEADER_A %lu\n",MAX_HEADER(t_start, S_HEADER_A) - A_SIZE);
	while (nb_node--)
	{
		printf("%p : %p octets\n", start->start, start->start + MAX_TINY);
		start++;;
	}
	}
