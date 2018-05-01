/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 20:50:34 by jgounand          #+#    #+#             */
/*   Updated: 2018/05/01 16:54:54 by jgounand         ###   ########.fr       */
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
# define MAX_TINY getpagesize() * NB_PAGES
# define MAX_MED getpagesize() * NB_PAGES
# define H_TINY (t_tny *)(g_mem + 1)
# define H_MED (t_med *)(g_mem + getpagesize())
# define H_FAT (t_fat *)(g_mem + getpagesize() * 2)
# define TINY_SIZE g_mem->max_size[0]
# define MED_SIZE g_mem->max_size[1]
# define FAT_SIZE g_mem->max_size[2]

typedef struct s_tiny
{
	void			*ptr;
	short				size;
}				t_tny;

typedef struct s_node
{
	void			*ptr;
	size_t			size;
}				t_node;

typedef t_tny t_med;
typedef t_node t_fat;

typedef struct	s_mem
{
	size_t	max_size[3];
	struct s_mem	*next;
}				t_mem;

extern	t_mem	*g_mem;

void *ft_malloc(size_t size);
void show_alloc_mem(void);
t_mem	*init_mem(void);
void ft_free(void *ptr);
size_t	nodecmpt(t_node **node);
#endif
