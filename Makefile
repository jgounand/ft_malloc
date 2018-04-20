CC				=	gcc
NAME			=	ft_malloc
FLAGS			=	-Wall -Wextra -Werror -g -fsanitize=address

LIB_PATH		=	libft
LIB				=	$(LIB_PATH)/libft.a
LIB_LINK		=	-L $(LIB_PATH) -lft

INC_DIR			=	inc
INCS			=	-I $(LIB_PATH)/$(INC_DIR) -I $(INC_DIR)

SRC_DIR			=	src
SRC_BASE		=	main.c ft_malloc.c show_alloc_mem.c
OBJ_DIR			=	obj

SRCS			=	$(addprefix $(SRC_DIR)/, $(SRC_BASE))
OBJS			=	$(addprefix $(OBJ_DIR)/, $(SRC_BASE:.c=.o))

# COLORS
C_NO			=	"\033[00m"
C_OK			=	"\033[35m"
C_GOOD			=	"\033[32m"
C_ERROR			=	"\033[31m"
C_WARN			=	"\033[33m"

# DBG MESSAGE
SUCCESS			=	$(C_GOOD)SUCCESS$(C_NO)
OK				=	$(C_OK)OK$(C_NO)

all: $(NAME)

$(NAME): $(LIB) $(OBJS)
	@$(CC) $(FLAGS) -o $@ $^ $(LIB_LINK)
	@echo "Compiling" [ $(NAME) ] $(SUCCESS)

$(LIB):
	@make -C $(LIB_PATH)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/*.h
	@mkdir -p obj
	@$(CC) $(FLAGS) $(INCS) -c -o $@ $<
	@echo "Linking" [ $< ] $(OK)

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJ_DIR)
	@make -C $(LIB_PATH) clean
	@echo "Cleaning" [ $(NAME) ] "..." $(OK)

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIB_PATH) fclean
	@echo "Delete" [ $(NAME) ] $(OK)

re: fclean all

.PHONY: clean all re fclean
