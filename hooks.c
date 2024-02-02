/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:19:23 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/02 22:19:50 by alberrod         ###   ########.fr       */
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

void zoom_out(t_fractal *fractal)
{
	fractal->x_range_max *= 1.5; 
	fractal->x_range_min *= 1.5; 
	fractal->y_range_max *= 1.5; 
	fractal->y_range_min *= 1.5; 
}
void zoom_in(t_fractal *fractal)
{
	fractal->x_range_max *= 0.8; 
	fractal->x_range_min *= 0.8; 
	fractal->y_range_max *= 0.8; 
	fractal->y_range_min *= 0.8; 
}

int	mouse_hook(int keycode, int x, int y, t_fractal *fractal)
{
	ft_printf("x: %d\ny: %d\n", x, y);
	if (keycode == ZOOM_IN)
		zoom_in(fractal);
	if (keycode == ZOOM_OUT)
		zoom_out(fractal);
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
	printf("keycode: %d\n", keycode);
	return (0);
}