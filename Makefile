ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME =			libft_malloc_$(HOSTTYPE).so

LINK =			libft_malloc.so

CC =			gcc

FLAGS =			-Wall -Werror -Wextra -fPIC

HEADERS =		-I ./inc -I $(LIBFT_DIR)

LIBRARIES =		-L$(LIBFT_DIR) -l$(LIBFT_NAME)

LIBFT_NAME =	ft

LIBFT =			$(LIBFT_DIR)lib$(LIBFT_NAME).a

LIBFT_DIR =		./libft/

SRC_DIR =		./src/

OBJ_DIR_NAME =	obj
OBJ_DIR =		./obj/

FILENAMES =		free malloc realloc show_alloc_mem alloc_data

FILENAMES =	ft_malloc show_alloc_mem ft_free mem ft_realloc realloc_node move_header clear_node tools free_tools defragment add_mem_header print_addrhex


OBJ_PATHS :=	$(addsuffix .o,$(FILENAMES))
OBJ_PATHS :=	$(addprefix $(OBJ_DIR),$(OBJ_PATHS))

.PHONY: all clean fclean re libft

all: libft $(NAME)

$(NAME): $(LIBFT) $(OBJ_PATHS)
	@$(CC) $(OBJ_PATHS) $(HEADERS) $(LIBRARIES) -shared -o $(NAME)
	@echo "\033[2K\r\033[0;32m[OK] \033[0m       \033[0;33m $(LINK) created ✅\033[0m"
	@/bin/rm -f $(LINK)
	@ln -s $(NAME) $(LINK)
	@echo "\033[2K\r\033[0;32m[OK] \033[0m       \033[0;33m $(NAME) created ✅\033[0m"

$(OBJ_PATHS): $(OBJ_DIR)%.o: $(SRC_DIR)%.c ./inc/ft_malloc.h
	@/bin/mkdir -p $(OBJ_DIR)
	@echo -e "\033[2K\r\033[0;32m[OK] \033[0m       \033[0;33m Compiling:\033[0m $<\c"
	@$(CC) -c $(FLAGS) $(HEADERS) $< -o $@

libft:
	@Make -C ./libft/

$(LIBFT) ./libft/:
	@Make -C ./libft/

clean:
	@echo "\033[0;32m[OK] \033[0m       \033[0;33m Deleting objects in:\033[0m Malloc" 
	@/bin/rm -rf $(OBJ_DIR)
	@make -C libft/ clean
	@/usr/bin/find . -name "$(OBJ_DIR_NAME)" -maxdepth 1 -type d -empty -delete

fclean:
	@echo "\033[0;32m[OK] \033[0m       \033[0;33m Deleting objects in:\033[0m Malloc" 
	@/bin/rm -rf $(OBJ_DIR)
	@echo "\033[2K\r\033[0;32m[OK] \033[0m       \033[0;33m $(NAME) deleted ✅\033[0m"
	@Make fclean -C ./libft/
	@/bin/rm -f $(NAME) $(LINK)

re: fclean all
