/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:13:29 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/02 18:13:46 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_fractal(t_fractal *fractal, char *name)
{
	fractal->color_base = 0xff00ff;
	fractal->zoom = 200;
	fractal->x = 0;
	fractal->y = 0;
	fractal->offset_x = -2.3;
	fractal->offset_y = -1.20;
	fractal->max_iterations;
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