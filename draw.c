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
    int     y_offset;
    int     x_offset;

    y_offset = y * fractal->size_line;
    x_offset = x * fractal->bits_per_pixel / 8;
    dst = fractal->img_address + y_offset + x_offset;
    *(unsigned int *)dst = color;
}


// c is the position of the pixel, which is scalated to the required size.
// c real is x axis
// c imaginary is y axis
void    set_fractal_for_mandelbrot(t_fractal *fractal)
{
    double  aspect_ratio;

    fractal->z_real = 0.0;
    fractal->z_imaginary = 0.0;
    aspect_ratio = (double)WIDTH / HEIGHT;
    fractal->c_real = scale(fractal->x, 
                WIDTH - 1,
                fractal->x_range_min * aspect_ratio,
                fractal->x_range_max * aspect_ratio);
    fractal->c_imaginary = scale(fractal->y,
                HEIGHT - 1,
                fractal->y_range_min,
                fractal->y_range_max);

}

// The formula for the Mandelbrot set is z = z^2 + c, where z and c are complex numbers.
// A complex number is of the form a + bi, where a is the real part, b is the imaginary part, and i is the square root of -1.

// When squaring a complex number (z^2), we get (a + bi)^2 = a^2 + 2abi - b^2 (because i^2 = -1).
// This gives us a new complex number with a real part (a^2 - b^2) and an imaginary part (2ab).

// The expression (a + bi)^2 is a result of applying the binomial theorem,
// which states that (x + y)^2 = x^2 + 2xy + y^2.

// So, when we say z = z^2 + c, we're actually doing two operations:
// 1. For the real part: z_real = (a^2 - b^2) + c_real
// 2. For the imaginary part: z_imaginary = (2ab) + c_imaginary

// This is why we split the operation into two parts, one for the real part and one for the imaginary part.


// Note: using pow() slows the fractal BY A LOT
void	mandelbrot(t_fractal *fractal)
{
    int		iteration;
    double	z_real_squared;
    double	z_imaginary_squared;

    iteration = -1;
    set_fractal_for_mandelbrot(fractal);
    while (++iteration < fractal->max_iterations)
    {
        z_real_squared = fractal->z_real * fractal->z_real;
        z_imaginary_squared = fractal->z_imaginary * fractal->z_imaginary;
        fractal->z_imaginary = 2.0 * fractal->z_real * fractal->z_imaginary + fractal->c_imaginary;
        fractal->z_real = z_real_squared - z_imaginary_squared + fractal->c_real;
        if (z_real_squared + z_imaginary_squared > WIDTH)
            break ;
    }
    if (iteration == fractal->max_iterations)
        my_mlx_pixel_put(fractal, fractal->x, fractal->y, 0x000000);
    else
        my_mlx_pixel_put(fractal, fractal->x, fractal->y, fractal->color_base * iteration);
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