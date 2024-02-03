/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:19:23 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/03 23:01:15 by alberrod         ###   ########.fr       */
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

static double	mouse_relative_position(int pixel, int size)
{
	return ((double)pixel / size);
}

void zoom_in(t_fractal *fractal, int x, int y)
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

void zoom_out(t_fractal *fractal, int x, int y)
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

int	change_color(t_fractal *fractal)
{
	if (fractal->random > 0)
	{
		fractal->color_base += 2;
		draw(fractal);
	}
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
	if (keycode == RANDOM)
	{
		fractal->random *= -1;	
		mlx_loop_hook(fractal->mlx, change_color, fractal);
	}
	if (keycode == PLUS)
	{
		fractal->max_iterations += 25;
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