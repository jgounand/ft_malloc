#!/bin/sh
export DYLD_LIBRARY_PATH='../ft_malloc'
export DYLD_INSERT_LIBRARIES='../libft_malloc.so'
export DYLD_FORCE_FLAT_NAMESPACE=1
$@
