CC       = cc
MINILIBX_DIR = mlx/
MINILIBX = $(MINILIBX_DIR)libmlx.a
FRACTOL_DIR  = .
CFLAGS   = -Wall -Wextra -Werror -g3 -fsanitize=address 
HEADERS  = -I $(MINILIBX_DIR) -I $(FRACTOL_DIR)
NAME     = fractol
RM       = rm -rf

CFILES = main.c
OFILES = $(CFILES:.c=.o)

all: $(NAME)

$(NAME): $(MINILIBX) $(OFILES)
	$(CC) $(CFLAGS) -L $(MINILIBX_DIR) -lmlx $(OFILES) -framework OpenGL -framework AppKit -o $(NAME)


$(MINILIBX):
	make -C $(MINILIBX_DIR)

clean:
	$(RM) $(OFILES)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)