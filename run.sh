#!/bin/sh
export DYLD_LIBRARY_PATH="/Users/jorisgounand/42/ft_malloc"
export DYLD_INSERT_LIBRARIES="/Users/jorisgounand/42/ft_malloc/libft_malloc_x86_64_Darwin.so"
export DYLD_FORCE_FLAT_NAMESPACE=1
$@
