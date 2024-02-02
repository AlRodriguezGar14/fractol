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

void    my_mlx_pixel_put(t_fractal *fractal, int x, int y, int color)
{
    char    *dst;
    int     offset;

    offset = (y * fractal->size_line + x * (fractal->bits_per_pixel / 8));
    dst = fractal->img_address + offset;
    *(unsigned int*)dst = color;
}


double	scale(double unscaled, double old_max, double new_min, double new_max)
{
	return ((new_max - new_min) * (unscaled - 0) / (old_max - 0) + new_min); 
}

void	mandelbrot(t_fractal *fractal)
{
	int		iteration;
	// the temporary is needed to avoid distortion
	double	real_z_tmp;

	iteration = -1;
	fractal->z_real = 0.0;
	fractal->z_imaginary = 0.0;
	// The zr and zi coordinates adapted to the fractal space
	// takes care of zoom and offset
	// c is the actual pixel
	double aspect_ratio = (double)WIDTH / HEIGHT;
	fractal->c_real = scale(fractal->x, WIDTH - 1, fractal->x_range_min * aspect_ratio, fractal->x_range_max * aspect_ratio);
	fractal->c_imaginary = scale(fractal->y, HEIGHT - 1, fractal->y_range_min, fractal->y_range_max);
	// fractal->c_real = (fractal->x / fractal->zoom) + fractal->offset_x;
	// fractal->c_imaginary = (fractal->y / fractal->zoom) + fractal->offset_y;

	// z = z^2 + c
	// when using complex numbers, the formula is: (a^2 - b^2) + 2abi
	// We have to split this in two operations with reals and imaginaries
	while (++iteration <= fractal->max_iterations)
	{
		// (a^2 - b^2) + c_real
		real_z_tmp = (pow(fractal->z_real, 2) - pow(fractal->z_imaginary, 2)) + fractal->c_real;
		// 2abi + c_imaginary
		fractal->z_imaginary = 2.0 * fractal->z_real * fractal->z_imaginary + fractal->c_imaginary;
		fractal->z_real = real_z_tmp;

		if (pow(fractal->z_real, 2) + pow(fractal->z_imaginary, 2) >= __DBL_MAX__)
			break ;
		if (iteration == fractal->max_iterations)
			my_mlx_pixel_put(fractal, fractal->x, fractal->y, 0x000000);
		else
			my_mlx_pixel_put(fractal, fractal->x, fractal->y, fractal->color_base + 0x002200 * iteration);

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
