NAME        =   cube3D

CC          =   cc

FLAG        =   -Wall -Wextra -Werror -g3

LIBFT_PATH  =   .libft
LIBFT_FILE  =   libft.a

MLX_FILE    =   libmlx.a
MLX_FLAGS   =   -lX11 -lXext -fPIE
MLX_PATH    =   ./.minilibx-linux
MLX_LIB     =   $(MLX_PATH)/$(MLX_FILE)
MLX_EX      =   $(MLX_LIB) $(MLX_FLAGS)

LIBFT_LIB   =   $(LIBFT_PATH)/$(LIBFT_FILE)

C_FILE		 = 		main.c								\
					parsing/utils_parse.c				\

OBJS        =   $(C_FILE:.c=.o)
DEPS		=	$(OBJS:.o=.d)

all: $(NAME)

-include $(DEPS)

.c.o:
	@printf "\r\033[K[cube3D] \033[0;32mBuilding : $<\033[0m"
	@$(CC) $(FLAG) -c $< -o $@ -MMD -MP

$(LIBFT_LIB):
	@make -C $(LIBFT_PATH)

$(MLX_LIB):
	@printf "\r\033[K[mlx] \033[0;32mLinking...\033[0m"
	@make -sC $(MLX_PATH)

$(NAME): $(LIBFT_LIB) $(MLX_LIB) $(OBJS)
	@printf "\r\033[K[cube3D] \033[0;32mLinking...\033[0m"
	@$(CC) $(OBJS) $(LIBFT_LIB) $(MLX_EX) -o $(NAME) -lm
	@printf "\r\033[K[cube3D] \033[0;32mDone!\033[0m\n"

clean:
	@make clean -sC $(MLX_PATH)
	@make clean -sC $(LIBFT_PATH)
	@rm -f $(OBJS) $(DEPS)
	@printf "[cube3D] \033[1;31mCleaned .o!\033[0m\n"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_PATH)
	@printf "[cube3D] \033[1;31mCleaned all!\033[0m\n"

re: fclean all

.PHONY: all clean fclean re
