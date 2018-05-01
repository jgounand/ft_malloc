/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 19:31:21 by jgounand          #+#    #+#             */
/*   Updated: 2018/05/01 17:05:24 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/ft_malloc.h"

void show_alloc_mem(void)
{
	t_tny	*tmp;
	t_fat	*fat;

	init_mem();
	tmp = H_TINY;
	printf("TINY : %p\n", (void *)g_mem + getpagesize() * 3);
	while (tmp->ptr)
	{
		printf("%p : %d octets\n", tmp->ptr, tmp->size);
		tmp++;
	}
	printf("%lu header tiny left\n", TINY_SIZE);
	tmp = H_MED;
	printf("SMALL : %p\n", (void *)g_mem + getpagesize() * 3 + MAX_TINY);
	while (tmp->ptr)
	{
		printf("%p : %d octets\n", tmp->ptr, tmp->size);
		tmp++;
	}
	printf("%lu header med left\n",MED_SIZE);
	fat = H_FAT;
	printf("LARGE: %p\n", (void *)g_mem + getpagesize() *3 + MAX_TINY + MAX_MED);
	while (tmp->ptr)
	{
		printf("%p : %d octets\n", tmp->ptr, tmp->size);
		tmp++;
	}
}
