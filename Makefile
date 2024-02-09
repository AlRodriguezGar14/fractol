CC       = cc
LIBFT_DIR    = utils/
MINILIBX_DIR = .mlx/
MINILIBX = $(MINILIBX_DIR)libmlx.a
FRACTOL_DIR  = .
# CFLAGS   = -Wall -Wextra -Werror -g3 -fsanitize=address
CFLAGS   = -Wall -Wextra -Werror -O3 -g3
#CFLAGS   = -g3
HEADERS  = -I $(FRACTOL_DIR) -I utils
NAME     = fractol
RM       = rm -rf

CFILES = src/main.c \
		src/init.c  \
		src/draw.c  \
		src/hooks.c  \
		src/move_fractal.c \
		src/draw_utils.c \
		src/mouse_hooks.c \
		src/key_hook.c \
		src/fractals/mandelbrot.c \
		src/fractals/julia.c \

OFILES = $(CFILES:.c=.o)

all: $(NAME)

$(NAME): $(MINILIBX) $(OFILES)
	$(CC) $(CFLAGS) -L $(MINILIBX_DIR) -lmlx -lft $(HEADERS) -L $(LIBFT_DIR) $(OFILES) -framework OpenGL -framework AppKit -o $(NAME)


$(MINILIBX):
	make -C $(MINILIBX_DIR)

clean:
	$(RM) $(OFILES)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)
