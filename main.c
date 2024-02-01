/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 19:28:17 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/01 19:51:48by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

typedef struct s_img
{
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}   t_img;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	int		color_base;
	int		zoom;
	char	*name;
    t_img 	*img;
}	t_data;


void    my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char    *dst;
    int     offset;

    offset = (y * img->line_length + x * (img->bits_per_pixel / 8));
    dst = img->addr + offset;
    *(unsigned int*)dst = color;
}

void	print_box(t_data *data, int initial_y, int initial_x, int color_add)
{
    int	idx = initial_y;
    int	jdx;

    while (idx++ < initial_y + 25 && idx < HEIGHT - 1)
    {
        jdx = initial_x;
        while (jdx++ < initial_x + 25 && jdx < WIDTH - 1)
        {
            my_mlx_pixel_put(data->img, jdx, idx, data->color_base * color_add);
        }
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
}

void	data_init(t_data *data)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, data->name);
    img->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	data->img = img;
	data->color_base = 0x99bbff;
	data->zoom = 10;
}

void	fill_with_blocks(t_data *fractal, int size)
{
	int x;
	int y = size / 2;
	int idx = 1;
	while (y < HEIGHT - size / 4 - 1)
	{
		x = size / 2;
		while(x < WIDTH - size / 4 - 1)
		{
			print_box(fractal, y, x, idx++);
			x += size;
		}
		y += size;
	}
}

int	key_hook(int keycode, t_data *fractal)
{
	if (keycode == 53)
	{
		mlx_destroy_window(fractal->mlx, fractal->win);
        free(fractal->mlx);
		exit(1);
	}
	printf("Hi from the key hook: %d\n", keycode);
	return (0);
}

int	close_window(t_data *fractal)
{
	mlx_destroy_window(fractal->mlx, fractal->win);
	free(fractal->mlx);
	exit(1);
}

int	main(int argc, char **argv)
{
	t_data	*fractal;
	
	if (argc != 2)
	{
		ft_fd_printf(2, "How to use: ./fractol mandelbrot\n");
		return (0);
	}

	fractal = (t_data *)malloc(sizeof(t_data));
	if (!fractal)
		return -1;
	fractal->name = ft_sprintf("%s", argv[1]);
	data_init(fractal);
	fill_with_blocks(fractal, 50);
	mlx_key_hook(fractal->win, key_hook, fractal);
	mlx_hook(fractal->win, 17, 0, close_window, fractal);
	mlx_loop(fractal->mlx);

	return (0);
}