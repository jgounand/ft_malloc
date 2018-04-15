/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 18:01:35 by jgounand          #+#    #+#             */
/*   Updated: 2017/11/08 10:19:15 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*srctmp;
	unsigned char	*dsttmp;
	size_t			i;

	dsttmp = (unsigned char *)dst;
	srctmp = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dsttmp[(int)i] = srctmp[(int)i];
		if (dsttmp[(int)i] == (unsigned char)c)
			return (dst + i + 1);
		i++;
	}
	return (NULL);
}
