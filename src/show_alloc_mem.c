/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 19:31:21 by jgounand          #+#    #+#             */
/*   Updated: 2018/05/09 10:11:40 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/ft_malloc.h"

void show_alloc_mem(void)
{
	t_tny	*tmp;
	t_fat	*fat;
	size_t	nb_node;

	init_mem();
	tmp = H_TINY;
	printf("MAX_HEADER(t_tny) %lu %lu \n", MAX_HEADER(t_tny) ,TINY_SIZE);
	nb_node = MAX_HEADER(t_tny) - TINY_SIZE;
	printf("\n\nTINY : %p %lu\n", (void *)g_mem + getpagesize() * 3, nb_node);
	while (nb_node--)
	{
		printf("H %p %p : %d octets\n",tmp, tmp->ptr, tmp->size);
		tmp++;
	}
	printf("%lu header tiny left\n", TINY_SIZE);
	tmp = H_MED;
	nb_node = MAX_HEADER(t_med) - MED_SIZE;
	printf("SMALL : %p %lu\n", (void *)g_mem + getpagesize() * 3 + MAX_TINY, nb_node);
	while (nb_node--)
	{
		printf("%p : %d octets\n", tmp->ptr, tmp->size);
		tmp++;
	}
	printf("%lu header med left\n",MED_SIZE);
	fat = H_FAT;
	nb_node = MAX_HEADER(t_fat) -  FAT_SIZE;
	printf("LARGE: %p %lu\n", (void *)g_mem + getpagesize() *3 + MAX_TINY + MAX_MED, nb_node);
	while (nb_node--)
	{
		printf("%p : %lu octets\n", fat->ptr, fat->size);
		fat++;
	}
}
