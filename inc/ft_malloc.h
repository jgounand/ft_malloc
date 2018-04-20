/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 20:50:34 by jgounand          #+#    #+#             */
/*   Updated: 2018/04/20 21:36:20 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <string.h>
# include <sys/mman.h>
# include "../libft/libft.h"

# define TINY	99
# define SMALL	250
# define NB_PAGES		150
# define MAX_TINY getpagesize() * NB_PAGES * TINY
# define MAX_MED getpagesize() * NB_PAGES * SMALL

typedef struct s_node
{
	struct s_node	*next;
	struct s_node	*previous;
	void			*ptr;
	size_t			size;
	char			hexa;
	void			*end;
	bool			free;

}				t_node;

typedef t_node t_tny;
typedef t_node t_med;
typedef t_node t_fat;
typedef t_node t_free;

typedef struct	s_mem
{
	t_tny	*tiny;
	t_med	*med;
	t_fat	*fat;
	t_free	*free;
	struct s_mem	*next;
}				t_mem;

typedef struct	s_key
{
	unsigned short	key;
}				t_key;

extern	t_mem	*g_mem;

void *ft_malloc(size_t size);
void show_alloc_mem(void);
t_mem	*init_mem(void);
void ft_free(void *ptr);
#endif
