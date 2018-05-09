/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 19:31:21 by jgounand          #+#    #+#             */
/*   Updated: 2018/05/09 17:46:51 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/ft_malloc.h"

void show_alloc_mem(void)
{
	t_tny	*tmp;
	t_fat	*fat;
	size_t	nb_node;

	init_mem();
	tmp = H_TINY;//	printf("MAX_HEADER(t_tny) %lu %lu \n", MAX_HEADER(t_tny) ,TINY_SIZE);
	nb_node = MAX_HEADER(t_tny, S_HEADER_T) - TINY_SIZE;
	printf("\n\nTINY : %p %lu\n", (void *)g_mem + getpagesize() * 3, nb_node);
	while (nb_node--)
	{
		printf("H %p %p : %d octets\n",tmp, tmp->ptr, tmp->size);
		tmp++;
	}
	printf("%lu header tiny left\n", TINY_SIZE);
	tmp = H_MED;
	nb_node = MAX_HEADER(t_med, S_HEADER_M) - MED_SIZE;
	printf("SMALL : %p %lu\n", (void *)g_mem + getpagesize() * 3 + MAX_TINY, nb_node);
	while (nb_node--)
	{
		printf("%p : %d octets\n", tmp->ptr, tmp->size);
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
	printf("S_HEADER_A %d\n", S_HEADER_A);
	printf("S_HEADER_T %d\n", S_HEADER_T);
	printf("S_HEADER_M %d\n", S_HEADER_M);
	printf("S_HEADER_F %d\n", S_HEADER_F);
	printf("HEADER_A %p\n", (t_start *)(g_mem + 1));
	printf("HEADER_T %p\n", H_TINY);
	printf("HEADER_M %p\n", H_MED);
	printf("HEADER_F %p\n", H_FAT);
	printf("TINY_SIZE %lu\n", TINY_SIZE);
	printf("MED_SIZE %lu\n", MED_SIZE);
	printf("FAT_SIZE %lu\n", FAT_SIZE);
	printf("aaa size %d\n", 0);
	printf("S_HEADER_A %d\n", S_HEADER_A);
	printf("S_HEADER_T %d\n", S_HEADER_T);
	printf("S_HEADER_M %d\n", S_HEADER_M);
	printf("S_HEADER_F %d\n", S_HEADER_F);
	printf("A_SIZE %lu\n", MAX_HEADER(t_start,S_HEADER_A) - A_SIZE);
}
