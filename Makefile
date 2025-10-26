NAME    = cub3D

CC      = cc
RM      = rm -rf
CFLAGS  = -Werror -Wextra -Wall -g3

MLX_PATH    = /home/kbouarfa/minilibx-linux
MLX         = $(MLX_PATH)/libmlx.a

LIBFT_PATH  = ./libft
LIBFT       = $(LIBFT_PATH)/libft.a

SRC_DIR     = ./src/
INC         = -I ./includes \
              -I $(LIBFT_PATH) \
              -I $(MLX_PATH)

SRC         = main.c\
							free/free.c\
							free/free_tools.c\
							parss_utils/parssing.c\
							parss_utils/tools1.c\
							parss_utils/check_path.c\
							parss_utils/read_content.c\
							parss_utils/get_textures.c\
							parss_utils/get_colors.c\
							parss_utils/get_map.c\
							parss_utils/check_map.c\
							minilibx/minilibx.c\
							minilibx/move_player.c\
							minilibx/ray.c\
							minilibx/ray_tools.c\
							minilibx/drawing.c\
							minilibx/load_textures.c\
							minilibx/projection_plane.c\
							minilibx/first_intersection.c\

SRCS        = $(addprefix $(SRC_DIR), $(SRC))
SRC_OBJS    = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(SRC_OBJS) $(MLX) $(LIBFT)
	@echo "🎮 Vinculando para crear el único: $(NAME) 🎮"
	@$(CC) $(CFLAGS) $(SRC_OBJS) -o $@ $(LIBFT) $(MLX) -lXext -lX11 -lm
	@echo "✅ ¡Compilación exitosa! ¡A disfrutar de tu : $(NAME)! 🔥🎮"

%.o: %.c
	@echo "🧩 Compilando $<..."
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@echo "✅ ¡Compilado con éxito!"

$(LIBFT):
	@echo "📦 Construyendo libft..."
	@$(MAKE) -s -C $(LIBFT_PATH) 

$(MLX):
	@echo "🎮🕹️ Construyendo MiniLibX..."
	@$(MAKE) -s -C $(MLX_PATH) 

clean:
	@echo " 📄 Quitando archivos objeto 🗑️"
	@$(RM) $(SRC_OBJS)
	@$(MAKE) -s -C $(LIBFT_PATH) 
	@$(MAKE) -s -C $(MLX_PATH) 
	@echo " ✅Limpieza completa y reinicio...🔄 "

fclean: clean
	@echo " Quitando todos... 🗑️ "
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean > /dev/null 2>&1
	@echo " 🗑️ Limpieza exhaustiva terminada, todo en su lugar! ✅🔄"

re: fclean all

.PHONY: all clean fclean re
