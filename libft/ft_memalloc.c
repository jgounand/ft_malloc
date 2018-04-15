/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 18:01:27 by jgounand          #+#    #+#             */
/*   Updated: 2018/01/11 04:13:14 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*tmp;

	tmp = (char *)malloc(size);
	if (!tmp)
	{
		ft_putendl_fd("MALLOC FAILED !!!", 2);
		exit(1);
	}
	ft_bzero(tmp, size);
	return (tmp);
}
