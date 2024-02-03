/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:17:43 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/02 21:13:50y alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	scale(double unscaled, double old_max, double new_min, double new_max)
{
	return ((new_max - new_min) * (unscaled - 0) / (old_max - 0) + new_min); 
}

void    my_mlx_pixel_put(t_fractal *fractal, int x, int y, int color)
{
    char    *dst;
    int     offset;

    offset = (y * fractal->size_line);
    dst = fractal->img_address + offset;
    *(unsigned int*)(dst + x * (fractal->bits_per_pixel / 8)) = color;
}

void	mandelbrot(t_fractal *fractal)
{
    int		iteration;
    double	real_z_tmp;
    double	z_real_squared;
    double	z_imaginary_squared;

    iteration = -1;
    fractal->z_real = 0.0;
    fractal->z_imaginary = 0.0;
    double aspect_ratio = (double)WIDTH / HEIGHT;
    fractal->c_real = scale(fractal->x, WIDTH - 1, fractal->x_range_min * aspect_ratio, fractal->x_range_max * aspect_ratio);
    fractal->c_imaginary = scale(fractal->y, HEIGHT - 1, fractal->y_range_min, fractal->y_range_max);

    while (++iteration <= fractal->max_iterations)
    {
        z_real_squared = fractal->z_real * fractal->z_real;
        z_imaginary_squared = fractal->z_imaginary * fractal->z_imaginary;
        real_z_tmp = z_real_squared - z_imaginary_squared + fractal->c_real;
        fractal->z_imaginary = 2.0 * fractal->z_real * fractal->z_imaginary + fractal->c_imaginary;
        fractal->z_real = real_z_tmp;

        if (z_real_squared + z_imaginary_squared > WIDTH)
            break ;
        if (iteration == fractal->max_iterations)
            my_mlx_pixel_put(fractal, fractal->x, fractal->y, 0x000000);
        else
            my_mlx_pixel_put(fractal, fractal->x, fractal->y, fractal->color_base * iteration);
            // my_mlx_pixel_put(fractal, fractal->x, fractal->y, fractal->color_base + 0x002200 * iteration);
    }
}

void	draw(t_fractal *fractal)
{
    fractal->y = -1;
    while (++fractal->y < HEIGHT - 1)
    {
        fractal->x = -1;
        while (++fractal->x < WIDTH - 1)
            mandelbrot(fractal);
    }
    mlx_put_image_to_window(fractal->mlx, fractal->window, fractal->image, 0, 0);
}