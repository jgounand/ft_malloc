/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 20:18:51 by jgounand          #+#    #+#             */
/*   Updated: 2017/11/08 09:28:53 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	size_dst;
	size_t	size_src;

	i = 0;
	if (!size)
		return (ft_strlen(dst));
	while (dst[i] != '\0')
		i++;
	size_dst = i;
	i = 0;
	while (src[i] != '\0')
		i++;
	size_src = i;
	i = 0;
	while (src[i] != '\0' && (size_dst + i) < size - 1)
	{
		dst[size_dst + i] = src[i];
		i++;
	}
	dst[size_dst + i] = '\0';
	if (size_dst < size)
		return (size_dst + size_src);
	else
		return (size + size_src);
}
