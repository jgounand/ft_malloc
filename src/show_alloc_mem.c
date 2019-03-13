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

void	print_addrhex(int p)
{
	char *str;
	char result[7];
	short i = 5;

	ft_bzero(result,7);
	result[0] = '0';
	result[1] = 'x';
	str = "0123456789ABCDEF";
	while (p)
	{
		result[i--] = (str[p % 16]);
		p /= 16;
	}
	ft_putstr(result);
}

void	print_ligne_alloc(void *ptr, size_t size)
{
	print_addrhex((uint16_t)ptr);
	ft_putstr(" - ");
	print_addrhex((uint16_t)ptr + size);
	ft_putstr(" : ");
	ft_putnbr(size);
	ft_putendl(" octets");
}

size_t	print_lignes_tymed(short type, t_tny *node)
{
	size_t	nb_node;
	size_t	total;

	total = 0;
	if (type == 0)
	{
		ft_putstr("TINY : ");
		nb_node = MAX_HEADER(t_tny, S_HEADER_T) - TINY_SIZE;

	}
	if (type == 1)
	{
		ft_putstr("SMALL : ");
		nb_node = MAX_HEADER(t_tny, S_HEADER_M) - MED_SIZE;

	}
	print_addrhex((uint16_t) node->ptr);
	ft_putstr("\n");
	while (nb_node--)
	{
		if (node->size > 0)
		{
			print_ligne_alloc(node->ptr,node->size);
			total += node->size;
		}
		node++;
	}
	return (total);
}

size_t	print_lignes_fat(t_fat	*node)
{
	size_t nb_node;
	size_t	total;

	total = 0;
	nb_node = MAX_HEADER(t_fat, S_HEADER_F) -  FAT_SIZE;
	if (nb_node == 0)
		return (0);
	ft_putstr("FAT : ");
	ft_putnbr(MAX_HEADER(t_fat, S_HEADER_F) -  FAT_SIZE);
	print_addrhex((uint16_t) node->ptr);
	ft_putstr("\n");
	while (nb_node--)
	{
		if (node->size > 0)
		{
			print_ligne_alloc(node->ptr,node->size);
			total += node->size;
		}
		node++;
	}
	return (total);
}

void show_alloc_mem()
{
	size_t	total;

	init_mem();
	total = 0;
	total = print_lignes_tymed(0,H_TINY);
	total += print_lignes_tymed(1,H_MED);
	total += print_lignes_fat(H_FAT);
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putstr("\n");
}
