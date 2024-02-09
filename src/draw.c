/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 23:12:15 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/09 04:52:46 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// using pow() slows the fractal BY A LOT
void	draw_fractal(t_fractal *fractal)
{
	int		iteration;
	double	z_real_squared;
	double	z_imaginary_squared;

	iteration = -1;
	while (++iteration < fractal->max_iterations)
	{
		z_real_squared = fractal->z_real * fractal->z_real;
		z_imaginary_squared = fractal->z_imaginary * fractal->z_imaginary;
		fractal->z_imaginary = 2.0 * fractal->z_real
			* fractal->z_imaginary
			+ fractal->c_imaginary;
		fractal->z_real = z_real_squared - z_imaginary_squared
			+ fractal->c_real;
		if (z_real_squared + z_imaginary_squared > WIDTH)
			break ;
	}
	if (iteration == fractal->max_iterations)
		my_mlx_pixel_put(fractal, fractal->x, fractal->y, 0x000000);
	else
		my_mlx_pixel_put(fractal, fractal->x, fractal->y,
			fractal->color_base * iteration);
}

void	draw(t_fractal *fractal)
{
	fractal->y = -1;
	while (++fractal->y < HEIGHT)
	{
		fractal->x = -1;
		while (++fractal->x < WIDTH)
		{
			if (!ft_strncmp(fractal->name, "mandelbrot", 10))
				set_fractal_for_mandelbrot(fractal);
			else if (!ft_strncmp(fractal->name, "julia", 5))
				set_fractal_for_julia(fractal);
			draw_fractal(fractal);
		}
	}
	mlx_clear_window(fractal->mlx, fractal->window);
	mlx_put_image_to_window(fractal->mlx,
		fractal->window,
		fractal->image,
		0, 0);
}
