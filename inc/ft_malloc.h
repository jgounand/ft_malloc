/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 20:50:34 by jgounand          #+#    #+#             */
/*   Updated: 2019/04/09 18:28:07 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <string.h>
# include <sys/mman.h>
# include "../libft/inc/libft.h"

# define TINY	256
# define SMALL	512
# define NB_PAGES		1
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

typedef struct	s_tiny
{
	void			*ptr;
	int				size;
}				t_tny;

typedef struct	s_fat
{
	void			*ptr;
	size_t			size;
}				t_fat;

typedef t_tny	t_med;

typedef struct	s_mem
{
	size_t				max_size[4];
	unsigned int		nb_pages_header[4];
}				t_mem;

typedef struct	s_start
{
	void *start;
    void *start_tiny;
	void *start_med;
}				t_start;

typedef struct	s_infonode
{
	size_t	left;
	t_tny	*ptr_node;
}				t_infonode;

extern	t_mem	*g_mem;

void			show_alloc_mem(void);
void			*ft_realloc(void *ptr, size_t size);
void			*ft_malloc(size_t size);
void			ft_free(void *ptr);

bool			add_mem_header(short type);

size_t			get_free_nodeleft(short type, size_t lenght);
t_tny			*get_free_node(short type, size_t lenght);
void			check_header_zero(short type);

void			try_defragment(t_tny *tofree);

short			get_type(void *ptr);
bool			not_begin_data(t_tny *tofree);
bool			diff_data(t_tny *tofree, bool type);

t_fat			*get_fat(void *ptr);
t_tny			*ret_node(t_tny *tofree, void *ptr);

void			*add_node_free(t_tny *tmp, void *ptr, bool type);

void			*add_small(short type, size_t lenght);

void			add_mem_data(t_tny **tmp, short type, short position);
t_mem			*mem_header(unsigned int nb_pages[4]);
void			*mem_data(short size);
t_mem			*init_mem(void);

size_t			push_header(t_tny **tmp, short type);
size_t			remove_header(t_tny **tmp, size_t bytes_cpy, short type);

void			print_addrhex(int p);

void			*r_with_node(t_tny **node, size_t size, short type);
void			*r_with_node1(t_tny **node, size_t size, short type);
void			*r_mall_free(t_tny *node, size_t size);

char			*ft_strrev(char *str);

void			*get_addr(void *ptr);
void			add_rm_header(short add, short type);
short			check_header_left(void);
t_start			*get_start(void *ptr, bool next);
t_start			*get_new_data(void *ptr, bool type);

#endif
