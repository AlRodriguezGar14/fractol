/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 04:21:09 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/09 04:21:40 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	set_fractal_for_julia(t_fractal *fractal)
{
	double	aspect_ratio;

	aspect_ratio = (double)WIDTH / HEIGHT;
	fractal->z_real = scale(fractal->x,
			WIDTH - 1,
			fractal->x_range_min * aspect_ratio,
			fractal->x_range_max * aspect_ratio);
	fractal->z_imaginary = scale(fractal->y,
			HEIGHT - 1,
			fractal->y_range_min,
			fractal->y_range_max);
	fractal->c_real = fractal->mouse_x;
	fractal->c_imaginary = fractal->mouse_y;
}
