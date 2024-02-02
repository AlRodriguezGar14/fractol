/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:19:23 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/03 00:07:07 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	close_window(t_fractal *fractal)
{
	mlx_destroy_window(fractal->mlx, fractal->window);
	// Pending to write a function to properly free the fractal
	free(fractal);
	exit(1);
	return (0);
}
void zoom_in(t_fractal *fractal, int x, int y)
{
    double zoom_factor = 0.5; // Change this to zoom in by a different amount
	fractal->zoom *= zoom_factor;
    double x_frac = (double)x / WIDTH;
    double y_frac = (double)y / HEIGHT;
    double x_range = fractal->x_range_max - fractal->x_range_min;
    double y_range = fractal->y_range_max - fractal->y_range_min;
    fractal->x_range_min += x_frac * x_range * zoom_factor;
    fractal->x_range_max -= (1 - x_frac) * x_range * zoom_factor;
    fractal->y_range_min += y_frac * y_range * zoom_factor;
    fractal->y_range_max -= (1 - y_frac) * y_range * zoom_factor;
}

void zoom_out(t_fractal *fractal, int x, int y)
{
    double zoom_factor = 0.5; // Change this to zoom out by a different amount
	fractal->zoom *= zoom_factor;
    double x_frac = (double)x / WIDTH;
    double y_frac = (double)y / HEIGHT;
    double x_range = fractal->x_range_max - fractal->x_range_min;
    double y_range = fractal->y_range_max - fractal->y_range_min;
    fractal->x_range_min -= x_frac * x_range * zoom_factor;
    fractal->x_range_max += (1 - x_frac) * x_range * zoom_factor;
    fractal->y_range_min -= y_frac * y_range * zoom_factor;
    fractal->y_range_max += (1 - y_frac) * y_range * zoom_factor;
}

// void zoom_out(t_fractal *fractal)
// {
// 	fractal->x_range_max *= 1.5; 
// 	fractal->x_range_min *= 1.5; 
// 	fractal->y_range_max *= 1.5; 
// 	fractal->y_range_min *= 1.5; 
// }
// void zoom_in(t_fractal *fractal)
// {
// 	fractal->x_range_max *= 0.8; 
// 	fractal->x_range_min *= 0.8; 
// 	fractal->y_range_max *= 0.8; 
// 	fractal->y_range_min *= 0.8; 
// }

int	mouse_hook(int keycode, int x, int y, t_fractal *fractal)
{
    ft_printf("x: %d\ny: %d\n", x, y);
    if (keycode == ZOOM_IN)
        zoom_in(fractal, x, y);
    if (keycode == ZOOM_OUT)
        zoom_out(fractal, x, y);
    draw(fractal);
    return (0);
}

int	key_hook(int keycode, t_fractal *fractal)
{
	if (keycode == ESC)
		close_window(fractal);
	if (keycode == LEFT)
		move_left(fractal);
	if (keycode == RIGHT)
		move_right(fractal);
	if (keycode == UP)
		move_up(fractal);
	if (keycode == DOWN)
		move_down(fractal);
	if (keycode == PLUS)
	{
		fractal->max_iterations += 50;
    	draw(fractal);
	}
	if (keycode == MINUS)
	{
		if (fractal->max_iterations > 50)
			fractal->max_iterations -= 25;
    	draw(fractal);
	}
	printf("keycode: %d\n", keycode);
	return (0);
}