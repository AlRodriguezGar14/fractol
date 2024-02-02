/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:19:23 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/02 18:29:06 by alberrod         ###   ########.fr       */
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

int	mouse_hook(int keycode, int x, int y, t_fractal *fractal)
{
	ft_printf("x: %d\ny: %d\n", x, y);
	return (0);
}

int	key_hook(int keycode, t_fractal *fractal)
{
	if (keycode == ESC)
		close_window(fractal);
	return (0);
}