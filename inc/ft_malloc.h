/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 20:50:34 by jgounand          #+#    #+#             */
/*   Updated: 2018/04/16 17:09:33 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <string.h>
# include <sys/mman.h>
# include "../libft/libft.h"

# define TINY	200
# define SMALL	2

typedef struct s_node
{
	struct s_node	*next;
	struct s_node	*end;
}				t_node;

typedef struct	s_mem
{
	t_node	*tiny;
	size_t	max_tiny;
	t_node	*small;
	size_t	max_small;
	t_node	*large;
//	size_t	max_large;
	struct s_mem	*next;
}				t_mem;

extern	t_mem	*g_mem;

void *ft_malloc(size_t size);
#endif
