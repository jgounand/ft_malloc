/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 17:19:06 by marene            #+#    #+#             */
/*   Updated: 2016/05/18 15:49:12 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"
#include <stdio.h>

int		main(void)
{
	printf("sizeof(t_header) : %lu\n", sizeof(t_header));
	printf("sizeof(int32_t) : %lu\n", sizeof(int32_t));
	return (0);
}
