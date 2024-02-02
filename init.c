/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:13:29 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/03 00:04:30 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_fractal(t_fractal *fractal, char *name)
{
	fractal->color_base = 0xffffff;
	fractal->zoom = 1;
	fractal->x = 0;
	fractal->y = 0;
	fractal->x_range_min = -2.0;
	fractal->x_range_max = 2.0;
	fractal->y_range_min = -2.0;
	fractal->y_range_max = 2.0;
	fractal->max_iterations = 42;
	fractal->name = ft_sprintf("%s", name);
}

void	init_mlx(t_fractal *fractal)
{
	fractal->mlx = mlx_init();
	fractal->window = mlx_new_window(fractal->mlx, WIDTH, HEIGHT, fractal->name);
	fractal->image = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
	fractal->img_address = mlx_get_data_addr(fractal->image,
				&fractal->bits_per_pixel,
				&fractal->size_line,
				&fractal->endian);
}