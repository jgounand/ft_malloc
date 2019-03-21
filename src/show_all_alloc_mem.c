
#include "../inc/ft_malloc.h"



void show_all_alloc_mem()
{
    size_t	total;

    init_mem();
    total = 0;
    total = print_lignes_tymed(0,H_TINY,1);
    total += print_lignes_tymed(1,H_MED,1);
    total += print_lignes_fat(H_FAT,1);
    ft_putstr("Total : ");
    ft_putnbr(total);
    ft_putstr("\n");
}
