/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 20:50:34 by jgounand          #+#    #+#             */
/*   Updated: 2018/05/24 14:10:09 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <string.h>
# include <sys/mman.h>
# include "../libft/libft.h"

# define TINY	256
# define SMALL	1024
# define NB_PAGES		1 //32 pour le projet
# define MAX_TINY getpagesize() * NB_PAGES
# define MAX_MED getpagesize() * NB_PAGES
# define H_TINY (t_tny *)((void *)(g_mem + 1) + getpagesize() * S_HEADER_A)
# define H_MED (t_med *)((void *)(H_TINY) + getpagesize() * S_HEADER_T)
# define H_FAT (t_fat *)((void *)H_MED + getpagesize() * S_HEADER_M)
# define S_HEADER_T g_mem->nb_pages_header[0]
# define S_HEADER_M g_mem->nb_pages_header[1]
# define S_HEADER_F g_mem->nb_pages_header[2]
# define S_HEADER_A g_mem->nb_pages_header[3]
# define TINY_SIZE g_mem->max_size[0]
# define MED_SIZE g_mem->max_size[1]
# define FAT_SIZE g_mem->max_size[2]
# define A_SIZE g_mem->max_size[3]
# define MAX_HEADER(s,n) getpagesize() * (n) / sizeof(s)

typedef struct s_tiny
{
	void			*ptr;
	int				size;
}				t_tny;

typedef struct s_fat
{
	void			*ptr;
	size_t			size;
}				t_fat;

typedef t_tny t_med;

typedef struct	s_mem
{
	size_t				max_size[4]; // remplacer par nb_pages_data
	unsigned int		nb_pages_header[4];
}				t_mem;

typedef struct	s_start
{
	void *start;
}				t_start;

extern	t_mem	*g_mem;

void *ft_malloc(size_t size);
void show_alloc_mem(void);
t_mem	*init_mem(void);
void ft_free(void *ptr);
short gettype(void *ptr);
t_mem	*init_mem(void);
void	add_mem_header(short type);
void	*get_data(void *ptr,short type, size_t lengh, t_tny *current);
void *get_addr(void *ptr);
t_start	*get_start(void *ptr, bool next);
t_start	*get_new_data(void *ptr);
void	clear_header(void);
t_tny	*ret_node(t_tny	*tofree, void *ptr);
short	get_type(void *ptr);
void	*add_node_free(t_tny *tmp, void *ptr, bool type);


//DEBUG
void	debug_check_MAX_HEADER(void);
#endif
