/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 20:50:34 by jgounand          #+#    #+#             */
/*   Updated: 2018/04/23 05:14:12 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <string.h>
# include <sys/mman.h>
# include "../libft/libft.h"

# define TINY	256
# define SMALL	1024
# define NB_PAGES		128
# define MAX_TINY getpagesize() * NB_PAGES * TINY
# define MAX_MED getpagesize() * NB_PAGES * SMALL

typedef struct s_tiny
{
	void			*ptr;
	int				size;
}				t_tny;

typedef struct s_node
{
	void			*ptr;
	size_t			size;
	bool			free;
}				t_node;

typedef t_tny t_med;
typedef t_node t_fat;

typedef struct	s_mem
{
	t_tny	*tiny;
	t_med	*med;
	t_fat	*fat;
	struct s_mem	*next;
}				t_mem;

extern	t_mem	*g_mem;

void *ft_malloc(size_t size);
void show_alloc_mem(void);
t_mem	*init_mem(void);
void ft_free(void *ptr);
size_t	nodecmpt(t_node **node);
#endif
