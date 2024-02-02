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

typedef struct s_data
{
	void	*mlx;
	void	*win;
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
	int		color_base;
	char	*name;
	int		x;
	int		y;
	double	offset_x;
	double	offset_y;
	double	zoom;
	double	zx;
	double	zy;
	double	cx;
	double	cy;
	int		max_iterations;

}	t_data;


void    my_mlx_pixel_put(t_data *img, int x, int y, int color)
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
            my_mlx_pixel_put(data, jdx, idx, data->color_base * color_add);
        }
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, data->name);
    data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
}
void	init_fractal(t_data *data)
{

	data->color_base = 0x99bbff;
	data->zoom = 100;
	data->x = 0;
	data->y = 0;
	data->offset_x = -1.21;
	data->offset_y = -1.21;
	data->max_iterations = 50;
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

// The x y are the coordenates of the mouse included by the library when
// calling the function. The offset is to zoom to the location of the mouse
int	mouse_hook(int keycode, int x, int y, t_data *fractal)
{
	double	zoom_level;

	zoom_level = 1.42;
	if (keycode == ZOOM_IN)
	{
		fractal->offset_x = (x / fractal->zoom + fractal->offset_x) - (x / (fractal->zoom * zoom_level));
		fractal->offset_y = (y / fractal->zoom + fractal->offset_y) - (y / (fractal->zoom * zoom_level));
		fractal->zoom *= zoom_level;
	}
	if (keycode == ZOOM_OUT && fractal->zoom >= 50)
	{
		fractal->offset_x = (x / fractal->zoom + fractal->offset_x) - (x / (fractal->zoom / zoom_level));
		fractal->offset_y = (y / fractal->zoom + fractal->offset_y) - (y / (fractal->zoom / zoom_level));
		fractal->zoom /= zoom_level;
	}
	printf("zoom: %f\n", fractal->zoom);
	return (0);
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
	init_fractal(fractal);
	fractal->name = ft_sprintf("%s", argv[1]);
	init_mlx(fractal);
	fill_with_blocks(fractal, 50);
	mlx_key_hook(fractal->win, key_hook, fractal);
	mlx_mouse_hook(fractal->win, mouse_hook, fractal);
	mlx_hook(fractal->win, 17, 0, close_window, fractal);
	mlx_loop(fractal->mlx);

	return (0);
}