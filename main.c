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

typedef struct s_fractal
{
	void	*mlx;
	void	*win;
	int		color_base;
	char	*name;
    t_img 	*img;
}	t_fractal;


void    my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
    char    *dst;
    int     offset;

    offset = (y * data->line_length + x * (data->bits_per_pixel / 8));
    dst = data->addr + offset;
    *(unsigned int*)dst = color;
}

void	print_box(t_fractal *fractal)
{
    int	idx = 0;
    int	jdx;

    while (idx++ < HEIGHT / 2 - 1)
    {
        jdx = 0;
        while (jdx++ < WIDTH / 4 - 1)
        {
            my_mlx_pixel_put(fractal->img, jdx, idx, fractal->color_base);
        }
    }
    mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img->img, 0, 0);
}

void	fractal_init(t_fractal *fractal)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	fractal->mlx = mlx_init();
	fractal->win = mlx_new_window(fractal->mlx, WIDTH, HEIGHT, fractal->name);
    img->img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	fractal->img = img;
	fractal->color_base = 0x99bbff;
}

int	main(int argc, char **argv)
{
	t_fractal	*fractal;
	
	if (argc != 2)
	{
		ft_fd_printf(2, "How to use: ./fractol mandelbrot\n");
		return (0);
	}

	fractal = (t_fractal *)malloc(sizeof(t_fractal));
	if (!fractal)
		return -1;
	fractal->name = ft_sprintf("%s", argv[1]);
	fractal_init(fractal);
	print_box(fractal);

	mlx_loop(fractal->mlx);
	return (0);
}