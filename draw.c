/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:17:43 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/02 19:09:22 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void    my_mlx_pixel_put(t_fractal *fractal, int x, int y, int color)
{
    char    *dst;
    int     offset;

    offset = (y * fractal->size_line + x * (fractal->bits_per_pixel / 8));
    dst = fractal->img_address + offset;
    *(unsigned int*)dst = color;
}

void	draw(t_fractal *fractal)
{
	fractal->y = -1;
	while (++fractal->y < HEIGHT - 1)
	{
		fractal->x = -1;
		while (++fractal->x < WIDTH - 1)
			my_mlx_pixel_put(fractal, fractal->x, fractal->y, fractal->color_base);
	}
	mlx_put_image_to_window(fractal->mlx, fractal->window, fractal->image, 0, 0);
}