/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 19:31:21 by jgounand          #+#    #+#             */
/*   Updated: 2019/04/09 17:30:27 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

char			*ft_strrev(char *str)
{
	int		i;
	int		length;
	char	buff;

	i = 0;
	length = ft_strlen(str);
	while (length - 1 > i)
	{
		buff = str[i];
		str[i] = str[length - 1];
		str[length - 1] = buff;
		length--;
		i++;
	}
	return (str);
}

static void		print_ligne_alloc(void *ptr, long size)
{
	print_addrhex((uint32_t)ptr);
	ft_putstr(" - ");
	if (size >= 0)
		print_addrhex((uint32_t)ptr + size);
	else
		print_addrhex((uint32_t)ptr - size);
	ft_putstr(" : ");
	ft_putnbr(size);
	ft_putendl(" octets");
}

static size_t	print_lignes_tymed(short type, t_tny *node, bool all)
{
	size_t	nb_node;
	size_t	total;

	total = 0;
	if (type == 0)
		ft_putstr("TINY : ");
	if (type == 1)
		ft_putstr("SMALL : ");
	nb_node = type == 0 ? MAX_HEADER(t_tny, S_HEADER_T) - TINY_SIZE :
			MAX_HEADER(t_tny, S_HEADER_M) - MED_SIZE;
	print_addrhex((uint32_t)node->ptr);
	ft_putstr("\n");
	while (nb_node--)
	{
		if (node->size > 0 || all)
		{
			print_ligne_alloc(node->ptr, node->size);
			total += node->size;
		}
		node++;
	}
	return (total);
}

static size_t	print_lignes_fat(t_fat *node, bool all)
{
	size_t	nb_node;
	size_t	total;

	ft_putnbr(FAT_SIZE);
	ft_putnbr(MAX_HEADER(t_fat, S_HEADER_F));
	total = 0;
	nb_node = MAX_HEADER(t_fat, S_HEADER_F) - FAT_SIZE;
	if (nb_node == 0)
		return (0);
	ft_putstr("FAT : ");
	print_addrhex((uint32_t)node->ptr);
	ft_putstr("\n");
	while (nb_node--)
	{
		if (node->size > 0 || all)
		{
			print_ligne_alloc(node->ptr, node->size);
			total += node->size;
		}
		node++;
	}
	return (total);
}

void			show_alloc_mem(void)
{
	size_t	total;

	init_mem();
	total = print_lignes_tymed(0, H_TINY, 0);
	total += print_lignes_tymed(1, H_MED, 0);
	total += print_lignes_fat(H_FAT, 0);
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putstr("\n");
}
