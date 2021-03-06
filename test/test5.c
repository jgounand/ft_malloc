/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 17:18:54 by marene            #+#    #+#             */
/*   Updated: 2019/09/10 15:15:43 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/ft_malloc.h"
#include <string.h>

int		main(void)
{
	char	*foo;

	foo = malloc(42);
	strcpy(foo, "bonjour");
	malloc(1024);
	malloc(1024 * 32);
	malloc(1024 * 1024);
	malloc(1024 * 1024 * 16);
	malloc(1024 * 1024 * 128);
	show_alloc_mem(); 
	return (0);
}
