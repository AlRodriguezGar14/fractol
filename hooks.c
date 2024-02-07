/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 23:12:15 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/07 11:54:59 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// Pending to write a function to properly free the fractal
// and the mlx pointers
int	end_program(t_fractal *fractal)
{
	mlx_destroy_window(fractal->mlx, fractal->window);
	mlx_destroy_image(fractal->mlx, fractal->image);
	free(fractal->mlx);
	free(fractal->name);
	free(fractal);
	exit(0);
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
		mlx_loop_hook(fractal->mlx, change_color, fractal);
	if (keycode == PLUS)
		plus(fractal);
	if (keycode == MINUS)
		minus(fractal);
	printf("keycode: %d\n", keycode);
	return (0);
}
