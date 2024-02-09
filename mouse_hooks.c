/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:37:43 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/09 02:42:00 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mouse_pos(int x, int y, t_fractal *fractal)
{
	fractal->mouse_x = scale(x, WIDTH,
			fractal->x_range_min,
			fractal->x_range_max);
	fractal->mouse_y = scale(y, HEIGHT,
			fractal->y_range_min,
			fractal->y_range_max);
	if (!ft_strncmp(fractal->name, "julia", 5))
		draw(fractal);
	return (0);
}

static double	mouse_relative_position(int pixel, int size)
{
	return ((double)pixel / size);
}

void	zoom_out(t_fractal *fractal, int x, int y)
{
	double	mouse_x_relative;
	double	mouse_y_relative;
	double	zoom_factor;
	double	x_range;
	double	y_range;

	zoom_factor = 0.5;
	fractal->zoom *= zoom_factor;
	if (fractal->zoom < 0.05)
		fractal->zoom = 0.05;
	mouse_x_relative = mouse_relative_position(x, WIDTH);
	mouse_y_relative = mouse_relative_position(y, HEIGHT);
	x_range = fractal->x_range_max - fractal->x_range_min;
	y_range = fractal->y_range_max - fractal->y_range_min;
	fractal->x_range_min -= mouse_x_relative * x_range * zoom_factor;
	fractal->x_range_max += (1 - mouse_x_relative) * x_range * zoom_factor;
	fractal->y_range_min -= mouse_y_relative * y_range * zoom_factor;
	fractal->y_range_max += (1 - mouse_y_relative) * y_range * zoom_factor;
}

void	zoom_in(t_fractal *fractal, int x, int y)
{
	double	mouse_x_relative;
	double	mouse_y_relative;
	double	zoom_factor;
	double	x_range;
	double	y_range;

	zoom_factor = 0.5;
	fractal->zoom *= zoom_factor;
	if (fractal->zoom < 0.05)
		fractal->zoom = 0.05;
	mouse_x_relative = mouse_relative_position(x, WIDTH);
	mouse_y_relative = mouse_relative_position(y, HEIGHT);
	x_range = fractal->x_range_max - fractal->x_range_min;
	y_range = fractal->y_range_max - fractal->y_range_min;
	fractal->x_range_min += mouse_x_relative * x_range * zoom_factor;
	fractal->x_range_max -= (1 - mouse_x_relative) * x_range * zoom_factor;
	fractal->y_range_min += mouse_y_relative * y_range * zoom_factor;
	fractal->y_range_max -= (1 - mouse_y_relative) * y_range * zoom_factor;
}
