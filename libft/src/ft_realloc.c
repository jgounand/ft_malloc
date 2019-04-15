/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 18:05:32 by jgounand          #+#    #+#             */
/*   Updated: 2018/05/24 14:35:48 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc_p(void *ptr, size_t old_size, size_t new_size)
{
	void	*new;

	if (old_size > new_size && ptr)
		return (NULL);
	new = (void *)ft_memalloc(new_size);
	if (!new)
		return (NULL);
	ft_memset(new, 0, new_size);
	if (ptr == NULL)
		return (new);
	new = ft_memcpy(new, ptr, old_size);
	free(ptr);
	return (new);
}
