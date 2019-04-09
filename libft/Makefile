NAME = libft.a
CC = gcc
CFLAGS = -Werror -Wextra -Wall
HEADERS =		-I$(PATH_INC)
PATH_INC = ./inc/
SRC_DIR =		./src/
OBJ_DIR_NAME =	obj
OBJ_DIR =		./obj/


FILENAMES = ft_memset ft_bzero ft_memcpy ft_memccpy ft_memmove ft_memchr \
ft_memcmp ft_strlen ft_strdup ft_strcpy ft_strncpy ft_strcat \
ft_strncat ft_strlcat ft_strchr ft_strrchr ft_strstr ft_strnstr \
ft_strcmp ft_strncmp ft_atoi ft_isalpha ft_isdigit ft_isalnum \
ft_isascii ft_isprint ft_toupper ft_tolower ft_memalloc ft_memdel \
ft_strnew ft_strdel ft_strclr ft_striter ft_striteri ft_strmap \
ft_strmapi ft_strequ ft_strsub ft_strjoin ft_strtrim ft_strsplit \
ft_itoa ft_putchar ft_putstr ft_putendl ft_putnbr ft_putchar_fd \
ft_putstr_fd ft_putendl_fd ft_putnbr_fd ft_strnequ  \
ft_lstnew ft_lstdelone ft_lstdel ft_lstadd ft_lstiter ft_lstmap \
ft_realloc ft_lstaddback ft_strjoin_free ft_lstsort ft_lstsortif \
ft_lstcmp ft_strchr_b ft_swap ft_cptnbr get_next_line open_dir	\
ft_lststr ft_fork close_dir ft_split_whitespaces

OBJ_PATHS :=	$(addsuffix .o,$(FILENAMES))
OBJ_PATHS :=	$(addprefix $(OBJ_DIR),$(OBJ_PATHS))


.PHONY: all clean fclean re

all: $(NAME)

$(NAME) : $(OBJ_PATHS)
		@ar rc $(NAME) $(OBJ_PATHS)
	@echo "\033[2K\r\033[0;32m[OK] \033[0m       \033[0;33m $(NAME) created ✅\033[0m"

$(OBJ_PATHS): $(OBJ_DIR)%.o: $(SRC_DIR)%.c inc/libft.h
	@/bin/mkdir -p $(OBJ_DIR)
	@echo -e "\033[2K\r\033[0;32m[OK] \033[0m       \033[0;33m Compiling:\033[0m $<\c"
	@$(CC) -c $(FLAGS) $(HEADERS) $< -o $@

clean :
	@echo "\033[0;32m[OK] \033[0m       \033[0;33m Deleting objects in:\033[0m Libft" 
		@/bin/rm -rf $(OBJ_DIR_NAME)

fclean : clean
			@/bin/rm -f libft.a
	@echo "\033[2K\r\033[0;32m[OK] \033[0m       \033[0;33m $(NAME) deleted ✅\033[0m"

re : fclean all
