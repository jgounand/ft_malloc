/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 12:39:10 by jgounand          #+#    #+#             */
/*   Updated: 2019/09/10 12:40:41 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

/*
**	Input:	void *ptr
**	Output:	void *ptr
**	Purpose:	return the next ptr % 8
*/

void	*get_addr(void *ptr)
{
	while ((uint32_t)ptr % 16)
		ptr++;
	return (ptr);
}
