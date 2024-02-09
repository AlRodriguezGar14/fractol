/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 04:18:48 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/09 04:20:49 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	set_fractal_for_mandelbrot(t_fractal *fractal)
{
	double	aspect_ratio;

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
