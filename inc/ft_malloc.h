/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 20:50:34 by jgounand          #+#    #+#             */
/*   Updated: 2018/04/15 21:56:38 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <string.h>
# include <sys/mman.h>
# include "../libft/libft.a"

# define TINY	1
# define SMALL	2

typedef struct	s_mem
{
	void	*tiny;
	size_t	max_tiny;
	void	*small;
	size_t	max_small;
	void	*large;
	size_t	max_large;
}				t_mem;

typedef struct	s_addr
{
	void	*start;
	size_t	len;
}				t_addr;

extern	t_malloc	g_mem;

#endif
