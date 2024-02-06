/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 23:12:15 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/06 13:46:12 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	end_program(t_fractal *fractal)
{
	// Pending to write a function to properly free the fractal
	// and the mlx pointers
	mlx_destroy_window(fractal->mlx, fractal->window);
	mlx_destroy_image(fractal->mlx, fractal->image);
	free(fractal->mlx);
	free(fractal->name);
	free(fractal);
	exit(0);
}

int mouse_pos(int x, int y, t_fractal *fractal)
{
	fractal->mouse_x = scale(x,WIDTH, fractal->x_range_min, fractal->x_range_max);
	fractal->mouse_y = scale(y, WIDTH, fractal->y_range_min, fractal->y_range_max);
	printf("mouse position:\n\tx: %f\n\ty: %f\n", fractal->mouse_x, fractal->mouse_y);
	if (!ft_strncmp(fractal->name, "julia", 5))
		draw(fractal);
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

void	reset(t_fractal *fractal)
{
	fractal->zoom = 1;
	fractal->random = -1;
	fractal->x_range_min = -2.0;
	fractal->x_range_max = 2.0;
	fractal->y_range_min = -2.0;
	fractal->y_range_max = 2.0;
	draw(fractal);
}

int	key_hook(int keycode, t_fractal *fractal)
{
	if (keycode == ESC)
		end_program(fractal);
	if (keycode == LEFT)
		move_left(fractal);
	if (keycode == RIGHT)
		move_right(fractal);
	if (keycode == UP)
		move_up(fractal);
	if (keycode == DOWN)
		move_down(fractal);
	if (keycode == RESET)
		reset(fractal);
	if (keycode == COLOR_RANDOM)
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
